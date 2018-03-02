#include "main.h"

#ifndef SPHERE_H
#define SPHERE_H


class Sphere {
public:
    Sphere() {}
    Sphere(float x, float y, float z, float radius);
    glm::vec3 position, end1, end2, speed;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void decelarate();
    void tick();
    void set_speed(float x, float y, float z);
private:
    VAO *object;
    static const float AIR_TERMINAL_SPEED = -0.55;
    static const float AIR_DEACCELARATION = 0.01; // This is the deaccelaration per frame(60 frames per second).
};

#endif // BOAT_H
