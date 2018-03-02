#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z, float height);
    glm::vec3 position;
    glm::vec3 speed;
    glm::vec3 accel;
    float rotation, rotation_x;
    void draw(glm::mat4 VP);
    glm::vec3 get_extreme();
    void set_position(float x, float y, float z);
    void tick();
    void left();
    void right();
    void down();
    void up();
    void forward();
    void back();
    void jump();
    void deaccelerate();
private:
    VAO *cannon;
    float net_calculate(float v_x, float v_y);
};

#endif // BOAT_H
