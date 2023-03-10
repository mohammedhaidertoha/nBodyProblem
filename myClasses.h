#ifndef MYCLASSES_H
#define MYCLASSES_H

// declare a 'fReaderClass' class to read a file and store it's contents into a vector
class fReaderClass {
private:
    std::vector<BodiesStruct> bodyVector = {}; // define a vector of type 'BodiesStruct'
    std::string fName_in = {}; // name of the file to be read
    double G = {}, T = {}, dt = {}; // initilise the constant variables
public:
    // declare a constructor that takes in a string 'fName' and assigns it to the class variable 'fName'
    fReaderClass(std::string fName_in) :fName_in(fName_in) { /*nothing to do*/ }
    // declare a function 'fRead' to read the file and store the values in a vector
    void fRead() {
        std::ifstream fIn(fName_in); // open the file using 'ifstream'
        std::string line = {}; // to store the values of each line
        int counter = { 0 }; // initialise a counter
        while (std::getline(fIn, line)) {
            counter++; // increment counter before the loop such that it's current value is 1 corresponding to line 1
            std::vector<double> contents;
            std::string lineChar; // declare a string 'lineChar' to store the individual characters of the line
            // declare a for-loop to iterate through each character of the line
            for (unsigned int i = 0; i < line.length(); i++) {
                // if character is not a space then add to the string variable
                if (line[i] != ' ') {
                    lineChar += line[i];
                }
                // however, if character is a space then 'lineChar' is converted to a double and then it is stored in the vector defined earlier
                else {
                    contents.push_back(std::stod(lineChar));
                    lineChar = ""; // 'lineChar' is reset to an empty string
                }
            }
            // if the counter is 1 i.e. if it is reading the first line, then the values stored in the vector are assigned to the variables
            contents.push_back(std::stod(lineChar));
            if (counter == 1) {
                G = contents[0];
                T = contents[1];
                dt = contents[2];
				
				// throw errors for invalid parameters
				if (G<=0 || T<=0 || dt<=0){
					throw std::logic_error("G, T and dt must all be greater than 0");
				}
				else if (dt>T) {
					throw std::logic_error("dt cannot be greater than T");
				}
            }
            // however, if it is not the first line then, create an object of the 'BodiesStruct' then push back the data stored in 'contents' to 'bodyVector'
            else {
                BodiesStruct bObj; // bObj is an object of 'BodiesStruct'
                bObj.dispX.actualVal = contents[0];
                bObj.dispY.actualVal = contents[1];
                bObj.velX.actualVal = contents[2];
                bObj.velY.actualVal = contents[3];
                bObj.mass = contents[4];
                bodyVector.push_back(bObj);
            }
        }
    }
    // define getter functions to return the corresponding values of varibles/vector
    double getG() { return G; }
    double getT() { return T; }
    double getDt() { return dt; }
    std::vector<BodiesStruct>getBody() { return bodyVector; }
};

// declare a 'fWriterClass' to write data to a file
class fWriterClass {
public:
    // define a constructor that takes in a string as the name of the file
    fWriterClass(std::string fName_out) {
        fOut.open(fName_out); // open the file
        fOut << std::left << std::setprecision(5); // set the precision to 10 sf
    }
    /* define a function that takes in a vector of 'BodiesStructs' objects, time step, G and final time to write the distances and velocities to a file
    inputs:
    1. bodyVector: a vector of 'BodiesStruct'
    2. dt: time step
    3. G: gravitational constant
    4. T: the final time
*/
    void write(std::vector<BodiesStruct>& bodyVector, double dt, double G, double T) {
        int numOfBodies = bodyVector.size(); // find the number of bodies by finding the size of the vector
        double iterations = T / dt; // find the number of iterations
        // define a for-loop to iterate through the vector then write the displacements of x and y of each body to the file
        for (int i = 0; i < numOfBodies; i++) {
            fOut << std::setw(15) << bodyVector[i].dispX.actualVal;
            fOut << std::setw(15) << bodyVector[i].dispY.actualVal; 
        }
        fOut << std::endl;
        // another loop to iterate over the number of iterations or iterations
        for (int counter = 0; counter < iterations; counter++) {
            // if there is only one body then displacements are calculated by multiplying the velocities by dt and adding on
            if (numOfBodies == 1) {
                bodyVector[0].dispX.actualVal += bodyVector[0].velX.actualVal * dt;
                bodyVector[0].dispY.actualVal += bodyVector[0].velY.actualVal * dt;
            }
            // otherwise, call the findK() four times since there are four k factors
            else {
                for (int step = 1; step <= 4; step++) {
                    findK(bodyVector, dt, G, step);
                }
                // compute the corresponding displacements and velocities
                for (int i = 0; i < numOfBodies; i++) {
                    bodyVector[i].dispX.actualVal = (bodyVector[i].dispX.actualVal + (1.0/ 6.0) * (bodyVector[i].dispX.k1 + 2 * bodyVector[i].dispX.k2 + 2 * bodyVector[i].dispX.k3 + bodyVector[i].dispX.k4));
                    bodyVector[i].dispY.actualVal = (bodyVector[i].dispY.actualVal + (1.0 / 6.0) * (bodyVector[i].dispY.k1 + 2 * bodyVector[i].dispY.k2 + 2 * bodyVector[i].dispY.k3 + bodyVector[i].dispY.k4));
                    bodyVector[i].velX.actualVal = (bodyVector[i].velX.actualVal + (1.0 / 6.0) * (bodyVector[i].velX.k1 + 2 * bodyVector[i].velX.k2 + 2 * bodyVector[i].velX.k3 + bodyVector[i].velX.k4));
                    bodyVector[i].velY.actualVal = (bodyVector[i].velY.actualVal + (1.0 / 6.0) * (bodyVector[i].velY.k1 + 2 * bodyVector[i].velY.k2 + 2 * bodyVector[i].velY.k3 + bodyVector[i].velY.k4));
                }
            }
            // write the new values to the file
            for (int i = 0; i < numOfBodies; i++) {
                fOut << std::setw(15) << bodyVector[i].dispX.actualVal;
                fOut << std::setw(15) << bodyVector[i].dispY.actualVal; 
                fOut << std::setw(15) << bodyVector[i].velX.actualVal; 
                fOut << std::setw(15) << bodyVector[i].velY.actualVal;
            }
            fOut << std::endl;
        }
    }
    // the destructor closes the file
    ~fWriterClass() {
        fOut.close();
    }
private:
    std::ofstream fOut;
};

#endif
