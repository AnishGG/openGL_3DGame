#include "main.h"
#include "cannon.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z);
    glm::vec3 position;
    glm::vec3 speed;
    glm::vec3 accel;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void add_cannon(float x, float y, float z);
    bool is_cannon_added;
    void tick();
    void left();
    void right();
    void down();
    void up();
    void forward();
    void back();
    void jump();
    Cannon cannon;
private:
    VAO *base;
    VAO *side;
    VAO *face;
    VAO *pole;

};

#endif // BOAT_H
