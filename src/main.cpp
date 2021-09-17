#include <vector>
#include  <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ostream>
#include <iomanip>
#include "file_init.h"


// Constants
int Tmax = 5000;
double G;
int NbBodyMass; // number of bodies with a mass
int NbTracer;   // number of tracers, a tracer is a body without any mass
double dt = 1.0e-1; // time-step precision in the numerical integration scheme
int saveFrequence = 100;

std::vector<Particle> particlesMass; 
std::vector<Particle> particlesTracer; 


void SaveSolution(double t, int iteration){
    // Each iteration, we save a snapchot of every particle's position
    // in a file.

    std::ostringstream oString;
    oString << "gravity_" << std::setfill('0') << std::setw(7) << iteration << ".particles"; 
    
    std::ofstream file_out;
    file_out.open(oString.str());
    file_out << "# X Y Z" << std::endl;
    for (auto &p_mass : particlesMass){
        file_out << p_mass.x << " " <<p_mass.y << " " << p_mass.z  << std::endl;
    };
    for (auto &p_tracer : particlesTracer){
        file_out << p_tracer.x << " " <<p_tracer.y << " " << p_tracer.z  << std::endl;
    };

    file_out.close();
}


int main(int argc, char* argv[]){

    init_parameters parameters = init_particles(G, NbBodyMass, NbTracer, argv[1]);
    NbBodyMass = parameters.number_body_of_mass;
    NbTracer = parameters.number_of_tracers;
    G = parameters.gravity;

    // Initialization of 2 vectors : one containing the body with masses, the other 
    // containing the tracers
    for(const auto& particle: parameters.vec_of_particles){
        if (particle.isTracer)
            particlesTracer.push_back(particle);
        else
            particlesMass.push_back(particle);
    };

    double t = 0;
    int iteration = 0;
    while (t < Tmax) {
        
        int i = 0; // i and j are used to skip the iteration in the nested loop
        int j;     // where p_mass1 = p_mass2


        // Two For loops, for each particle with a mass,  we compute
        // its acceleration caused by all the other particles
        for( auto& p_mass1 : particlesMass){
            j = 0;
            // Before computing a particle acceleration, 
            // we have to reset it to zero at each time-step
            p_mass1.resetAcceleration();
            for( auto& p_mass2 : particlesMass){
                if ( i != j){
                    p_mass1.computeAcceleration(p_mass2, G);
                }
                j += 1;
            }
            // Once the particle acceleration has been computed
            // we use a leap-frog integration scheme to compute
            // its position
            p_mass1.computePosition(dt);
            i += 1;
        };

        // Same method but this time applied to the tracers,
        // only the body with a mass interacts with them
        for ( auto& tracer : particlesTracer){
            tracer.resetAcceleration();
            for (auto& p_mass : particlesMass){
                tracer.computeAcceleration(p_mass, G);
            };
            tracer.computePosition(dt);
        };
        if( iteration % saveFrequence == 0){
            std::cout<< " == Saving iteration " << iteration << "  |  " << "t = " << t<< std::endl;
            SaveSolution(t, iteration);
        }
        iteration += 1;
        t += dt;
    };
};