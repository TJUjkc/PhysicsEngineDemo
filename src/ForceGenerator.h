#pragma once
#include "Vec3.h"
#include "RigidBody.h"
#include <vector>
#include <algorithm>

namespace sph {

class ForceGenerator {
public:
    virtual ~ForceGenerator() {}

    virtual void updateForce(RigidBody* body, float dt) = 0;
};

class GravityGenerator : public ForceGenerator {
public:
    Vec3 gravity;

    GravityGenerator(const Vec3& g = Vec3(0, -9.81f, 0)) : gravity(g) {}

    void updateForce(RigidBody* body, float dt) override {
        if (!body->hasFiniteMass()) {
            return;
        }
        body->addForce(gravity * body->mass);
    }
};

class SpringGenerator : public ForceGenerator {
public:
    RigidBody* other;
    float restLength;
    float springConstant;

    SpringGenerator(RigidBody* otherBody, float restLen, float k)
        : other(otherBody), restLength(restLen), springConstant(k) {}

    void updateForce(RigidBody* body, float dt) override {

        Vec3 diff = body->position - other->position;
        float length = diff.magnitude();
        if (length < 1e-6f) {
            return;
        }

        float extension = length - restLength;

        Vec3 force = diff.normalized() * (-springConstant * extension);
        body->addForce(force);
    }
};

class DragGenerator : public ForceGenerator {
public:
    float k1;
    float k2;

    DragGenerator(float linear = 0.1f, float quadratic = 0.01f)
        : k1(linear), k2(quadratic) {}

    void updateForce(RigidBody* body, float dt) override {
        if (!body->hasFiniteMass()) {
            return;
        }

        Vec3 force = body->velocity * -k1;

        float speed = body->velocity.magnitude();
        force += body->velocity * (-k2 * speed);
        body->addForce(force);
    }
};

class AnchorSpringGenerator : public ForceGenerator {
public:
    Vec3 anchor;
    float restLength;
    float springConstant;

    AnchorSpringGenerator(const Vec3& anchorPoint, float restLen, float k)
        : anchor(anchorPoint), restLength(restLen), springConstant(k) {}

    void updateForce(RigidBody* body, float dt) override {

        Vec3 diff = body->position - anchor;
        float length = diff.magnitude();
        if (length < 1e-6f) {
            return;
        }

        float extension = length - restLength;
        Vec3 force = diff.normalized() * (-springConstant * extension);
        body->addForce(force);
    }
};

class BuoyancyGenerator : public ForceGenerator {
public:
    float liquidDensity;
    float volume;
    float waterLevel;
    float maxDepth;

    BuoyancyGenerator(float density = 1000.0f, float vol = 1.0f,
                      float waterLvl = 0.0f, float maxD = 2.0f)
        : liquidDensity(density), volume(vol),
          waterLevel(waterLvl), maxDepth(maxD) {}

    void updateForce(RigidBody* body, float dt) override {
        if (!body->hasFiniteMass()) {
            return;
        }

        float depth = -(body->position.y - waterLevel);

        if (depth <= 0) {
            return;
        }

        float submersion = std::min(depth / maxDepth, 1.0f);

        Vec3 force(0, liquidDensity * volume * 9.81f * submersion, 0);
        body->addForce(force);
    }
};

struct ForceRegistration {
    RigidBody* body;
    ForceGenerator* fg;
};

class ForceRegistry {
public:
    std::vector<ForceRegistration> registrations;

    void add(RigidBody* body, ForceGenerator* fg) {
        registrations.push_back({body, fg});
    }

    void remove(RigidBody* body, ForceGenerator* fg) {
        registrations.erase(
            std::remove_if(registrations.begin(), registrations.end(),
                [&](const ForceRegistration& reg) {
                    return reg.body == body && reg.fg == fg;
                }),
            registrations.end());
    }

    void clear() {
        registrations.clear();
    }

    void updateForces(float dt) {
        for (auto& reg : registrations) {
            reg.fg->updateForce(reg.body, dt);
        }
    }
};

}
