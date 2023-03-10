#include <myFunctions.h>
#include <myClasses.h>

using namespace std;

/*  define a function to calculate the change inx and y distances, consequently the distance between two bodies given a vector of bodies and return the difference in distances
    inputs:
    1. vector<BodiesStruct>& bodyVector: vector of BodiesStruct
    2. i: an index
    3. j: an index
    4. kFactor: the corresponding kFactor of Runge-Kutta 4th order
    5. xDiff: difference in x
    6. yDiff: difference in x
*/
void computeDistance(std::vector<BodiesStruct>& bodyVector, int i, int j, int kFactor, double& xDiff, double& yDiff, double& dij) {
    // if kFactor is 1, then calculate the difference in x and y distances and carry on till all four kFactors have been found
    if (kFactor == 1) {
        xDiff = bodyVector[i].dispX.actualVal - bodyVector[j].dispX.actualVal;
        yDiff = bodyVector[i].dispY.actualVal - bodyVector[j].dispY.actualVal;
    }
    else if (kFactor == 2) {
        xDiff = (bodyVector[i].dispX.actualVal + 0.5 * bodyVector[i].dispX.k1) - (bodyVector[j].dispX.actualVal + 0.5 * bodyVector[j].dispX.k1);
        yDiff = (bodyVector[i].dispY.actualVal + 0.5 * bodyVector[i].dispY.k1) - (bodyVector[j].dispY.actualVal + 0.5 * bodyVector[j].dispY.k1);
    }
    else if (kFactor == 3) {
        xDiff = (bodyVector[i].dispX.actualVal + 0.5 * bodyVector[i].dispX.k2) - (bodyVector[j].dispX.actualVal + 0.5 * bodyVector[j].dispX.k2);
        yDiff = (bodyVector[i].dispY.actualVal + 0.5 * bodyVector[i].dispY.k2) - (bodyVector[j].dispY.actualVal + 0.5 * bodyVector[j].dispY.k2);
    }
    else if (kFactor == 4) {
        xDiff = (bodyVector[i].dispX.actualVal + bodyVector[i].dispX.k3) - (bodyVector[j].dispX.actualVal + bodyVector[j].dispX.k3);
        yDiff = (bodyVector[i].dispY.actualVal + bodyVector[i].dispY.k3) - (bodyVector[j].dispY.actualVal + bodyVector[j].dispY.k3);
    }
    // calculate the difference in distance using Pythagoras
    dij = pow(xDiff, 2) + pow(yDiff, 2);
}

/*  define a function to calculate the displacements and velocity of the bodies using Runge-Kutta 4th Order method.
    The function takes in a vector of 'BodiesStructs' objects containing the displacements and velocities, alongside step size, G and kFactor
    inputs:
    1. bodyVector: a vector of 'BodiesStruct'
    2. dt: time step
    3. G: gravitational constant
    4. kFactor: k factor number (essentially which k factor is it)
*/
void findK(std::vector<BodiesStruct>& bodyVector, double dt, double G, int kFactor) {
    int numOfBodies = bodyVector.size(); // find the number of bodies by finding the size of the vector
    double xVal = {}, yVal = {}; // initialise x and y values
    // define a for-loop to iterate over each body in the vector
    for (int i = 0; i < numOfBodies; i++) {
        double xSum = {0}, ySum = {0}; // initilise the summation variables to store the sum of the forces that acts on the body
        // use a switch-case statement to find the displacements in x and y
        switch (kFactor) {
            // if kFactor is 1, i.e. k1 then find out x and y displacements then repeat for all four k factors
        case 1:
            bodyVector[i].dispX.k1 = bodyVector[i].velX.actualVal * dt;
            bodyVector[i].dispY.k1 = bodyVector[i].velY.actualVal * dt;
            break;
        case 2:
            bodyVector[i].dispX.k2 = (bodyVector[i].velX.actualVal + 0.5 * bodyVector[i].velX.k1) * dt;
            bodyVector[i].dispY.k2 = (bodyVector[i].velY.actualVal + 0.5 * bodyVector[i].velY.k1) * dt;
            break;
        case 3:
            bodyVector[i].dispX.k3 = (bodyVector[i].velX.actualVal + 0.5 * bodyVector[i].velX.k2) * dt;
            bodyVector[i].dispY.k3 = (bodyVector[i].velY.actualVal + 0.5 * bodyVector[i].velY.k2) * dt;
            break;
        case 4:
            bodyVector[i].dispX.k4 = (bodyVector[i].velX.actualVal + bodyVector[i].velX.k3) * dt;
            bodyVector[i].dispY.k4 = (bodyVector[i].velY.actualVal + bodyVector[i].velY.k3) * dt;
            break;
        }
        // define another for-loop to iterate over the number of bodies to find the foces acting on them
        for (int j = 0; j < numOfBodies; j++) {
            // if the body is the current body that's being iterated then continue
            if (j == i) {
                continue;
            }
            
            // otherwise, compute the x and y values
            else {
                // call computeDistance() to find the difference in x and y and the distance between the two bodies
                if (kFactor == 1) {
                    double xDiff = {}, yDiff = {}, dij = {};
                    computeDistance(bodyVector, i, j, kFactor, xDiff, yDiff, dij);
                    // use the values obtained through computeDistance() to find the forces acting on the body and repeat for all k factors
                    xVal = bodyVector[j].mass * (bodyVector[j].dispX.actualVal - bodyVector[i].dispX.actualVal) * (G * pow(dij, -1.5));
                    yVal = bodyVector[j].mass * (bodyVector[j].dispY.actualVal - bodyVector[i].dispY.actualVal) * (G * pow(dij, -1.5));
                }
                else if (kFactor == 2) {
                    double xDiff = {}, yDiff = {}, dij = {};
                    computeDistance(bodyVector, i, j, kFactor, xDiff, yDiff, dij);
                    xVal = bodyVector[j].mass * ((bodyVector[j].dispX.actualVal + 0.5 * bodyVector[j].dispX.k1) - (bodyVector[i].dispX.actualVal + 0.5 * bodyVector[i].dispX.k1)) * (G * pow(dij, -1.5));
                    yVal = bodyVector[j].mass * ((bodyVector[j].dispY.actualVal + 0.5 * bodyVector[j].dispY.k1) - (bodyVector[i].dispY.actualVal + 0.5 * bodyVector[i].dispY.k1)) * (G * pow(dij, -1.5));
                }
                else if (kFactor == 3) {
                    double xDiff = {}, yDiff = {}, dij = {};
                    computeDistance(bodyVector, i, j, kFactor, xDiff, yDiff, dij);
                    xVal = bodyVector[j].mass * ((bodyVector[j].dispX.actualVal + 0.5 * bodyVector[j].dispX.k2) - (bodyVector[i].dispX.actualVal + 0.5 * bodyVector[i].dispX.k2)) * (G * pow(dij, -1.5));
                    yVal = bodyVector[j].mass * ((bodyVector[j].dispY.actualVal + 0.5 * bodyVector[j].dispY.k2) - (bodyVector[i].dispY.actualVal + 0.5 * bodyVector[i].dispY.k2)) * (G * pow(dij, -1.5));
                }
                else if (kFactor == 4) {
                    double xDiff = {}, yDiff = {}, dij = {};
                    computeDistance(bodyVector, i, j, kFactor, xDiff, yDiff, dij);
                    xVal = bodyVector[j].mass * ((bodyVector[j].dispX.actualVal + bodyVector[j].dispX.k3) - (bodyVector[i].dispX.actualVal + bodyVector[i].dispX.k3)) * (G * pow(dij, -1.5));
                    yVal = bodyVector[j].mass * ((bodyVector[j].dispY.actualVal + bodyVector[j].dispY.k3) - (bodyVector[i].dispY.actualVal + bodyVector[i].dispY.k3)) * (G * pow(dij, -1.5));
                }
            }
            // add the x and y values to the corresponding summation variables
            xSum += xVal;
            ySum += yVal;
        }
        // find the x and y velocities for each k factor
        if (kFactor == 1) {
            bodyVector[i].velX.k1 = xSum * dt;
            bodyVector[i].velY.k1 = ySum * dt;
        }
        else if (kFactor == 2) {
            bodyVector[i].velX.k2 = xSum * dt;
            bodyVector[i].velY.k2 = ySum * dt;
        }
        else if (kFactor == 3) {
            bodyVector[i].velX.k3 = xSum * dt;
            bodyVector[i].velY.k3 = ySum * dt;
        }
        else if (kFactor == 4) {
            bodyVector[i].velX.k4 = xSum * dt;
            bodyVector[i].velY.k4 = ySum * dt;
        }
    }
}

int main() {
    // create a 'fReaderClass' object called 'readerObj'
    fReaderClass readerObj("parameters.txt");

    // read the file 'parameters.txt'
    readerObj.fRead();

    // extract using the getter functions and assign the constants from the file to variables to be used
    double G = readerObj.getG();
    double T = readerObj.getT();
    double dt = readerObj.getDt();
    std::vector<BodiesStruct> bodyVector = readerObj.getBody();

    // call findK() to update the displacements and velocities
    for (int k = 1; k <= 4; k++) {
        findK(bodyVector, dt, G, k);
    }

    // create a 'fWriterClass' object called 'writerObj'
    fWriterClass writerObj("output.txt");

    // write the data to the file
    writerObj.write(bodyVector, dt, G, T);

    return 0; // return success
}
