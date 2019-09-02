# Background

The previous programs have been great for doing one thing at a time, but real world applications have to keep track of many things at once. Modern desktops and laptops accomplish this with running multiple threads or CPU cores all at once, but we don't have this luxury on a microcontroller. The problem then becomes how do we do more than one thing at a time? The answer is interrupts.

Interrupts and exceptions force the CPU to stop what it's doing, go do some other code, then resume where it was when it has finished. This guide will teach you about external interrupts which allow the outside environment change your software. The goal of this guide is to combine the previous two projects so we can light up LEDs with buttons and do something time sensitive, such as counting, at the same time. The GIF below demonstrates what the Wifi Clock will do after you have completed this guide.

![](https://giant.gfycat.com/MellowRespectfulHoneycreeper.gif)

# Requirements

You must have first completed the Arduino setup guide, and the **Programming the Wifi Clock with Arduino** parts 1 through 3.

# Setup

After opening the Arduino IDE, click **File**, then **New**. This should create a new window of the IDE. In this window, select **File**, then **Save As**. This should bring up a new window in the Arduino folder. If it does not, navigate there. Name the file something descriptive such as **Interrupt Counter**, then click **Save**.

Also make sure the correct port is selected by selecting **Tools** from the top menu, then **Port**.

# Writing the Code

Like we did in the previous guide, we must include the *LedControl* library. We must also define the pins for **DIN**, **CLK**, and **LOAD**. After this, we must also create the LedControl object. This should all be done before the setup function. In the setup function, we also need to turn the chip on, set the intensity to 8, and clear the display. This was also done in the previous guide. Try to do this on your own. You can reference the code at the end of the guide if you don't remember.

Now that we have set up the LED controller, we need to make a counter. We can copy the code we wrote in the previous guide to make our lives easier. To do this, click **File**, then **Open**, then find and open the file for your previous project. After this, a new window should open with your old code. Once this is open, copy your `void write_num(int n)` function and the code in your `void loop()` function and paste it into this new project. Upload this code using **Ctrl-u**, or the upload button. You should now have a working counter like in the last guide.

The next thing we need to do is define the pin numbers for the buttons and LEDs in the same way we defined the pins for the LED controller chip. The pin numbers for the buttons and LEDs are in the table below. These should be entered right under the other defined constants
| Constant Name | Pin Number |
|:----------:|:----------:|
| MODE | 12 |
| INCR | 10 |
| DECR | 2 |
| RLED | 0 |
| GLED | 4 |
| BLED | 5 |
&nbsp;
Now that the pins are defined, we can set them up. In the setup function, use the `pinMode()` function to setup the pins in the table above. Do this like you did in the **Buttons** guide. 

Now that our pins are setup, we have to write functions for what should happen when each is pressed. These types of functions are often called "callbacks" or "Interrupt Service Routines" (ISRs). With our particular microcontroller, we need to also put these into a special part of memory with the **ICACHE_RAM_ATTR** tag. For the mode button, type the following before the setup function:

```c
void ICACHE_RAM_ATTR mode_callback(void)
{
	int state = !digitalRead(MODE);
	digitalWrite(RLED, state);
}
```
&nbsp;
The above function will simply turn on the red led when the button is pressed. Copy this function and make the necessary changes for the other two buttons and LEDs.

The last thing we need to do is connect the callbacks we just wrote to the pins themselves. This should go in the setup function after the buttons are set up. To do this for the MODE button, type the following:
```c
attachInterrupt(digitalPinToInterrupt(MODE), mode_callback, CHANGE);
```
&nbsp;
This line attaches the callback for the MODE button to the button itself. It also tells the microcontroller to call the callback whenever the logic level changes on the MODE pin. Try to get write the lines for the other two buttons on your own.

After this, upload the code. You should see the display counting. When you press the buttons, the corresponding LED should light up, but the display keeps counting at the same rate. If you this did not work or you are getting an error, you can reference the code below.

```c
#include "LedControl.h"

#define DIN 13
#define CLK 14
#define LOAD 15
#define MODE 12
#define INCR 10
#define DECR 2
#define RLED 0
#define GLED 4
#define BLED 5

LedControl lc = LedControl(DIN, CLK, LOAD, 1);

void ICACHE_RAM_ATTR mode_callback(void)
{
  int state = !digitalRead(MODE);
  digitalWrite(RLED, state);
}

void ICACHE_RAM_ATTR incr_callback(void)
{
  int state = !digitalRead(INCR);
  digitalWrite(GLED, state);
}

void ICACHE_RAM_ATTR decr_callback(void)
{
  int state = !digitalRead(DECR);
  digitalWrite(BLED, state);
}

void setup() {
  // setup MAX7219
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  // setup buttons
  pinMode(MODE, INPUT_PULLUP);
  pinMode(INCR, INPUT_PULLUP);
  pinMode(DECR, INPUT_PULLUP);

  // setup ISRs
  attachInterrupt(digitalPinToInterrupt(MODE), mode_callback, CHANGE);
  attachInterrupt(digitalPinToInterrupt(INCR), incr_callback, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DECR), decr_callback, CHANGE);
  
  // setup LEDs
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  
}

void write_num(int n)
{
  int ones = n % 10;
  int tens = n / 10;
  lc.setDigit(0, 0, ones, false);
  lc.setDigit(0, 1, tens, false);
}

void loop() {
  for (int i = 0; i < 60; i++) {
    write_num(i);
    delay(1000);
  }
}
```

# Congratulations!

You have written your first program using interrupts. This simple example will allow us to build up to more complex things such as a fully functional clock with a menu.

# Bonus

Try to change your program so that when a button is pressed, it displays the number of the button on the correct display. The table below shows which button corresponds to which number and display. When the button is pressed, the number displays. When any button is released, all the numbers clear except the counter. The buttons should also still control the LEDs.

| Button | Number to Display | Display Number |
|:-----:|:-----:|:-----:|
| MODE | 1 | 5 |
| INCR | 2 | 4 |
| DECR | 3 | 3 |
&nbsp;
**HINT:** There should only be a few places where you need to add or change code for this. In your loop function, you should remove the `int` in the line `for (int i = 0; i < 60; i++) {`. You should then add the line `int i;` after you declare your LedControl object. This makes **i** a global variable.

The next thing you need to change is in each callback, you'll need to add **if** statements to check if the button is pressed, and do the correct operation if it is. Don't forget that when the button is released, the counter still must be there, so you need to rewrite **i** to the display. A GIF demonstrating this can be seen below.

![](https://giant.gfycat.com/BogusGraveCowrie.gif)