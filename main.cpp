#include "simulation.h"

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

class Planet {
    double mass;
    glm::vec3 position; 
    glm::vec3 velocity; 

    Planet() {
        mass = massDistribution(generator); 

        position = glm::vec3 ( 
            positionDistribution(generator),
            positionDistribution(generator),
            positionDistribution(generator)); 

        velocity = glm::vec3 ( 
            velocityDistribution(generator),
            velocityDistribution(generator),
            velocityDistribution(generator)); 
    }
}; 

vector<glm::Vec3> summation (){

    vector<glm::vec3> accelerations(3); 
    
    int currentAccel; 

    for (int i = 0; i < planets.size(); i ++) {
        currentAccel = 0; 
        for (int j = 0; j < planets.size(); j++) {
            if (i==j) {
                continue;
            } else {
                currentAccel += GRAVITATIONAL_CONSTANT * 
                ((planets[i].pos - planets[j].pos) / 
                pow(planets[i].pos - planets[j].pos,3));  // MAGNITUDE TO POWER OF 3 --> BUILT IN FUNCTION? 
            }
        }
        accelerations[i] = currentAccel; 
    }
    return accelerations; 
}

void solver () {
    vector<glm::vec3> accelerations = summation(); 
    int i = 0; 
    for (Planet planet : planets) {
        // is this correct and does this work for vec3 datatype? 
        planet.velocity += accelerations[i] * dt; 
        planet.position += planet.velocity[i] * dt; 
    }
}

bool collisionChecker(){
    // add logic for collision checking (sum of radius between any two planets less than distance between )

    return true; 
}

void populate (vector<Planet> vector, int num) {
    int i = 0; 
    while (i < num) {
        Planet planet(); 
        vector.add(planet); 
        i++; 
    }
}



int main (){
    populate(planets, 3); 

    // for every unit dt run... 
    solver(); 
}
