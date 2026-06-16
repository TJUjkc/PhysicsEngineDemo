#pragma once
#include "Vec3.h"
#include "Mat4.h"

namespace sph {

class Camera {
public:
    Vec3 position;
    Vec3 target;
    Vec3 up;

    float yaw;
    float pitch;

    float distance;

    float fov;
    float aspect;
    float nearPlane;
    float farPlane;

    float moveSpeed;
    float rotateSpeed;

    Camera()
        : position(Vec3(0, 5, 15)), target(Vec3::zero()), up(Vec3::up()),
          yaw(-90.0f), pitch(30.0f), distance(20.0f),
          fov(60.0f), aspect(16.0f / 9.0f), nearPlane(0.1f), farPlane(1000.0f),
          moveSpeed(5.0f), rotateSpeed(1.0f) {}

    Mat4 getViewMatrix() const {
        float yawRad = yaw * 3.14159265f / 180.0f;
        float pitchRad = pitch * 3.14159265f / 180.0f;

        Vec3 pos(
            distance * std::cos(pitchRad) * std::cos(yawRad),
            distance * std::sin(pitchRad),
            distance * std::cos(pitchRad) * std::sin(yawRad)
        );

        return Mat4::lookAt(pos, Vec3::zero(), Vec3::up());
    }

    Mat4 getProjectionMatrix() const {
        return Mat4::perspective(
            fov * 3.14159265f / 180.0f, aspect, nearPlane, farPlane);
    }

    void orbit(float dYaw, float dPitch) {
        yaw += dYaw * rotateSpeed;
        pitch += dPitch * rotateSpeed;
        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }
    }

    void zoom(float delta) {
        distance -= delta * 2.0f;
        if (distance < 2.0f) {
            distance = 2.0f;
        }
        if (distance > 100.0f) {
            distance = 100.0f;
        }
    }
};

}
