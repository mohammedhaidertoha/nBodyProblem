# nBodyProblem
This program simulates the motion of multiple bodies under the influence of gravity using the Runge-Kutta 4th Order method.

### Table of Contents
- [Introduction](#introduction)
- [C++ Libraries](#C++ Libraries)
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
