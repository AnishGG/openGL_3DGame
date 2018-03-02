#include "main.h"
#include "cannon.h"
#include "cylinder.h"
#include "sphere.h"

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
    void set_speed(glm::vec3 speed);
    void add_cannon(float x, float y, float z, float height);
    void add_poal(float x, float y, float z, float height, float radius);
    glm::vec3 release_fireball();
    bool is_cannon_added, is_pole_added, is_fireball_present;
    bounding_box_t bounding_box();
    void tick();
    void left();
    void right();
    void down();
    void up();
    void forward();
    void back();
    void jump();
    void deaccelerate();
    Cannon cannon;
    Cylinder pole;
    Sphere fireball;
private:
    VAO *base;
    VAO *side;
    VAO *face;
    static const float FIRE_BALL_SPEED = 0.7; // This is the deaccelaration per frame(60 frames per second).
//    VAO *pole;

};

#endif // BOAT_H
