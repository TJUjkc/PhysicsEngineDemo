#pragma once
#include "Vec3.h"
#include "RigidBody.h"
#include <vector>
#include <algorithm>

namespace sph {

struct Contact {
    RigidBody* bodyA;
    RigidBody* bodyB;
    Vec3 contactNormal;
    float penetration;
    Vec3 contactPoint;
    float restitution;

    float friction;

    Contact()
        : bodyA(nullptr), bodyB(nullptr),
          penetration(0), restitution(0.5f), friction(0.3f) {}
};

class ContactResolver {
public:
    int maxIterations;
    float velocityEpsilon;
    float positionEpsilon;

    ContactResolver(int iterations = 10,
                    float velEps = 0.001f,
                    float posEps = 0.01f)
        : maxIterations(iterations),
          velocityEpsilon(velEps),
          positionEpsilon(posEps) {}

    void resolveContacts(std::vector<Contact>& contacts, float dt) {
        if (contacts.empty()) {
            return;
        }

        for (auto& c : contacts) {
            prepareContact(c);
        }

        resolvePosition(contacts);

        resolveVelocity(contacts, dt);
    }

private:

    void prepareContact(Contact& c) {
        if (c.bodyA && c.bodyB) {
            c.restitution = std::min(
                getRestitution(c.bodyA), getRestitution(c.bodyB));
            c.friction = std::sqrt(
                getFriction(c.bodyA) * getFriction(c.bodyB));
        }
    }

    float getRestitution(RigidBody* body) {
        return 0.5f;
    }

    float getFriction(RigidBody* body) {
        return 0.3f;
    }

    void resolvePosition(std::vector<Contact>& contacts) {
        for (int iter = 0; iter < maxIterations; ++iter) {

            float maxPen = 0;
            for (auto& c : contacts) {
                if (c.penetration > maxPen) {
                    maxPen = c.penetration;
                }
            }

            if (maxPen <= positionEpsilon) {
                break;
            }

            for (auto& c : contacts) {
                adjustPositions(c, maxPen);
            }
        }
    }

    void adjustPositions(Contact& c, float maxPen) {
        if (c.penetration <= 0) {
            return;
        }

        float totalInverseMass = 0;
        if (c.bodyA && c.bodyA->hasFiniteMass()) {
            totalInverseMass += c.bodyA->inverseMass;
        }
        if (c.bodyB && c.bodyB->hasFiniteMass()) {
            totalInverseMass += c.bodyB->inverseMass;
        }
        if (totalInverseMass <= 0) {
            return;
        }

        float move = c.penetration / totalInverseMass;
        if (c.bodyA && c.bodyA->hasFiniteMass()) {
            c.bodyA->position += c.contactNormal * (move * c.bodyA->inverseMass);
        }
        if (c.bodyB && c.bodyB->hasFiniteMass()) {
            c.bodyB->position -= c.contactNormal * (move * c.bodyB->inverseMass);
        }
        c.penetration = 0;
    }

    void resolveVelocity(std::vector<Contact>& contacts, float dt) {
        for (int iter = 0; iter < maxIterations; ++iter) {

            float maxMag = 0;
            for (auto& c : contacts) {
                float mag = computeVelocityMag(c, dt);
                if (mag > maxMag) {
                    maxMag = mag;
                }
            }

            if (maxMag <= velocityEpsilon) {
                break;
            }

            for (auto& c : contacts) {
                adjustVelocities(c, dt);
            }
        }
    }

    float computeVelocityMag(Contact& c, float dt) {
        Vec3 relVel = computeRelativeVelocity(c);
        float contactVel = relVel.dot(c.contactNormal);
        return std::fabs(contactVel);
    }

    Vec3 computeRelativeVelocity(const Contact& c) {
        Vec3 velA = c.bodyA ? c.bodyA->velocity : Vec3::zero();
        Vec3 velB = c.bodyB ? c.bodyB->velocity : Vec3::zero();
        return velA - velB;
    }

    void adjustVelocities(Contact& c, float dt) {
        Vec3 relVel = computeRelativeVelocity(c);

        float contactVel = relVel.dot(c.contactNormal);

        float desiredDeltaVel = -contactVel * (1 + c.restitution);

        float totalInverseMass = 0;
        if (c.bodyA && c.bodyA->hasFiniteMass()) {
            totalInverseMass += c.bodyA->inverseMass;
        }
        if (c.bodyB && c.bodyB->hasFiniteMass()) {
            totalInverseMass += c.bodyB->inverseMass;
        }
        if (totalInverseMass <= 0) {
            return;
        }

        float impulseMag = desiredDeltaVel / totalInverseMass;
        Vec3 impulse = c.contactNormal * impulseMag;

        if (c.bodyA && c.bodyA->hasFiniteMass()) {
            c.bodyA->velocity += impulse * c.bodyA->inverseMass;
        }
        if (c.bodyB && c.bodyB->hasFiniteMass()) {
            c.bodyB->velocity -= impulse * c.bodyB->inverseMass;
        }
    }
};

class CollisionDetector {
public:

    static unsigned sphereVsSphere(
        const RigidBody& bodyA, const RigidBody& bodyB,
        std::vector<Contact>& contacts)
    {
        if (bodyA.bvType != BoundingVolumeType::SPHERE ||
            bodyB.bvType != BoundingVolumeType::SPHERE) {
            return 0;
        }

        Vec3 delta = bodyA.position - bodyB.position;
        float distSq = delta.magnitudeSquared();
        float radiusSum = bodyA.boundingSphere.radius + bodyB.boundingSphere.radius;

        if (distSq >= radiusSum * radiusSum) {
            return 0;
        }

        float dist = std::sqrt(distSq);

        Vec3 normal = (dist > 1e-6f) ? (delta / dist) : Vec3(0, 1, 0);

        Contact c;
        c.bodyA = const_cast<RigidBody*>(&bodyA);
        c.bodyB = const_cast<RigidBody*>(&bodyB);
        c.contactNormal = normal;
        c.penetration = radiusSum - dist;
        c.contactPoint = bodyB.position + normal * bodyB.boundingSphere.radius;
        contacts.push_back(c);
        return 1;
    }

    static unsigned sphereVsPlane(
        const RigidBody& sphere, float planeY,
        const Vec3& planeNormal,
        std::vector<Contact>& contacts)
    {
        if (sphere.bvType != BoundingVolumeType::SPHERE) {
            return 0;
        }

        float dist = (sphere.position - Vec3(0, planeY, 0)).dot(planeNormal);

        float pen = sphere.boundingSphere.radius - dist;

        if (pen <= 0) {
            return 0;
        }

        Contact c;
        c.bodyA = const_cast<RigidBody*>(&sphere);
        c.bodyB = nullptr;
        c.contactNormal = planeNormal;
        c.penetration = pen;
        c.contactPoint = sphere.position - planeNormal * dist;
        contacts.push_back(c);
        return 1;
    }

    static unsigned aabbVsAabb(
        const RigidBody& bodyA, const RigidBody& bodyB,
        std::vector<Contact>& contacts)
    {
        if (bodyA.bvType != BoundingVolumeType::AABB ||
            bodyB.bvType != BoundingVolumeType::AABB) {
            return 0;
        }

        if (!bodyA.boundingAABB.intersects(bodyB.boundingAABB)) {
            return 0;
        }

        Vec3 aMin = bodyA.boundingAABB.min(), aMax = bodyA.boundingAABB.max();
        Vec3 bMin = bodyB.boundingAABB.min(), bMax = bodyB.boundingAABB.max();

        float overlapX = std::min(aMax.x, bMax.x) - std::max(aMin.x, bMin.x);
        float overlapY = std::min(aMax.y, bMax.y) - std::max(aMin.y, bMin.y);
        float overlapZ = std::min(aMax.z, bMax.z) - std::max(aMin.z, bMin.z);

        float minOverlap = overlapX;
        Vec3 normal(1, 0, 0);
        if (overlapY < minOverlap) {
            minOverlap = overlapY;
            normal = Vec3(0, 1, 0);
        }
        if (overlapZ < minOverlap) {
            minOverlap = overlapZ;
            normal = Vec3(0, 0, 1);
        }

        Vec3 delta = bodyA.position - bodyB.position;
        if (delta.dot(normal) < 0) {
            normal = normal * -1;
        }

        Contact c;
        c.bodyA = const_cast<RigidBody*>(&bodyA);
        c.bodyB = const_cast<RigidBody*>(&bodyB);
        c.contactNormal = normal;
        c.penetration = minOverlap;
        c.contactPoint = (bodyA.position + bodyB.position) * 0.5f;
        contacts.push_back(c);
        return 1;
    }

    static unsigned aabbVsPlane(
        const RigidBody& aabbBody, float planeY,
        const Vec3& planeNormal,
        std::vector<Contact>& contacts)
    {
        if (aabbBody.bvType != BoundingVolumeType::AABB) {
            return 0;
        }

        Vec3 aMin = aabbBody.boundingAABB.min();

        float pen = planeY - aMin.y;
        if (pen <= 0) {
            return 0;
        }

        Vec3 aMax = aabbBody.boundingAABB.max();

        Contact c;
        c.bodyA = const_cast<RigidBody*>(&aabbBody);
        c.bodyB = nullptr;
        c.contactNormal = planeNormal;
        c.penetration = pen;
        c.contactPoint = Vec3(
            (aMin.x + aMax.x) * 0.5f,
            aMin.y,
            (aMin.z + aMax.z) * 0.5f
        );
        contacts.push_back(c);
        return 1;
    }
};

}
