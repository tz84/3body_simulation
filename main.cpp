#include<iostream>
#include<cmath> 
#include<random> 
#include<vector> 

using namespace std; 

double GRAVITATIONAL_CONSTANT = 6.67430 * pow(10, -11); 

    // random number generator 
default_random_engine generator(random_device{}()); 

double lowerBoundMass = 0; 
double upperBoundMass = 1; 

double lowerBoundPosition = 0; 
double upperBoundPosition = 1; 

double lowerBoundVelocity = 0; 
double upperBoundVelocity = 1; 
// range distributor for initial values of mass, position and velocity of planet 
uniform_real_distribution<double> massDistribution(lowerBoundMass, upperBoundMass);
uniform_real_distribution<double> positionDistribution(lowerBoundPosition, upperBoundPosition);
uniform_real_distribution<double> velocityDistribution(lowerBoundVelocity, upperBoundVelocity);

double dt = 1; 

// array storing created planets 
vector<Planet> planets(3); 

int main (){
/*
------------------
GLOBAL VARIABLES  |
------------------

double gravitationalConstant (universal gravitational constant)

range massRange (the range for a planets possible mass)
range positionRange (the range for a planets possible initial position)
range velocityRange (the range for a planets possible initial velocity)

array (of type Planet) Planets (stores all created planet objects for current simulatoin)

double dt (the difference in time between velocity and position updates of planets )


---------
CLASSES  |
---------

class Planet {

    double mass 
    vector position 
    vector velocity 

    constructor {

        this.mass = number within massRange 
        this.position = vector within positionRange 
        this.velocity = vector within velocityRange 
    
    }

}

----------
FUNCTIONS |
----------


summation { // finds net acceleration on each planet 
    i and j = 0 
    array accelerations (corresponding to Planets array)

    for planet i in Planets {
        if (collisionChecker()) {
            break; (end simulation!)
        } else {
            while (j < Planets.size) {
                if ( j == i ) {
                    continue; 
                } else {
                    a = FORMULA 
                    add a to accelerations
                }
            }
        }

    return accelerations
    }
}

solver { // reiman solver 

    for planet in Planets {
        planet.velocity += accelerations[correspondingIndex] * dt 
        planet.position += planet.velocity * dt (is this correct for a reiman approximation?)
    }

}

populate { // starts the simulation by creating 3 planet objects 

}


-----------------------
MAIN PROGRAM STRUCTURE |
-----------------------

main {
    populate()

    // for every unit of time dt run
    summation()
    solver()

    
}

*/





}