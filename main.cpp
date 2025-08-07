#include "simulation.h"

float GRAVITATIONAL_CONSTANT = 6.67430 * pow(10, -11); 
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
uniform_real_distribution<float> massDistribution(lowerBoundMass, upperBoundMass);
uniform_real_distribution<float> radiusDistribution(lowerBoundRadius, upperBoundRadius);
uniform_real_distribution<float> positionDistribution(lowerBoundPosition, upperBoundPosition);
uniform_real_distribution<float> velocityDistribution(lowerBoundVelocity, upperBoundVelocity);

float dt = 1.0f; 

class Planet {
public: 
    float mass;
    float radius; 

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
vector<Planet> planets; 

vector<glm::vec3> summation (){

    vector<glm::vec3> accelerations(planets.size()); 

    for (int i = 0; i < planets.size(); i ++) {
        glm::vec3 currentAccel(0,0,0); 
        for (int j = 0; j < planets.size(); j++) {
            if (i==j) {
                continue;
            } else {
                if (collisionChecker(planets[i], planets[j])) {
                    endSimulation = true;
                } else {
                    glm::vec3 vector = planets[j].position - planets[i].position; 
                    float vector_magnitude = glm::length(vector); 
                    currentAccel += GRAVITATIONAL_CONSTANT * planets[j].mass * vector / pow(vector_magnitude,3); 
                }
            }
        }
        accelerations[i] = currentAccel; 
    }
    return accelerations; 
}

void solver () {
    vector<glm::vec3> accelerations = summation(); 
    for (int i = 0; i < planets.size(); i++) {
        planets[i].velocity += accelerations[i] * dt; 
        planets[i].position += planets[i].velocity * dt; 
    }
}

bool collisionChecker(Planet planet1, Planet planet2){

    double distance = glm::length(planet1.position - planet2.position); 

    // get sum of radisu of planets 
    double radiusSum = planet1.radius + planet2.radius; 

    // if distance < sum return true 
    return distance < radiusSum;
}

void populate (vector<Planet>& vector, int num) {
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
        std::this_thread::sleep_for(std::chrono::milliseconds((int)dt)); 
    }
    
}
