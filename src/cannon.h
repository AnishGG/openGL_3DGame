#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z, float height, float radius);
    glm::vec3 position, end1, end2;
    float rotation_x, rotation_y;
    void draw(glm::mat4 VP);
    void rotate_about_point(glm::mat4 VP, glm::vec3 point, float rotation);
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
