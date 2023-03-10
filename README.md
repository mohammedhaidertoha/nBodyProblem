# nBodyProblem
This program simulates the motion of multiple bodies under the influence of gravity using the Runge-Kutta 4th Order method.

### Table of Contents
- [Introduction](#introduction)
- [Libraries](#Libraries)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)

### Introduction
The program reads a file containing the initial position, velocity, and mass of each body as well as the gravitational constant G, the total time T to simulate, and the time step dt. The file format is as follows:

```
G T dt
x1 y1 vx1 vy1 m1
x2 y2 vx2 vy2 m2
...
xn yn vxn vyn mn
```
where G, T, and dt are floating-point numbers, and the rest of the values are double-precision floating-point numbers.

The program then simulates the motion of the bodies over the specified time period and time step using the Runge-Kutta 4th Order method, and outputs the position and velocity of each body at each time step to the console.

### C++ Libraries
The program is written in C++, and uses the following libraries:

```C++
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>
```

### Installation
To use this program, please follow these steps:

Clone this repository.
Compile the source code using a C++ compiler.
Create a file with the format specified in the introduction.
Run the compiled executable with the file as input.

### Usage
To use this program, run the compiled executable with the file containing the input data as a command line argument:

```bash
./nbody filename.txt
```
where filename.txt is the path to the input file.

The program will output the position and velocity of each body at each time step to the console.

### License
This project is licensed under the MIT License. See the [License](https://opensource.org/licenses/MIT) file for details.
