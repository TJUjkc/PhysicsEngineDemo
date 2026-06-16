#pragma once
#include <cmath>
#include "Vec3.h"

namespace sph {

class Quaternion {
public:
    float w, x, y, z;

    Quaternion(float w = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f)
        : w(w), x(x), y(y), z(z) {}

    Quaternion operator*(const Quaternion& q) const {
        return Quaternion(
            w * q.w - x * q.x - y * q.y - z * q.z,
            w * q.x + x * q.w + y * q.z - z * q.y,
            w * q.y - x * q.z + y * q.w + z * q.x,
            w * q.z + x * q.y - y * q.x + z * q.w
        );
    }

    Quaternion& operator*=(const Quaternion& q) {
        *this = *this * q;
        return *this;
    }

    void normalize() {
        float mag = std::sqrt(w * w + x * x + y * y + z * z);
        if (mag > 0.0f) {
            w /= mag;
            x /= mag;
            y /= mag;
            z /= mag;
        }
    }

    Quaternion normalized() const {
        Quaternion q = *this;
        q.normalize();
        return q;
    }

    Quaternion conjugate() const {
        return Quaternion(w, -x, -y, -z);
    }

    static Quaternion fromAxisAngle(const Vec3& axis, float angle) {
        float halfSin = std::sin(angle / 2.0f);
        float halfCos = std::cos(angle / 2.0f);
        return Quaternion(
            halfCos,
            axis.x * halfSin,
            axis.y * halfSin,
            axis.z * halfSin
        );
    }

    Vec3 rotateVector(const Vec3& v) const {
        Quaternion qv(0, v.x, v.y, v.z);
        Quaternion result = (*this) * qv * conjugate();
        return Vec3(result.x, result.y, result.z);
    }

    Mat4 toMatrix() const {
        float xx = x * x, yy = y * y, zz = z * z;
        float xy = x * y, xz = x * z, yz = y * z;
        float wx = w * x, wy = w * y, wz = w * z;

        Mat4 mat;
        mat.m[0][0] = 1.0f - 2.0f * (yy + zz);
        mat.m[0][1] = 2.0f * (xy - wz);
        mat.m[0][2] = 2.0f * (xz + wy);
        mat.m[0][3] = 0.0f;

        mat.m[1][0] = 2.0f * (xy + wz);
        mat.m[1][1] = 1.0f - 2.0f * (xx + zz);
        mat.m[1][2] = 2.0f * (yz - wx);
        mat.m[1][3] = 0.0f;

        mat.m[2][0] = 2.0f * (xz - wy);
        mat.m[2][1] = 2.0f * (yz + wx);
        mat.m[2][2] = 1.0f - 2.0f * (xx + yy);
        mat.m[2][3] = 0.0f;

        mat.m[3][0] = 0.0f;
        mat.m[3][1] = 0.0f;
        mat.m[3][2] = 0.0f;
        mat.m[3][3] = 1.0f;

        return mat;
    }
};

}
