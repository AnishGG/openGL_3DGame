#include "main.h"
#include "cannon.h"
#include "cylinder.h"
#include "sphere.h"

#ifndef SAIL_H
#define SAIL_H


class Sail {
public:
    Sail() {}
    Sail(glm::vec3 one, glm::vec3 two, glm::vec3 three, glm::vec3 rotation_point);
    glm::vec3 position;
    glm::vec3 speed;
    glm::vec3 accel;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void set_speed(glm::vec3 speed);
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
    VAO *base;
};

#endif // SAIL_H
