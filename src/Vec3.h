#pragma once
#include <cmath>

namespace sph {

class Vec3 {
public:
    float x, y, z;

    Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    static Vec3 zero() { return Vec3(0, 0, 0); }
    static Vec3 one()  { return Vec3(1, 1, 1); }
    static Vec3 up()   { return Vec3(0, 1, 0); }
    static Vec3 down() { return Vec3(0, -1, 0); }
    static Vec3 left() { return Vec3(-1, 0, 0); }
    static Vec3 right(){ return Vec3(1, 0, 0); }
    static Vec3 forward() { return Vec3(0, 0, 1); }
    static Vec3 back()    { return Vec3(0, 0, -1); }

    Vec3 operator+(const Vec3& o) const { return {x + o.x, y + o.y, z + o.z}; }
    Vec3 operator-(const Vec3& o) const { return {x - o.x, y - o.y, z - o.z}; }
    Vec3 operator*(float s) const { return {x * s, y * s, z * s}; }
    Vec3 operator/(float s) const { return {x / s, y / s, z / s}; }
    Vec3 operator-() const { return {-x, -y, -z}; }

    Vec3& operator+=(const Vec3& o) {
        x += o.x; y += o.y; z += o.z;
        return *this;
    }

    Vec3& operator-=(const Vec3& o) {
        x -= o.x; y -= o.y; z -= o.z;
        return *this;
    }

    Vec3& operator*=(float s) {
        x *= s; y *= s; z *= s;
        return *this;
    }

    float dot(const Vec3& o) const { return x * o.x + y * o.y + z * o.z; }

    Vec3 cross(const Vec3& o) const {
        return {
            y * o.z - z * o.y,
            z * o.x - x * o.z,
            x * o.y - y * o.x
        };
    }

    float magnitudeSquared() const { return x * x + y * y + z * z; }
    float magnitude() const { return std::sqrt(magnitudeSquared()); }

    Vec3 normalized() const {
        float m = magnitude();
        if (m > 0) {
            return (*this) / m;
        } else {
            return Vec3::zero();
        }
    }
};

}
