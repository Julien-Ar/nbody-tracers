#ifndef PARTICLE_H
#define PARTICLE_H


class Particle {
    public :
        double x, y, z, vx, vy ,vz, ax, ay, az;
        float mass;
        bool isTracer;
        Particle();
        Particle(double, double, double, 
                double, double, double, 
                double, double, double,
                float, bool);
        void computePosition(double dt);
        void computeAcceleration(Particle , double G );
        void resetAcceleration();
};

#endif


