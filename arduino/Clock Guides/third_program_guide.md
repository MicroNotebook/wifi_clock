# Background

So far we have made LEDs blink using two different methods. This is fine for beginning, but we have these 7 segment displays on our clock, so let's do something more interesting! This guide will make use of a library to send commands to the chip controlling these displays. You'll also learn about integer division, the modulus operator, and why they are often used in programming. The GIF below demonstrates what the Wifi Clock will do after you have completed this guide.

![](https://giant.gfycat.com/MarriedQuickBluebottlejellyfish.gif)

# Requirements

You must have first completed the Arduino setup guide, and the **Programming the Wifi Clock with Arduino** parts 1 and 2.

# Setup

After opening the Arduino IDE, click **File**, then **New**. This should create a new window of the IDE. In this window, select **File**, then **Save As**. This should bring up a new window in the Arduino folder. If it does not, navigate there. Name the file something descriptive such as **Simple Counter**, then click **Save**.

Also make sure the correct port is selected by selecting **Tools** from the top menu, then **Port**.

# Writing the Code

The first thing we must do is include the *LedControl* library in the sketch. A library is essentially a collection of functions that make coding easier and cleaner. This particular library is for the MAX7219 chip on the bottom of your board and allows us to easily send it commands. To include the library, type the following code as the first line of the program:

```c
#include "LedControl.h"
```
&nbsp;
The next thing we have to do is define what pins are connected to the three control pins of the MAX7219 chip. In the past, we have defined pins using the `const int` format; however, this time we will use `define` statements since they are better for this. For our board, the **DIN** pin is connected to pin 13, the **CLK** pin is connected to pin 14, and the **LOAD** pin is connected to pin 15. To set this up, type the following below where you included the library:

```c
#define DIN 13
#define CLK 14
#define LOAD 15
```
&nbsp;
We now have to make an instance of the LedControl object. You can think of this as a reference to the display or the chip. Type the following to set this up:

```c
LedControl lc = LedControl(DIN, CLK, LOAD, 1);
```

This line names an instance of the LedControl object "lc" and tells the microcontroller the **DIN**, **CLK**, and **LOAD** pins. It also specifies we are only using one of these chips.
&nbsp;
Now that the chip is defined, we have to initialize it. This will involve turning the chip on, setting the brightness, and clearing the display. To do this, type the following in the `setup()` function:

```c
lc.shutdown(0, falses);
lc.setIntensity(0, 8);
lc.clearDisplay(0);
```
&nbsp;
Now that we've done all the necessary setup, we can get to what we want the program to actually do. We will make a simple counter that will count and display seconds, then reset when it gets to 60. First we will make a simple **for** loop. Type the following in the `loop()` function.

```c
for (int i = 0; i < 60; i++) {

	delay(1000);
}
```
&nbsp;
This will tell the microcontroller to count to 60, while waiting a second in between changing. Now that we have the counter, we need a way to display it. To do this, we will make a function. Between the `setup()` and `loop()` functions, add the following:

```c
void write_num(int n)
{

}
```
&nbsp;
This creates the skeleton for a function that will take in a integer number, then write it to the displays. To do this, we will use the function in the *LedControl* library called `setDigit()`. This function takes in a single-digit integer and prints it to the screen, so to make our function work, we will have to manipulate our number. Type the following in the `write_num()` function to do this:

```c
int ones = n % 10;
int tens = n / 10;
lc.setDigit(0, 0, ones, false);
lc.setDigit(0, 1, tens, false);
```
&nbsp;
This code works by first finding the ones place of the number, then the tens place of the number. It then writes the ones place to the far right digit, then the tens place to the second from the right digit.

To get the ones place, we take the result of the number mod 10, which gives the remainder after dividing the number by 10. To get the tens place, we use integer division and divide the number by 10. In integer division, their are no fractions. For example, if we did **19 / 5**, the result would be 3 since 5 goes into 19 three times with a remainder of 4. Similarly, if we did **19 % 5**, the result would be 4 since that is the remainder of **19 / 5**.

All that's left for this program to work is to call this function with the current count each second. To do this, type the following line before the `delay(1000);` line in the **for** loop:

```c
write_num(i);
```
&nbsp;
Save the file by clicking **File**, then **Save**. Next, click the **Tools** tab, then select **Port**. Select the correct port for the clock board. If you are on Windows, this will be something like **COMx** where **x** is a number. If you are on Mac or Linux, the port will be something like **/dev/ttyx** where **x** is a number, or *USB*. After this, press the right-pointing arrow above the name of the file. This will upload the code to the board and run it.

If you get an error after uploading the code, you can reference the code below.

```c
#include "LedControl.h"

#define DIN 13
#define CLK 14
#define LOAD 15

LedControl lc = LedControl(DIN, CLK, LOAD, 1);

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
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

You now have a working counter for seconds. This will be useful later when we make a fully functional clock!

# Bonus

See if you can add to the `write_num()` function to make it count minutes as well. **Hint**: Instead of counting to 60 in the **for** loop, count to 3600, since we want to count the number of seconds in an hour. You will have to modify your `write_num()` function to write the number of minutes to the 2 and 3 digits. In this function, you might want to start by separating minutes and seconds using integer division and the modulus operator. A GIF demonstrating this can be seen below.

![](https://giant.gfycat.com/RepulsiveUnhealthyAmurratsnake.gif)