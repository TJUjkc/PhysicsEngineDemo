#define _USE_MATH_DEFINES
#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "PhysicsWorld.h"
#include "Camera.h"
#include "Shader.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

static sph::PhysicsWorld g_world;
static sph::Camera       g_camera;
static int   g_width = 1280, g_height = 720;
static bool  g_mouseDown = false;
static int   g_mouseX = 0, g_mouseY = 0;
static DWORD g_lastTick = 0;
static bool  g_paused = false;
static float g_dtScale = 1.0f;

void reshape(int w, int h) {
    g_width = w;
    g_height = h;
    glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int, int) {
    switch (key) {
        case 'p': case 'P': {
            g_paused = !g_paused;
        } break;
        case '+': case '=': {
            g_dtScale = std::min(g_dtScale + 0.1f, 3.0f);
        } break;
        case '-': case '_': {
            g_dtScale = std::max(g_dtScale - 0.1f, 0.1f);
        } break;
        case 'r': case 'R': {
            g_world.clear();
            setupWorld();
        } break;
        case 27: {
            exit(0);
        } break;
    }
}

void specialKey(int key, int, int) {
    switch (key) {
        case GLUT_KEY_LEFT: {
            g_camera.yaw -= 5.0f;
        } break;
        case GLUT_KEY_RIGHT: {
            g_camera.yaw += 5.0f;
        } break;
        case GLUT_KEY_UP: {
            g_camera.pitch = std::min(g_camera.pitch + 3.0f, 89.0f);
        } break;
        case GLUT_KEY_DOWN: {
            g_camera.pitch = std::max(g_camera.pitch - 3.0f, -89.0f);
        } break;
    }
}

void mouseButton(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON) {
        g_mouseDown = (state == GLUT_DOWN);
        g_mouseX = x;
        g_mouseY = y;
    }
    if (btn == 3) {
        g_camera.distance = std::max(g_camera.distance - 0.5f, 3.0f);
    }
    if (btn == 4) {
        g_camera.distance = std::min(g_camera.distance + 0.5f, 50.0f);
    }
}

void mouseMotion(int x, int y) {
    if (g_mouseDown) {
        int dx = x - g_mouseX, dy = y - g_mouseY;
        g_camera.yaw += dx * 0.4f;
        g_camera.pitch += dy * 0.4f;
        g_camera.pitch = std::max(-89.0f, std::min(89.0f, g_camera.pitch));
        g_mouseX = x;
        g_mouseY = y;
    }
}

void setupWorld() {
    auto* floor = new sph::RigidBody();
    floor->position = sph::Vec3(0, -0.5f, 0);
    floor->scale = sph::Vec3(20, 0.5f, 20);
    floor->setStatic(true);
    floor->bvType = sph::BoundingVolumeType::AABB;
    floor->boundingAABB = {10, 0.5f, 10};
    g_world.addBody(floor);

    for (int i = 0; i < 5; ++i) {
        auto* ball = new sph::RigidBody();
        ball->position = sph::Vec3(
            (float)(rand() % 10 - 5),
            5.0f + (float)(rand() % 5),
            (float)(rand() % 10 - 5));
        ball->velocity = sph::Vec3(
            (float)(rand() % 6 - 3),
            0,
            (float)(rand() % 6 - 3));
        ball->bvType = sph::BoundingVolumeType::SPHERE;
        ball->boundingSphere = {0.5f};
        ball->setMass(1.0f);
        g_world.addBody(ball);
    }

    for (int i = 0; i < 3; ++i) {
        auto* box = new sph::RigidBody();
        box->position = sph::Vec3(
            (float)(rand() % 8 - 4),
            8.0f + (float)(rand() % 4),
            (float)(rand() % 8 - 4));
        box->velocity = sph::Vec3(
            (float)(rand() % 4 - 2),
            0,
            (float)(rand() % 4 - 2));
        box->bvType = sph::BoundingVolumeType::AABB;
        box->boundingAABB = {0.4f, 0.4f, 0.4f};
        box->setMass(2.0f);
        g_world.addBody(box);
    }

    g_world.gravity = sph::Vec3(0, -9.81f, 0);
    g_world.floorY = 0.0f;
}

void drawFloor() {
    glDisable(GL_TEXTURE_2D);
    glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
    glBegin(GL_QUADS);
    float s = 20.0f;
    glVertex3f(-s, 0, -s);
    glVertex3f( s, 0, -s);
    glVertex3f( s, 0,  s);
    glVertex3f(-s, 0,  s);
    glEnd();

    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    for (int i = -(int)s; i <= (int)s; i++) {
        glVertex3f((float)i, 0.01f, -s);
        glVertex3f((float)i, 0.01f,  s);
        glVertex3f(-s, 0.01f, (float)i);
        glVertex3f( s, 0.01f, (float)i);
    }
    glEnd();
}

void drawBodies() {
    for (auto* body : g_world.bodies) {
        if (body->isStatic) {
            continue;
        }
        glPushMatrix();
        glTranslatef(body->position.x, body->position.y, body->position.z);
        glScalef(body->scale.x, body->scale.y, body->scale.z);

        if (body->bvType == sph::BoundingVolumeType::SPHERE) {
            glColor4f(0.8f, 0.3f, 0.2f, 0.85f);
            glutSolidSphere(body->boundingSphere.radius, 16, 16);
        } else if (body->bvType == sph::BoundingVolumeType::AABB) {
            glColor4f(0.2f, 0.5f, 0.8f, 0.85f);
            float hx = body->boundingAABB.halfExtentsX;
            float hy = body->boundingAABB.halfExtentsY;
            float hz = body->boundingAABB.halfExtentsZ;
            glScalef(hx, hy, hz);
            glutSolidCube(2.0f);
        }

        glPopMatrix();
    }
}

void display() {
    DWORD now = GetTickCount();
    float dt = (float)(now - g_lastTick) / 1000.0f;
    if (dt > 0.1f) {
        dt = 0.1f;
    }
    g_lastTick = now;

    if (!g_paused) {
        g_world.step(dt * g_dtScale);
    }

    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sph::Mat4 view = g_camera.getViewMatrix();
    sph::Mat4 proj = g_camera.getProjectionMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(reinterpret_cast<const float*>(&proj));

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(reinterpret_cast<const float*>(&view));

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    drawFloor();
    drawBodies();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, g_width, 0, g_height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);

    std::ostringstream ss;
    ss << "Bodies: " << g_world.bodies.size()
       << "  TimeScale: " << std::fixed << std::setprecision(1) << g_dtScale << "x"
       << (g_paused ? "  [PAUSED]" : "");
    glRasterPos2f(10, g_height - 20);
    for (char c : ss.str()) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)c);
    }

    {
        std::string info = "P: Pause  +/-: TimeScale  R: Reset  Arrows/Drag: Camera  Scroll: Zoom  ESC: Quit";
        glRasterPos2f(10, (float)(g_height - 50));
        for (char c : info) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)c);
        }
    }

    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(g_width, g_height);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Simple Physics Engine");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    g_camera.position = sph::Vec3(0, 5, 15);
    g_camera.yaw = -90.0f;
    g_camera.pitch = 30.0f;
    g_camera.distance = 20.0f;

    setupWorld();
    g_lastTick = GetTickCount();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);

    glutMainLoop();
    return 0;
}
