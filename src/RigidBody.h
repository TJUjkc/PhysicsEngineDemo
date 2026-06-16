#pragma once
#include "Vec3.h"
#include "Quaternion.h"
#include "Mat4.h"

namespace sph {

enum class BoundingVolumeType {
    NONE,
    SPHERE,
    AABB
};

struct BoundingSphere {
    float radius;
};

struct BoundingAABB {
    float halfExtentsX, halfExtentsY, halfExtentsZ;

    Vec3 min() const { return Vec3(-halfExtentsX, -halfExtentsY, -halfExtentsZ); }
    Vec3 max() const { return Vec3( halfExtentsX,  halfExtentsY,  halfExtentsZ); }

    bool intersects(const BoundingAABB& other) const {
        return true;
    }
};

class RigidBody {
public:
    Vec3 position;
    Vec3 velocity;
    Vec3 acceleration;

    Quaternion orientation;
    Vec3 angularVelocity;

    Vec3 scale;

    float mass;
    float inverseMass;

    bool isStatic;

    BoundingVolumeType bvType;
    BoundingSphere boundingSphere;
    BoundingAABB boundingAABB;

    float linearDamping;
    float angularDamping;

    RigidBody()
        : position(Vec3::zero()), velocity(Vec3::zero()), acceleration(Vec3::zero()),
          orientation(Quaternion()), angularVelocity(Vec3::zero()),
          scale(Vec3(1, 1, 1)),
          mass(1.0f), inverseMass(1.0f), isStatic(false),
          bvType(BoundingVolumeType::NONE),
          boundingSphere({0.5f}),
          boundingAABB({0.5f, 0.5f, 0.5f}),
          linearDamping(0.999f), angularDamping(0.999f) {}

    void setMass(float m) {
        if (m <= 0) {
            mass = 0;
            inverseMass = 0;
        } else {
            mass = m;
            inverseMass = 1.0f / m;
        }
    }

    void setStatic(bool s) {
        isStatic = s;
        if (isStatic) {
            inverseMass = 0;
        }
    }

    bool hasFiniteMass() const {
        return inverseMass > 0;
    }

    void addForce(const Vec3& force) {
        forceAccum += force;
    }

    void addTorque(const Vec3& torque) {
        torqueAccum += torque;
    }

    void clearAccumulators() {
        forceAccum = Vec3::zero();
        torqueAccum = Vec3::zero();
    }

    void integrate(float dt) {
        if (isStatic) {
            return;
        }

        velocity += acceleration * dt;

        position += velocity * dt;

        velocity *= std::pow(linearDamping, dt);

        angularVelocity *= std::pow(angularDamping, dt);

        orientation = Quaternion::fromAxisAngle(
            angularVelocity.normalized(),
            angularVelocity.magnitude() * dt
        ) * orientation;
        orientation.normalize();

        clearAccumulators();
    }

    Mat4 getTransformMatrix() const {
        Mat4 trans = Mat4::translate(position);
        Mat4 rot = orientation.toMatrix();
        Mat4 scl = Mat4::scale(scale);
        return trans * rot * scl;
    }

private:
    Vec3 forceAccum;
    Vec3 torqueAccum;
};

}

