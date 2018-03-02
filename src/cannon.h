#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z);
    glm::vec3 position;
    glm::vec3 speed;
    glm::vec3 accel;
    float rotation;
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
    float net_calculate(float v_x, float v_y);
};

#endif // BOAT_H
