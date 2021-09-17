#ifndef FILE_INIT_H
#define FILE_INIT_H

#include <vector>
#include  <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <typeinfo>
#include "particle.h"  

struct init_parameters
{
    //      Struct used to return the data contained
    //      in the tests files, the files are in the form : 
    //
    //      G
    //      NbBodyMass NbTracer
    //      x y z vx vy vz m     <-- NbNodyMass lines like rhis
    //      .
    //      .                       
    //      .
    //      .
    //      x y z vx vy vz       <-- NbTracer lines like this

    std::vector<Particle> vec_of_particles;
    double gravity;
    int number_body_of_mass;
    int number_of_tracers;
};

init_parameters init_particles(double G, int NbBodyMass, int NbTracer, std::string filename){
    struct init_parameters parameters;
    std::ifstream file;
    file.open(filename);
    std::string line;
    std::vector<Particle> vect_particles;
    int i = 0;
    bool isTracer = 1;
    double x, y ,z ,vx, vy ,vz;
    float m;
    while(file.is_open()){
        if (file.eof()){
            file.close();
        }
        else {
            while(getline(file, line)){;
                std::istringstream sString( line );
                if( i == 0){
                    sString >> G; 
                }
                else if (i == 1){
                    sString >> NbBodyMass >> NbTracer;
                }
                else if (((NbBodyMass + 1 )>= i)  && (i>1) ) {
                    // the lines here are the body with masses
                    sString >> x >>  y >> z >> vx >> vy >> vz >> m;
                    Particle p = Particle(x, y, z, vx, vy, vz, 0, 0, 0, m, not isTracer);
                    vect_particles.push_back(p);
                }
                else{
                    // the lines here are the tracers
                    sString >> x >>  y >> z >> vx >> vy >> vz;
                    Particle p = Particle(x, y, z, vx, vy, vz, 0, 0, 0, 0, isTracer);
                    vect_particles.push_back(p);
                };
                i += 1;
            };
        };
    };
    parameters.vec_of_particles = vect_particles;
    parameters.gravity = G;
    parameters.number_body_of_mass = NbBodyMass;
    parameters.number_of_tracers = NbTracer;
    return parameters;
}; 


#endif