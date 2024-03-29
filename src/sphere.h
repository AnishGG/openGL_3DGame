#include "main.h"

#ifndef SPHERE_H
#define SPHERE_H


class Sphere {
public:
    Sphere() {}
    Sphere(float x, float y, float z, float radius, color_t col1 = COLOR_RED);
    glm::vec3 position, end1, end2, speed;
    float rotation, radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void decelarate();
    void tick();
    void set_speed(float x, float y, float z);
    bounding_box_t bounding_box();
private:
    VAO *object;
    static const float AIR_TERMINAL_SPEED = -0.55;
    static const float AIR_DEACCELARATION = 0.01; // This is the deaccelaration per frame(60 frames per second).
};

#endif // BOAT_H
