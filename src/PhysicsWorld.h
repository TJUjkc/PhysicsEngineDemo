#pragma once
#include "RigidBody.h"
#include "ForceGenerator.h"
#include "Collision.h"
#include <vector>
#include <algorithm>

namespace sph {

class PhysicsWorld {
public:
    float fixedDeltaTime;

    Vec3 gravity;
    float floorY;

    std::vector<RigidBody*> bodies;
    ForceRegistry forceRegistry;
    ContactResolver contactResolver;
    std::vector<Contact> contacts;

    PhysicsWorld()
        : fixedDeltaTime(1.0f / 60.0f),
          gravity(Vec3(0, -9.81f, 0)),
          floorY(0.0f) {}

    ~PhysicsWorld() {
        clear();
    }

    void addBody(RigidBody* body) {
        bodies.push_back(body);
    }

    void removeBody(RigidBody* body) {
        bodies.erase(
            std::remove(bodies.begin(), bodies.end(), body),
            bodies.end());
    }

    void clear() {
        bodies.clear();
        forceRegistry.clear();
        contacts.clear();
    }

    void step(float dt) {

        applyGravity();

        detectCollisions();

        contactResolver.resolveContacts(contacts, dt);

        for (auto* body : bodies) {
            body->integrate(dt);
        }

        enforceFloor();

        contacts.clear();
    }

    void fixedStep() {
        step(fixedDeltaTime);
    }

private:

    void applyGravity() {
        for (auto* body : bodies) {
            if (body->isStatic || !body->hasFiniteMass()) {
                continue;
            }
            body->addForce(gravity * body->mass);
        }
    }

    void detectCollisions() {

        for (size_t i = 0; i < bodies.size(); ++i) {
            if (bodies[i]->bvType == BoundingVolumeType::SPHERE) {
                CollisionDetector::sphereVsPlane(
                    *bodies[i], floorY, Vec3::up(), contacts);
            } else if (bodies[i]->bvType == BoundingVolumeType::AABB) {
                CollisionDetector::aabbVsPlane(
                    *bodies[i], floorY, Vec3::up(), contacts);
            }

            for (size_t j = i + 1; j < bodies.size(); ++j) {
                if (bodies[i]->bvType == BoundingVolumeType::SPHERE &&
                    bodies[j]->bvType == BoundingVolumeType::SPHERE) {
                    CollisionDetector::sphereVsSphere(*bodies[i], *bodies[j], contacts);
                } else if (bodies[i]->bvType == BoundingVolumeType::AABB &&
                           bodies[j]->bvType == BoundingVolumeType::AABB) {
                    CollisionDetector::aabbVsAabb(*bodies[i], *bodies[j], contacts);
                }
            }
        }
    }

    void enforceFloor() {
        for (auto* body : bodies) {
            if (body->isStatic) {
                continue;
            }

            float bottomY;
            if (body->bvType == BoundingVolumeType::SPHERE) {
                bottomY = body->position.y - body->boundingSphere.radius * body->scale.y;
            } else if (body->bvType == BoundingVolumeType::AABB) {
                bottomY = body->position.y - body->boundingAABB.halfExtentsY * body->scale.y;
            } else {
                bottomY = body->position.y;
            }

        if (bottomY < floorY) {
            body->position.y += floorY - bottomY;
            if (body->velocity.y < 0) {
                body->velocity.y *= -0.5f;
            }
        }
        }
    }
};

}
