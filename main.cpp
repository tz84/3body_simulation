#include "simulation.h"

double GRAVITATIONAL_CONSTANT = 6.67430 * pow(10, -11); 
bool endSimulation = false; 

// random number generator 
default_random_engine generator(random_device{}()); 

double lowerBoundMass = 0; 
double upperBoundMass = 1; 

double lowerBoundRadius = 0; 
double upperBoundRadius = 1; 

double lowerBoundPosition = 0; 
double upperBoundPosition = 1; 

double lowerBoundVelocity = 0; 
double upperBoundVelocity = 1; 

// range distributor for initial values of mass, position and velocity of planet 
uniform_real_distribution<double> massDistribution(lowerBoundMass, upperBoundMass);
uniform_real_distribution<double> radiusDistribution(lowerBoundRadius, upperBoundRadius);
uniform_real_distribution<double> positionDistribution(lowerBoundPosition, upperBoundPosition);
uniform_real_distribution<double> velocityDistribution(lowerBoundVelocity, upperBoundVelocity);

int dt = 1; 

class Planet {
public: 
    double mass;
    double radius; 

    glm::vec3 position; 
    glm::vec3 velocity; 

    Planet() {
        mass = massDistribution(generator); 
        radius = radiusDistribution(generator); 

        position = glm::vec3 ( 
            positionDistribution(generator),
            positionDistribution(generator),
            positionDistribution(generator)); 

        velocity = glm::vec3 ( 
            velocityDistribution(generator),
            velocityDistribution(generator),
            velocityDistribution(generator)); 
    };
}; 

// array storing created planets 
vector<Planet> planets(3); 

vector<glm::vec3> summation (){

    vector<glm::vec3> accelerations(3); 

    for (int i = 0; i < planets.size(); i ++) {
        glm::vec3 currentAccel(0,0,0); 
        for (int j = 0; j < planets.size(); j++) {
            if (i==j) {
                continue;
            } else {
                if (collisionChecker(planets[i], planets[j])) {
                    endSimulation = true;
                } else {
                    currentAccel += GRAVITATIONAL_CONSTANT * 
                    ((planets[i].position - planets[j].position) / 
                    pow(planets[i].position - planets[j].position,3));  // MAGNITUDE TO POWER OF 3 --> BUILT IN FUNCTION? 
                }
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
        i++; 
    }
}

bool collisionChecker(Planet planet1, Planet planet2){

    // get distance between planets 
    double distancex = abs(planet1.position.x - planet2.position.x); 
    double distancey = abs(planet1.position.y - planet2.position.y);
    double distancez = abs(planet1.position.z - planet2.position.z);

    glm::vec3 vector(distancex, distancey, distancez); 

    double distance = glm::length(vector); 

    // get sum of radisu of planets 
    double radiusSum = planet1.radius + planet2.radius; 

    // if distance < sum return true 
    return distance < radiusSum;
}

void populate (vector<Planet> vector, int num) {
    int i = 0; 
    while (i < num) {
        Planet planet; 
        vector.push_back(planet); 
        i++; 
    }
}

int main (){
    populate(planets, 3); 

    while (!endSimulation) {
        solver(); 
        std::this_thread::sleep_for(std::chrono::milliseconds(dt)); 
    }
    
}
