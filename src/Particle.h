#pragma once
#include "Vec3.h"

namespace sph {

class Particle {
public:

    Vec3 position;
    Vec3 velocity;
    Vec3 acceleration;

    float mass;
    float inverseMass;

    float damping;

    Vec3 forceAccum;

    Particle()
        : position(Vec3::zero()), velocity(Vec3::zero()), acceleration(Vec3::zero()),
          mass(1.0f), inverseMass(1.0f), damping(0.999f), forceAccum(Vec3::zero()) {}

    void setMass(float m) {
        if (m <= 0) {
            mass = 0;
            inverseMass = 0;
        } else {
            mass = m;
            inverseMass = 1.0f / m;
        }
    }

    bool hasFiniteMass() const {
        return inverseMass > 0;
    }

    void addForce(const Vec3& force) {
        forceAccum += force;
    }

    void integrate(float dt) {
        if (inverseMass <= 0) {
            return;
        }

        velocity += acceleration * dt;

        velocity *= std::pow(damping, dt);

        position += velocity * dt;

        clearAccumulator();
    }

    void clearAccumulator() {
        forceAccum = Vec3::zero();
    }
};

}
