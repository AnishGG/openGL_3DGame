#include "main.h"

#ifndef SPHERE_H
#define SPHERE_H


class Sphere {
public:
    Sphere() {}
    Sphere(float x, float y, float z, float radius);
    glm::vec3 position, end1, end2;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    void left();
    void right();
    void down();
    void up();
private:
    VAO *object;
};

#endif // BOAT_H
