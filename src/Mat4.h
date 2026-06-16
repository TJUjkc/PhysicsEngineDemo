#pragma once
#include <cmath>
#include <cstring>
#include "Vec3.h"

namespace sph {

class Mat4 {
public:
    float m[4][4];

    Mat4() {
        identity();
    }

    void identity() {
        memset(m, 0, sizeof(m));
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
    }

    float* operator[](int i) {
        return m[i];
    }
    const float* operator[](int i) const {
        return m[i];
    }

    Mat4 operator*(const Mat4& other) const {
        Mat4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.m[i][j] = 0;
                for (int k = 0; k < 4; ++k) {
                    result.m[i][j] += m[i][k] * other.m[k][j];
                }
            }
        }
        return result;
    }

    Vec3 transform(const Vec3& v) const {
        return Vec3(
            m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3],
            m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3],
            m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3]
        );
    }

    Mat4 transpose() const {
        Mat4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.m[i][j] = m[j][i];
            }
        }
        return result;
    }

    float determinant() const {

        const float* a = m[0];
        const float* b = m[1];
        const float* c = m[2];
        const float* d = m[3];

        auto det3 = [](float a0, float a1, float a2,
                       float b0, float b1, float b2,
                       float c0, float c1, float c2) -> float {
            return a0 * (b1 * c2 - b2 * c1)
                 - a1 * (b0 * c2 - b2 * c0)
                 + a2 * (b0 * c1 - b1 * c0);
        };

        return a[0] * det3(b[1], b[2], b[3], c[1], c[2], c[3], d[1], d[2], d[3])
             - a[1] * det3(b[0], b[2], b[3], c[0], c[2], c[3], d[0], d[2], d[3])
             + a[2] * det3(b[0], b[1], b[3], c[0], c[1], c[3], d[0], d[1], d[3])
             - a[3] * det3(b[0], b[1], b[2], c[0], c[1], c[2], d[0], d[1], d[2]);
    }

    Mat4 inverse() const {

        Mat4 adj;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {

                float sub[3][3];
                int si = 0;
                for (int r = 0; r < 4; ++r) {
                    if (r == i) {
                        continue;
                    }
                    int sj = 0;
                    for (int col = 0; col < 4; ++col) {
                        if (col == j) {
                            continue;
                        }
                        sub[si][sj++] = m[r][col];
                    }
                    ++si;
                }

                float det3 = sub[0][0] * (sub[1][1] * sub[2][2] - sub[1][2] * sub[2][1])
                           - sub[0][1] * (sub[1][0] * sub[2][2] - sub[1][2] * sub[2][0])
                           + sub[0][2] * (sub[1][0] * sub[2][1] - sub[1][1] * sub[2][0]);

                float sign = ((i + j) % 2 == 0) ? 1.0f : -1.0f;
                adj.m[j][i] = sign * det3;
            }
        }

        float det = m[0][0] * adj.m[0][0] + m[0][1] * adj.m[1][0]
                  + m[0][2] * adj.m[2][0] + m[0][3] * adj.m[3][0];

        Mat4 result;
        float invDet = 1.0f / det;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.m[i][j] = adj.m[i][j] * invDet;
            }
        }
        return result;
    }

    static Mat4 translate(const Vec3& v) {
        Mat4 mat;
        mat.m[0][3] = v.x;
        mat.m[1][3] = v.y;
        mat.m[2][3] = v.z;
        return mat;
    }

    static Mat4 scale(const Vec3& v) {
        Mat4 mat;
        mat.m[0][0] = v.x;
        mat.m[1][1] = v.y;
        mat.m[2][2] = v.z;
        return mat;
    }

    static Mat4 rotateX(float angle) {
        float c = std::cos(angle), s = std::sin(angle);
        Mat4 mat;
        mat.m[1][1] = c;
        mat.m[1][2] = -s;
        mat.m[2][1] = s;
        mat.m[2][2] = c;
        return mat;
    }

    static Mat4 rotateY(float angle) {
        float c = std::cos(angle), s = std::sin(angle);
        Mat4 mat;
        mat.m[0][0] = c;
        mat.m[0][2] = s;
        mat.m[2][0] = -s;
        mat.m[2][2] = c;
        return mat;
    }

    static Mat4 rotateZ(float angle) {
        float c = std::cos(angle), s = std::sin(angle);
        Mat4 mat;
        mat.m[0][0] = c;
        mat.m[0][1] = -s;
        mat.m[1][0] = s;
        mat.m[1][1] = c;
        return mat;
    }

    static Mat4 perspective(float fov, float aspect, float near, float far) {
        float f = 1.0f / std::tan(fov / 2.0f);
        Mat4 mat;
        memset(mat.m, 0, sizeof(mat.m));
        mat.m[0][0] = f / aspect;
        mat.m[1][1] = f;
        mat.m[2][2] = (far + near) / (near - far);
        mat.m[2][3] = (2.0f * far * near) / (near - far);
        mat.m[3][2] = -1.0f;
        mat.m[3][3] = 0.0f;
        return mat;
    }

    static Mat4 lookAt(const Vec3& eye, const Vec3& target, const Vec3& up) {
        Vec3 zAxis = (eye - target).normalized();
        Vec3 xAxis = up.cross(zAxis).normalized();
        Vec3 yAxis = zAxis.cross(xAxis);

        Mat4 mat;
        mat.m[0][0] = xAxis.x;
        mat.m[0][1] = xAxis.y;
        mat.m[0][2] = xAxis.z;
        mat.m[0][3] = -xAxis.dot(eye);
        mat.m[1][0] = yAxis.x;
        mat.m[1][1] = yAxis.y;
        mat.m[1][2] = yAxis.z;
        mat.m[1][3] = -yAxis.dot(eye);
        mat.m[2][0] = zAxis.x;
        mat.m[2][1] = zAxis.y;
        mat.m[2][2] = zAxis.z;
        mat.m[2][3] = -zAxis.dot(eye);
        mat.m[3][0] = 0;
        mat.m[3][1] = 0;
        mat.m[3][2] = 0;
        mat.m[3][3] = 1;
        return mat;
    }
};

}
