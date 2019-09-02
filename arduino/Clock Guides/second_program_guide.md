# Background

So far we have made an LED blink at a consistent rate, but what if we want to make the LED light up when the user interacts with it? For this, we would need some kind of input, in this case, a button. This guide will teach you how to use buttons on the clock board to make a corresponding LED light up. The GIF below demonstrates what the Wifi Clock will do after you have completed this guide.

![](https://giant.gfycat.com/GorgeousGreatFluke.gif)

# Requirements

You first should have completed the **Hello World** guide so you know how to make an LED light up.

# Setup

After opening the Arduino IDE, click **File**, then **New**. This should create a new window of the IDE. In this window, select **File**, then **Save As**. This should bring up a new window in the Arduino folder. If it does not, navigate there. Name the file something descriptive such as **Buttons**, then click **Save**.

Also make sure the correct port is selected by selecting **Tools** from the top menu, then **Port**.

# Writing the code

We first need to declare two variables; one for the red LED and one for the **Mode** button. Before the `setup()` function, add these lines of code:

```c
const int MODE = 12;
const int RLED = 0;
```
&nbsp;
Next we must tell the microcontroller that we want to use these two pins. Like in the previous guide, the red LED will need to be output. Since we want constantly check if the **Mode** button is pressed, we want it to be an input. Specifically, we want it to be an input with a pull-up resistor (there are technical reasons for this that this guide will not go into). To set these pins correctly, type in the following code in the `setup()` function:

```c
pinMode(RLED, OUTPUT);
pinMode(MODE, INPUT_PULLUP);
```
&nbsp;
Now that we have our pins declared, we want to tell the microcontroller what to do. We want it to continuously find out if the button is pushed. We then want to output this state to an LED. To do this, type the following code in the **loop()** function.

```c
int state = digitalRead(MODE);
digitalWrite(RLED, !state);
```
&nbsp;
This code uses the **digitalRead()** function, which reads the state of a pin, and stores the result in a variable. If the button is pushed, that variable *state* will be a 0. If it is not pushed, *state* will be a 1. After the state of the button has been read, the program will output the *state* variable to the LED. Since the button is backwards from what you would normally think, we add a **!** before the variable *state*. This means that if *state* is 1, the LED will get a 0, or be off. If *state* is 0, the LED will get a 1, or be on. 

Now that we have written all of the code, we need to upload it to the board. First, save the file. Then upload the code by pressing the right-pointing arrow above the name of the file. This will upload the code to the board and run it.

If you get an error after uploading the code, you can reference the code below.

```c
const int MODE = 12;
const int RLED = 0;

void setup() {
  pinMode(RLED, OUTPUT);
  pinMode(MODE, INPUT_PULLUP);
}

void loop() {
  int state = digitalRead(MODE);
  digitalWrite(RLED, !state);
}
```

# Congratulations!

You now have written a program that is able to take in some input, and produce some output based on it. This will be used in almost every program from here on out.

# Bonus

See if you can get the other buttons to work with the other LEDs like we did with the **Mode** button and red LED. For reference, the pin numbers for the **Incr** button, **Decr** button, green LED, and blue LED are 10, 2, 4, and 5 respectively. A GIF demonstrating this can be seen below.

![](https://giant.gfycat.com/FarawayWellwornChihuahua.gif)