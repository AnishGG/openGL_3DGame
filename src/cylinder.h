#include "main.h"

#ifndef CYLINDER_H
#define CYLINDER_H


class Cylinder {
public:
    Cylinder() {}
    Cylinder(float x, float y, float z, float height, float radius);
    glm::vec3 position;
    glm::vec3 speed;
    glm::vec3 accel;
    float rotation, rotation_x;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    void left();
    void right();
    void down();
    void up();
    void forward();
    void back();
    void jump();
private:
    VAO *cannon;
};

#endif // BOAT_H
