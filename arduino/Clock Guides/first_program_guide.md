# Background

When learning a new programming language, the first program you almost always write is called a **Hello World** program that simply prints the words *Hello World* to the console. Since microcontrollers don't have screens by default, the **Hello World** for microcontrollers is often making an LED blink. This simple program will do just that to demonstrate the basics of programming in Arduino C. The GIF below demonstrates what the Wifi Clock will do after you have completed this guide.

![](https://giant.gfycat.com/HastyHatefulAmericanratsnake.gif)

# Requirements

You must have first completed the setup guide for Arduino with the NodeMCU.

# Setup

After opening the Arduino IDE, click **File**, then **New**. This should create a new window of the IDE. In this window, select **File**, then **Save As**. This should bring up a new window in the Arduino folder. If it does not, navigate there. Name the file something descriptive such as **Hello World**, then click **Save**.

We should now have a blank Arduino file with two functions: `void setup()` and `void loop()`. The code in the `setup()` function will be executed once when the microcontroller turns on. The code in the `loop()` function will run over and over again after the setup function.

# Writing the Code

Before we can start coding, we need to declare a variable. A variable is a descriptive name that holds some value. Type in the following line before the `setup()` function to make a variable for the red LED on your clock board:

```c
const int RLED = 0;
```
&nbsp;
This line tells the microcontroller to make a variable called RLED. This variable will be an integer (or int) and will be constant (or const), meaning it will always have the same value and never be able to change. The value assigned to this variable is 0, which is the pin number for the red LED. The semicolon at the end of the line means that we are done typing this line. It is like the period at the end of a sentence.

Now we have to tell the microcontroller we want to use this pin, and specify that it is for output, meaning we want to send signals out of the pin. Remove the comment (the line that starts with **//** in the `setup()` function, and replace it with the following:

```c
pinMode(RLED, OUTPUT);
```
&nbsp;
Now that we have written all the setup code, we have to tell the microcontroller what we want to repeatedly do. We want it to turn the red LED on, wait some period of time, turn the red LED off, then wait again. This function will go on and on until the microcontroller gets turned off. Remove the comment (the line that starts with **//** in the `loop()` function, and replace it with the following:

```c
digitalWrite(RLED, HIGH);
delay(1000);
digitalWrite(RLED, LOW);
delay(1000);
```
&nbsp;
The **digitalWrite()** function allows you to turn pins on or off (with HIGH or LOW respectively. The **delay()** function will make the microcontroller do nothing for as many microseconds as you tell it. Since we told it to wait for 1000 microseconds, it will wait for 1 second.

Save the file by clicking **File**, then **Save**. Next, click the **Tools** tab, then select **Port**. Select the correct port for the clock board. If you are on Windows, this will be something like **COMx** where **x** is a number. If you are on Mac or Linux, the port will be something like **/dev/ttyx** where **x** is a number, or *USB*. After this, press the right-pointing arrow above the name of the file. This will upload the code to the board and run it.

If you get an error after uploading the code, you can reference the code below.

```c
const int RLED = 0;

void setup() {
  pinMode(RLED, OUTPUT);
}

void loop() {
  digitalWrite(RLED, HIGH);
  delay(1000);
  digitalWrite(RLED, LOW);
  delay(1000);
}
```

# Congratulations!

You have written your first program with Arduino! This simple program will be the base for everything as complex as making a fully functioning clock that updates time via WiFi.

# Bonus

See if you can setup the other two LEDs to make a sequence. The sequence should turn on the red LED. After waiting for a second, the red LED turns off at the same time the green one turns on. After another second, the green LED should turn off at the same time the blue one turns on.  After the blue LED has been on for a second, it should turn off at the same time the red LED turns on. This should allow the whole thing to repeat. For reference the pin numbers for the green and blue LEDs are 4 and 5 respectively. A GIF demonstrating this can be seen below.

![](https://giant.gfycat.com/CreativeWellwornHalicore.gif)