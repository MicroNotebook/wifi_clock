# Background
Since programming microcontrollers with the Arduino IDE is different from writing a normal C or C++ program, this guide serves as a reference for the Arduino IDE. This guide is broken up into sections, so you can reference it whenever you are unsure about anything related to Arduino.

# New Sketch
When you open a new sketch on the IDE there will be two functions; a `void setup()` function and a `void loop()` function. You can delete the comments in these sections and add your code to each.

In order to run any code you write in this sketch, you must first name the sketch by clicking **File**, then **Save As**. You can then choose where to save it, and what to name the file.

Another thing you must do before uploading a sketch to a board is selecting the type of board you use. To do this, click **Tools**, then **Board**, then the type of board you are using. In the Wifi Clock guides, we use the *NodeMCU 1.0 (ESP-12E Module)*.

The final thing you must do before you can upload a sketch is make sure the correct port is selected. To select a port, click **Tools**, then **Port**, then the correct port. If you are programming on a Windows computer, the port will look like **COMX**, where **X** is a number. If you are programming on a Linux or Mac computer, the port will look like **/dev/ttyX** where **X** could be a number, or the word *USB* followed by a number.

# Setup Function
This function will only be run once when the microcontroller boots up. As the name implies, this is for setup. Usually you declare the pins you're using, initialize any chips you're using, setup interrupts, and set any initial conditions in this function.

# Loop Function
This function will run repeatedly after the setup function is called. This function is for anything you want to do over and over again, such as counting, checking conditions, or updating variables. This function can also be left blank if you have setup interrupts to handle everything.

# Adding Libraries
To add libraries to your IDE, click **Sketch**, then **Include Library**, then **Manage Libraries**. From there, you can install any libraries you want. For the Wifi Clock project, we downloaded the *LedControl* library.

There are two ways to include libraries with an Arduino sketch. The first is the normal way you would do it in C by typing an include statement followed by the library's name. You can also have the IDE do this for you by clicking **Sketch**, then **Include Library**, then clicking on the desired library.

# Before the Setup Function
Like in normal C programs, the place to include libraries and define constants is the first few lines. This should go before the setup function.

It is often necessary when programming microcontrollers to use global variables, whether they are normal variables such as counters, or they are custom objects. Before the setup function is the place to initialize this.

# Board Manager
If you need to add a board to the IDE, such as the NodeMCU board we use with the Wifi Clock, you can do this in the board manager. To get the the board manager, click on **Tools**, then **Board**, then **Boards Manager** From this menu, you can install firmware for new boards, or update firmware for existing boards.

**Note:** You can only download new third party boards by first including the link to them in preferences. To do this, go to **File**, then **Preferences**, then add the URL to the *Additional Boards Manager URLs*. If you need to add more than one, you can separate them with a comma.

# Arduino Constants
Arduino has a lot of predefined constants that you can use. Below is a table of the most common and where to use them. It should be noted that **LED_BUILTIN** is board specific. Since we are using the NodeMCU board with the Wifi Clock, the build-in LED is connected to pin 16.
| Constant | Value | Use Case |
| ----- |:-----:| ----- |
| LOW | 0 | Used with digitalWrite() or digitalRead(). Means logic LOW or 0. |
| HIGH | 1 | Used with digitalWrite() or digitalRead(). Means logic HIGH or 1. |
| true | 1 | Used when evaluating logical expressions. |
| false | 0 | Used when evaluating logical expressions. |
| INPUT | 0 | Used with the pinMode() function for declaring a pin as input. |
| OUTPUT | 1 | Used with the pinMode() function for declaring a pin as output. |
| INPUT_PULLUP| 2 | Used with the pinMode() function for declaring a pin as input with a pull-up resistor. | 
| RISING | 1 | Used with the attachInterrupt() function to specify an ISR should trigger on the rising edge of an event or button press. |
| FALLING | 2 | Used with the attachInterrupt() function to specify an ISR should trigger on the falling edge of an event or button press. |
| CHANGING | 3 | Used with the attachInterrupt() function to specify an ISR should trigger on the rising and falling edge of an event or button press.
| LED_BUILTIN | 16 | The pin number of the built-in LED on the board you are using. Often used with the pinMode() function.

# Common Arduino Functions
This section will detail some of the common Arduino functions and how to use them.

### pinMode
```c
void pinMode(int pin, int mode)
```
The `pinMode()` function enables a pin and tells the microcontroller what mode to set it to. It can also enable pull-up resistors on a pin if it's supported. The first parameter is the pin number you want to setup. The second parameter is the mode you want to set this pin to. The mode can be **INPUT**, **OUTPUT**, or **INPUT_PULLUP**. This function does not return anything.
&nbsp;

### digitalWrite
```c
void digitalWrite(int pin, int value)
```
The `digitalWrite()` function outputs a **1** or **0** on the given pin.  The first parameter is the pin number you want to output the voltage on. The second parameter is the value you want to put on that pin. This can be either **HIGH** (**1**) or **LOW** (**0**). This function does not return anything.

### digitalRead
```c
int digitalRead(int pin)
```
The `digitalRead()` function reads the voltage on the given pin and determines if it is a logic **HIGH** or **LOW**. The first parameter is the pin number you want to read. It outputs either **HIGH** (**1**) or **LOW** (**0**).
&nbsp;

### attachInterrupt
```c
attachInterrupt(digitalPinToInterrupt(pin), ISR, mode)
or
void attachInterrupt(int interrupt, void (*ISR)(void), int mode)
```
The `attachInterrupt()` function allows a given mode to trigger an ISR on from a given pin. This function should be used with the `digitalPinToInterrupt()` function (see first definition). The second definition is just shown here to explain how the function works. The first parameter is the interrupt number. This should be determined by providing the pin number you want to trigger the interrupt to the `digitalPinToInterrupt()` function. The second parameter is the function you want to be triggered by the pin. The third parameter is mode you want to trigger the ISR on the pin. This can be **RISING**, **FALLING**, or **CHANGE** (see Constants section for explanations). This function does not return anything. An example of standard use of this function is provided below.

```c
#define RLED 0
#define MODE 12

void copy(void)
{
	digitalWrite(MODE, !digitalRead(RLED));
}

void setup(void)
{
	pinMode(RLED, OUTPUT);
	pinMode(MODE, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(MODE), copy, CHANGE);
}

void loop(void)
{
}
```
&nbsp;

### digitalPinToInterrupt
```c
int digitalPinToInterrupt(int pin)
```
This function finds what interrupt number corresponds to the given pin and returns it. The first parameter is the pin you want to generate an interrupt. This function outputs the interrupt number for that pin.
&nbsp;

### delay
```c
void delay(unsigned long ms)
```
This function waits the given number of milliseconds. The first parameter of this function is the number of milliseconds to wait. This function does not return anything.

&nbsp;

### delayMicroseconds
```c
void delayMicroseconds(unsigned int us)
```
This function waits the given number of microseconds. For accuracy purposes, if the given number of microseconds is larger than a few thousand, you should use the `delay()` function. The first parameter is the number of microseconds to wait. This function does not return anything.
&nbsp;

### millis
```c
unsigned long millis(void)
```
This function returns the number of milliseconds that have passed since the program started (usually when the microcontroller turns on). This function relies on timers to work, so it is more accurate than delay; however, this can cause issues when using other timers.
&nbsp;

### micros
```c
unsigned long micros(void)
```
This function returns the number of microseconds that have passed since the program started (usually when the microcontroller turns on). This function relies on timers to work, so it is more accurate than delay; however, this can cause issues when using other timers. It should be noted that since microseconds are very small, the variable holding the amount of microseconds that have passed will overflow (and thus lose all meaning) in about 1.19 hours. 
&nbsp;

# LedControl Functions
This section will detail some of the functions in the *LedControl* library and how to use them since they are used heavily with the Wifi Clock. This library allows the user to easily control a MAX7219 chip, which can control sets of 7-segment displays or LED matrices. This library can be downloaded via the **Library Manager**. All the functions in this library are member functions.

### LedControl
```c
LedControl LedControl(int dataPin, int clkPin, int csPin, int numDevices=1)
```
This function initializes the class and returns a *LedControl*. For the Wifi Clock, **dataPin**, **clkPin**, and **csPin** should be set to 13, 14, and 15 respectively. We only use one MAX7219 chip on the Wifi Clock board, so **numDevices** should be set to 1.
&nbsp;

### shutdown
```c
void shutdown(int addr, bool status)
```
This function turns the MAX7219 on or off. The **status** parameter should be set to **false** or **0** to turn the chip on, and **true** or **1** to turn the chip off. The **addr** parameter is the address of the chip. On the Wifi Clock board this should be 0.
&nbsp;

### setIntensity
```c
void setIntensity(int addr, int intensity)
```
This function sets the brightness of the displays. The **intensity** parameter determines how bright the displays are and can be any value from 0 to 15 (inclusive).  The **addr** parameter is the address of the chip. On the Wifi Clock board this should be 0.
&nbsp;

### clearDisplay
```c
void clearDisplay(int addr)
```
This function turns all the LEDs off. The **addr** parameter is the address of the chip. On the Wifi Clock board this should be 0.
&nbsp;

### setDigit
```c
void setDigit(int addr, int digit, byte value, bool dp)
```
This function writes a number to one of the displays. The **digit** parameter is the number of the display you want to write to. On the Wifi Clock board, display 0 is the far right digit and display 5 is the far left digit. The **value** parameter is the number you want to write to the given display. This can be any number 0 to 15 (inclusive). Numbers 10 to 15 will be represented by hexadecimal digits. The **dp** parameter is set to **true** if you want the decimal point on the given display to be turned on, and set to **false** if you want it to be turned off. The **addr** parameter is the address of the chip. On the Wifi Clock board this should be 0.
&nbsp;

### setChar
```c
void setChar(int addr, int digit, char value, bool dp)
```
This function writes a character to the given display. Only some characters can be written to the displays. The **digit** parameter is the number of the display you want to write to. On the Wifi Clock board, display 0 is the far right digit and display 5 is the far left digit. The **value** parameter is the character you want to display on the given digit. This parameter can be set to the characters in the table below. The **dp** parameter is set to **true** if you want the decimal point on the given display to be turned on, and set to **false** if you want it to be turned off. The **addr** parameter is the address of the chip. On the Wifi Clock board this should be 0.
| Type | Characters |
| ----- | ----- |
| digits | 0 1 2 3 4 5 6 7 8 9
| letters | A b c d E F H L P |
| symbols | . - _ |
&nbsp;

# Ticker Functions
This section will detail how to use the timers and functions in the *Ticker* library. This library allows the user to use timers and timer interrupts on the ESP8266. Depending on your version of Arduino, this library can either be downloaded via the **Library Manager**, or it may be included in with ESP8266 packages. All the functions in this library are member functions.

### Ticker
```c
Ticker Ticker(void)
```
This initializes an instance of the Ticker class, which reserves a timer in the ESP8266.
&nbsp;

### attach
```c
void attach(float seconds, callback_function_t callback)
```
This function allows a given ISR to be called based on a Ticker timer. The **seconds** parameter is the amount of seconds you want to pass between calls of the ISR. The **callback** parameter is the function you want to be called repetitively. This should be a function with the format `void funcName(void)`. When passing the function as a parameter, just the name should be used.
&nbsp;

### detach
```c
void detach(void)
```
This function detaches the interrupt from the timer.