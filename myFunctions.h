#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>


// define a struct to store the properties of each body, where actuaVal is the value of the variable and k factors of the Runge-Kutta 4th Order method
struct PropertiesStruct {
    double actualVal = {}, k1 = {}, k2 = {}, k3 = {}, k4 = {};
};

// define a struct to store each body's displacement, velocity and mass
struct BodiesStruct {
    PropertiesStruct dispX = {}, dispY = {}, velX = {}, velY = {};
    double mass = {};
};


// function declarations
void computeDistance(std::vector<BodiesStruct>& bodyVector, int i, int j, int kFactor, double& xDiff, double& yDiff, double& dij);
void findK(std::vector<BodiesStruct>& bodyVector, double dt, double G, int kFactor);

#endif
