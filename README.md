# nBodyProblem
This program simulates the motion of multiple bodies under the influence of gravity using the Runge-Kutta 4th Order method.

### Table of Contents
- [Introduction](#introduction)
- [Technologies](#technologies)
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
