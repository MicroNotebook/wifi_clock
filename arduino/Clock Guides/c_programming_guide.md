# Background
The purpose of this guide is to serve as a reference for programming in C. This guide will not cover everything in C, but simply some basics. You can come to this guide whenever you are confused by something in other guides, or want to know more about C.

# Variables
Variables in C are like variables in math. They are simply a name or letter that represents something else. They can be used to represent numbers, characters, places in memory, or any other type in C. There are some rules to the naming of variables in C. All variables in C must begin with a letter or an underscore (**_**). The only characters allowed in variable names are numbers, letters (both upper and lower case), and underscores. Variables are case sensitive, so you could have two separate variables with the same name, but one is all lowercase letters, and one is all uppercase letters. Variables can not have the same name as a reserved name or function name. Below are some examples.

Valid Examples:
- a
- num
- _num
- NUM
- myVar
- my_Var2

Invalid Examples:
- 2var
- my num
- new*var
- printf
- case


# Types
C is a weakly typed language, meaning you must give types to all of your variables when you initialize them. The basic C types are **char**, **int**, and **float**.

A **char** is simply a character, such as a letter or number, however there are also special characters such as the newline and null characters. Characters are specified by single quotes (see examples below). They also can be specified by the number of the character according to the [ASCII table](http://www.asciitable.com/). Variables initialized by `char` are "signed" meaning the can be represented by both positive and negative numbers. If we want to initialize a character, but we don't care about the sign, we can initialize it as `unsigned char`.  All of the below variables will hold the same character.

```c
char firstA = 'a';
char secondA = 97;
unsigned char thirdA = 97;
```
&nbsp;
An **int** is an integer, or whole, number. You can try assigning a fractional number to an integer variable, but the C compiler will only assign the whole number part to the variable. Like characters, integers can be both signed or unsigned. In addition to this, integers can be either "short" or "long." As the names imply, shorts can hold smaller numbers than longs. Both shorts and longs can be signed or unsigned. Below are some examples of integers. All variables below will hold the same value.

```c
int a = 5;
unsigned int b = 5.5;
short c = 5;
long d = 5.0;
```
&nbsp;
A **float** is a decimal number and is always signed. Like integers, floats can be longs; however, long floats are called **double**. There are also long doubles that hold even more data than doubles. Below are some examples of initializing floats. The below variables do **not** hold the same values.

```c
float a = -10.52;
double b = 781.15828592;
long double c = -1.33525;
```
&nbsp;
If you know the value of a certain variable won't change, you can add the keyword `const` when initializing it. When initializing a variable with the `const` keyword you must specify the value. You can declare a variable as constant for any of the types mentioned above. Below are some examples of constant variables.

```c
const int a = 10;
const long double b = 5.251522159001;
const unsigned char c = 92;
```

# Comments
Comments are a way to make the code more readable to humans and are denoted by either **//** for a single-line comment, or **/\*** and **\*/** for a multi-line comment. For single line comments, everything after the **//** is ignored. For multi-line comments, everything between the **/\*** and **\*/** is ignored. Comments are completely ignored by the C compiler, meaning you can type anything and your code will still work. Comments are often used when debugging your programs since you can quickly stop the line from functioning while still having it there. Below are some examples.

```c
//This is a comment
/*This is a multiline comment on one line.*/
/*
This is
a multiline comment
on many lines.
*/

// The comment on the next line shows the result
int a = 5 + 10;		// a = 15

// The following code has been commented out for debugging purposes
//int b = 6 - a;

// All of the following code will be ignored
/*
int c = 10;
float d = 6.5;
float e = c * d;
*/
```

# Mathematical Operations
Math operations in C are as simple as to do as typing them into a calculator.  You can do addition, subtraction, multiplication, and division on regular numbers, as well as variables. C is also smart enough to recognize and apply order of operations. For a full list of operator precedence, see the table [here](https://www.tutorialspoint.com/cprogramming/c_operators_precedence.htm). With the exception of division, these operators work as expected for all types. Below are some examples.

```c
int a = 5;
float b = 2.5;

float w = a + b;		// w = 7.5
int x = a - 9;			// x = -4
float y = a * b;		// y = 12.5
float z = (6 + b) * a;	// z = 42.5
```
&nbsp;
Division is different in the fact that there are two types of division; integer division and float division. As the names imply, integer division is between two integers, while float division is between any other two types. Float division works as you would expect division to normally work (the result can be a number with a decimal place). Integer division does not work like this; the result must be an integer. This means that if we divide 6 by 4, the result is 1. Essentially, it just returns the whole number answer. If we want the remainder from this division, we can use the modulus operator (**%**). If we then did **6 % 4**, the result would be 2, since 4 goes into 6 once, and then there is a remainder of 4. Below are some examples.

```c
int a = 5 / 2;		// a = 2
int b = 5 % 2;		// b = 1
float c = 5.0 / 2;	// c = 2.5
int d = a / c;		// d = 0
```
&nbsp;
In addition to the basic operators, C also has a few shortcuts that make typing easier. If you want to add or subtract one from a variable, you can use the `++` or `--` operators. These symbols go before or after the variable name (see examples below). If you want the addition or subtraction to occur before other operations, you put the symbol before the variable name. If you want the addition or subtraction to occur after the variable has been evaluated, you put the symbol after the variable name.

```c
int i = 5;
int a = 10 + ++i;	// a = 16, i = 6
int b = 4 + i--;	// b = 10, i = 5
b++;				// b = 11
--a;				// a = 15
```
&nbsp;
Another type of shortcut can be used if we want to update a variable. For example, look at the code below.

```c
int a = 5;
a += 9;			// a = 14
```
The second line of this code is the same as `a = a + 9`. This type of shortcut can be used with any other mathematical operator, such as multiplication, division, and subtraction.

# Logical and Comparison Operators
In addition to mathematical operators, C has certain logical and comparison operators that determine if something is **true** or **false**. In C, the number **0** is considered **false** and every other number is considered true. If a logical is evaluated and determined to be **true**, C returns a **1**. 

The comparison operators are in the table below. Notice that the **Equal To** operator is two equal signs. This is different than the assignment operator (**=**) that is used to give a value to a variable.
| Operator | Explanation |
|:-----:| ----- |
| > | Greater Than |
| < | Less Than |
| == | Equal To |
| >= | Greater Than or Equal To |
| <= | Less Than or Equal To |

It is important to note that chaining together groups of operators does not work in C like it works in mathematics. For instance, in the code `5 < x < 10`, if `x = 11`, the statement would be **true**, and thus return **1**. This is because the statement would be evaluated left to right, so `5 < x` would be evaluated first. Since 5 is less than 9, **1** would be returned. Then, `1 < 10` would be evaluated, which is **true**, and so **1** would be returned. For more examples, see the code below.

```c
int a = 15;
int b = 3;
int c = a == b;					// c = 0
int d = (a - b) >= 12 == 1;		// d = 1
```
&nbsp;
The logical operators are listed in the table below. The logical AND operator returns a **1** only if both numbers on either side of it are not **0**, otherwise it returns a **0**. The logical OR operator returns a **1** if either number is not **0**, otherwise it returns a **0**. The logical NOT operator is slightly different in that it only has one operand. The operator goes in front of the variable or value it will negate and returns whatever the value isn't. In other words, if the number is **0**, it returns a **1**, otherwise, it returns a **0**.
| Operator | Explanation |
|:-----:| ----- |
| && | Logical AND |
| \|\| | Logical OR |
| ! | Logical NOT |

The order of operations for logical operators is slightly strange. Logical NOT takes precedence since it only has one operator. The next highest is logical AND, followed by logical OR. By following this order, we can see that the last example below evaluates to **0**. First, **b** is negated, so we're left with **1 && 0**, which evaluates to **0**. Next we have **b || 0**, and since **b** is **0**, we see that **e** will be **0**.

```c
int a = 15;
int b = !a;				// b = 0
int c = b && a;			// c = 0
int d = c || a;			// d = 1
int e = b || !b && 0;	// e = 0
```

# Arrays
Arrays in C are lists of variables of the same type. To initialize an array, you must know the type of variable you want, as well as the number of elements in the array you can have. You can have arrays of any type. You can access the individual elements in the array by putting the number of the element in brackets after the name of the array (see examples below). It should be noted that the index of the first element in an array is 0, and the last element of the array is indexed by the length of the array minus 1. Below are some examples of initializing and using arrays.

```c
int arr[5] = {9, 8, 7, 6, 5};	// initializes and array where we know the elements ahead of time
int arr2[5];					// initializes an empty array
arr2[0] = 4;					// stores 4 in the first position of the array
arr2[1] = 18;					// stores 18 in the index 1 of the array
arr2[2] = arr[0] + arr[4];		// stores 9 + 5 = 14 in the third element of the array
arr2[3] = arr2[2] + arr[2];		// stores 14 + 7 = 21 in index 3 of the array
```

# If Statements
Often times in programming we want things to happen, only if something else has happened. To do this, we use **if** statements. These work by checking if a certain condition is true. If it is, the code inside the **if** statement is run. If not, the next condition will be checked if there is an **else if** statement. If this is not true, then the code will keep checking until there is either an **else** statement, or nothing. If there is an else statement, it acts as a default. If there is no **else**, then the code will keep going. Below are a few examples.
```c
int a = 5;
int b = 3;
int c = -10;

if (a > b + c) {	// this will be false (5 > 3 + (-10))
	a = 0;			// this will not be run, so a is still 5
}

if (c > a) {		// this will be false (-10 > 5)
	a = 0;			// this will not be run
} else if (c > b) {	// this will be false (-10 > 3)
	b = 0;			// this will not be run
} else {			// since the other two have failed, this will be run
	c = 0;			// this will be run
}

if (a > c) {		// this will be true (5 > 0)
	a += 5;			// this will run, so a = 10
} else {			// since the if statement was true, this will not be run
	a = 0;			// this will not be run
}
```

# Loops
There are 3 types of loops in C: **while**, **do... while**, and **for**.

The easiest loops to use are **for** loops. Often times they are used for counters. The first part of a **for** loop is used for initialization of any variables. The second part is the condition when the loop ends. The last part of the loop is the update condition. Below is an example of a for loop that does nothing but count from 0 to 9.

```c
for (int i = 0; i < 10; i++) {

}
```
&nbsp;
If you want to do something repeatedly until a condition is met you should use a **while** loop. These only have a field where an exit condition is met. These can be used like **for** loops, as in the example below.

```c
int i = 0;
while (i < 10) {

	i++;
}
```
&nbsp;
The final kind of loop is a **do... while** loop. These are used if you want to do a loop at least once. They are useful when you want to do error checking or get user input. The code inside the loop will be iterated through once, then the exit condition is checked. If the condition has not been met yet, the code will be repeated. Below is an example.

```c
int i = 10;
int a = 1;
do {
	a *= i;
} while (a < 100);
```

# Functions
Functions are bundles of code that allow the programmer to abstract things away and make the code more readable. The first line of the function is the function definition. This tells the programmer and computer what the name of the function is, what the return value is, and what parameters the function needs to work. After this, the code that will be executed when the function is called is written. Below is a simple example of a function that adds 5 to a number.

```c
double add5(double x)
{
	return x + 5;
}
```
&nbsp;
In the above example, the return statement is what the function returns when it is called. Below is an example using the simple **add5** function.

```c
double a = 10.0;
double b = add5(a);		// b = 15
double c = add5(a);		// c = 15
double d = add5(b + c);	// d = 35, since b + c + 5 = 35
```
&nbsp;
As you can see from the last example, you can do other operations inside the parentheses for the function. This will be evaluated before the function does anything with the number passed to it. Another thing to point out from the above example is that we passed in a double. It is important to pass in a number or variable of the type the function expects, otherwise errors could result.

The previous example had a return type of **double**; however, not all functions will return something. When this happens, the return type is **void**. This can also be used when a function does not take in any parameters. Below are two examples that use the **void** type.

```c
int get5(void)
{
	return 5;
}

void printHi(void)
{
	printf("Hi\n");		// this assumes stdio.h is included
}
```

# Libraries
Libraries are files that contain code that often works together to serve one purpose. Often, libraries have optimized code for doing basic things. These files often have two parts, the .c file that contains the code for the functions, and the .h header file. When including libraries, we include the .h file. A few common libraries in C are *stdio.h*, *stdlib.h*, and *math.h*. These statements usually are the first lines of a C file. Below is an example on how to include libraries in your program.

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
```

# Define Statements
To make code easy to read and change, sometimes we want a variable to actually be constant. This can be achieved with **define** statements. These allow the programmer to give a word a value that cannot change. Often, these constants are in all capitol letters. If we have a long program and have some value entered many places, instead of changing each of those places, we can change the parameter once. These statements often are at the top of a file after libraries are included. Below are examples of define statements.

```c
#define ITERATIONS 10
#define TIME 5
```

# Advanced Mathematical Operations
C does not have any operators for more complex mathematical operations built in. If we want to use trigonometric functions or exponents we must use the *math.h* library. Below is a table of the function definitions for some of the most common functions in this library.

| Function Prototype | Explanation |
| ----------------------- | ----------------------- | 
|double cos(double x) | Returns the cosine of an angle in radians. |
| double sin(double x) | Returns the sine of an angle in radians. |
| double exp(double x) | Returns Euler's number raised to **x**. |
| double pow(double x, double y) | Returns **x** raised to the power **y**. |
| double fabs(double x) | Returns the absolute value of **x**. |
| double ceil(double x) | Returns **x** rounded up to the nearest integer. |
| double floor(double x) | Returns **x** rounded down to the nearest integer. |