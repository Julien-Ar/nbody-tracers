#include "particle.h"
#include <math.h>

Particle::Particle(){
    x  = 0,  y  = 0, z  = 0;
    vx = 0,  vy = 0, vz = 0;
    ax = 0,  ay = 0, az = 0;
    mass = 0;
    isTracer = 1;
};

Particle::Particle(double x1, double y1 , double z1, 
                double vx1, double vy1, double vz1, 
                double ax1, double ay1, double az1,
                float mass1, bool isTracer1){
    
    x  = x1,   y  = y1,   z  = z1;
    vx = vx1,  vy = vy1,  vz = vz1;
    ax = ax1,  ay = ay1,  az = az1;
    mass = mass1;
    isTracer = isTracer1;
};

void Particle::computeAcceleration(Particle p1 , double G){
    // We compute the acceleration on the current particle object
    // caused by Particle p1
    double dx = x - p1.x;
    double dy = y - p1.y;
    double dz = z - p1.z;
    double mass = p1.mass;
    double distance = sqrt(dx*dx + dy*dy + dz*dz) ;
    double F = G*mass/(distance*distance); // Force intensity

    // dx/distance, dy/distance dz/distance are the components
    // of the unit vector in the direction of p1 ----> current particle 
    ax += -F*dx/distance;   
    ay += -F*dy/distance;
    az += -F*dz/distance;
};

void Particle::computePosition(double dt){
    // Leap-Frog integration scheme, conserve the energy
    vx = vx + ax*dt;
    vy = vy + ay*dt;
    vz = vz + az*dt;

    x = x + vx*dt;
    y = y + vy*dt;
    z = z + vz*dt;
};


void Particle::resetAcceleration(){
    ax = 0;
    ay = 0;
    az = 0;
};
