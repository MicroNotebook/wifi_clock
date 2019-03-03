from machine import Pin,SPI,Timer
# Registers and associated values
_NOOP = const(0x0)	# Used when cascading Max7219
_DIGIT0 = const(0x3)
_DIGIT1 = const(0x2)
_DIGIT2 = const(0x1)
_DIGIT3 = const(0x6)
_DIGIT4 = const(0x5)
_DIGIT5 = const(0x4)
_DECODEMODE = const(0x9)	# (0 = no decode/raw segment values, 1 = decode only digit 0, 0xFF = decode on all digits)

_DIGIT_DICT = {
    0: _DIGIT0,
    1: _DIGIT1,
    2: _DIGIT2,
    3: _DIGIT3,
    4: _DIGIT4,
    5: _DIGIT5,
}

_RED_LED_PIN = 12
_GREEN_LED_PIN = 13
_BLUE_LED_PIN = 15

_MODE_BUTTON_PIN = 14
_INCR_BUTTON_PIN = 2
_DECR_BUTTON_PIN = 0

_SPI_MOSI_PIN = 5
_SPI_MISO_PIN = 12
_SPI_CLK_PIN = 16
_SPI_CS_PIN = 4

_INTENSITY = const(0xA)		# (0 = lowest intensity, 0xF = max intensity)
_SCANLIMIT = const(0xB)		# (0 = display digit 0 only, 7 = display all 7 digits)
_SHUTDOWN = const(0xC)		# (0 = shutdown, 1 = normal operation)
_DISPLAYTEST = const(0xF)	# (0 = normal mode, 1 = test mode)

_HEX_TO_SEG = { 0x0: 0b1111110, 0x1: 0b0110000, 0x2: 0b1101101, 0x3: 0b1111001, 0x4: 0b0110011, 0x5: 0b1011011, 0x6: 0b1011111, 0x7: 0b1110000, 0x8: 0b1111111, 0x9: 0b1111011, 0xA: 0b1110111, 0xB: 0b0011111, 0xC: 0b1001110, 0xD: 0b0111101, 0xE: 0b1001111, 0xF: 0b1000111,}

class WifiClock:
	def __init__(self):

		#initalize spi
		self.spi = SPI(-1, baudrate=10000000, polarity=1, phase=0, sck=Pin(_SPI_CLK_PIN), mosi=Pin(_SPI_MOSI_PIN), miso=Pin(_SPI_MISO_PIN))
		self.cs = Pin(_SPI_CS_PIN)
		self.cs.init(self.cs.OUT, True)

		#initialize leds
		self.red_led = Pin(_RED_LED_PIN, Pin.OUT)
		self.green_led = Pin(_GREEN_LED_PIN, Pin.OUT)
		self.blue_led = Pin(_BLUE_LED_PIN, Pin.OUT)

		#initialize buttons with interrupts
		self.mode_button = Pin(_MODE_BUTTON_PIN, Pin.IN, Pin.PULL_UP)
		self.mode_button.irq(trigger=Pin.IRQ_FALLING, handler=self.mode_button_callback)
		self.incr_button = Pin(_INCR_BUTTON_PIN, Pin.IN, Pin.PULL_UP)
		self.incr_button.irq(trigger=Pin.IRQ_FALLING, handler=self.incr_button_callback)
		self.decr_button = Pin(_DECR_BUTTON_PIN, Pin.IN, Pin.PULL_UP)
		self.decr_button.irq(trigger=Pin.IRQ_FALLING, handler=self.decr_button_callback)

		#initialize current number
		self.current_num = None

		#initialize timer
		self.timer = Timer(1)

		self.init()

	def register(self, command, data):
		self.cs.value(0)
		self.spi.write(bytearray([command, data]))
		self.cs.value(1)

	def init(self):
		for command, data in (
			(_SHUTDOWN, 0),	# Turn display off
			(_SCANLIMIT, 7),	# Display all 7 digits
			(_DECODEMODE, 0xFF),# Decode all digits
			(_INTENSITY, 0xa),	# Set brightness to 10
			(_SHUTDOWN, 1),	# Turn display on
		):
			self.register(command, data)

		self.write_num(000000)
		self.red_led.value(0)
		self.green_led.value(0)
		self.blue_led.value(0)

	def start_clock24(self):
		self.timer.init(period=1000, mode=Timer.PERIODIC, callback=self.clock_timer_callback)

	def display_brightness(self, value):
		if 0 <= value <= 15:
			self.register(_INTENSITY, value)
		else:
			raise ValueError("Brightness out of range")

	def display_clear(self):
		self.register(_DECODEMODE, 0xFF)
		for i in range(6):
			self.register(_DIGIT_DICT[i], 0x0)

	def write_num(self, value):
		self.register(_DECODEMODE, 0xFF)
		if (0 <= value <= 999999):
			self.current_num = value
			for i in range(6):
				self.register(_DIGIT_DICT[i], value % 10)
				value = value // 10
		elif (0 > value >= -99999):
			self.current_num = value
			value = -value
			self.register(_DIGIT5, 0xA)
			for i in range(5):
				self.register(_DIGIT_DICT[i], value % 10)
				value = value // 10
		else:
			raise ValueError("Value out of range")


	def write_hex(self, value):
		self.register(_DECODEMODE, 0x0)
		if (0x0 <= value <= 0xffffff):
			for i in range(6):
				self.register(_DIGIT_DICT[i], _HEX_TO_SEG[value % 16])
				value = value // 16
		else:
			raise ValueError("Value out of range")


	def _debounce(self, button):
		flag = 0

		for i in range(50):
			flag = button.value()
			if button.value():
				return not flag

		return not flag


	# button callbacks
	def mode_button_callback(self, pin):
		if self._debounce(self.mode_button):
			self.toggle_led(self.red_led)

	def incr_button_callback(self, pin):
		if self._debounce(self.incr_button):
			self.increment_num()

	def decr_button_callback(self, pin):
		if self._debounce(self.decr_button):
			self.decrement_num()

	# timer callbacks
	def timer_callback(self, tim):
		self.increment_num()

	def clock_timer_callback(self, val):
		self.increment_clock24()

	#other functions
	def toggle_led(self, led):
		led.value(not (led.value()))

	def increment_num(self):
		if (self.current_num + 1) > 999999:
			self.current_num = 0
		self.write_num(self.current_num + 1)

	def increment_clock24(self):
		if self.current_num >= 235959:
			self.write_num(000000)

		elif ((self.current_num % 10000) + 1) >= 5960:
			self.write_num(self.current_num - 5959 + 10000)
			
		elif (((self.current_num + 1) % 100) // 60) == 1:
			self.write_num(self.current_num - 59 + 100)

		else:
			self.increment_num()
	
	def decrement_num(self):
		if (self.current_num - 1) < -99999:
			self.current_num = 0
		self.write_num(self.current_num - 1)


		
