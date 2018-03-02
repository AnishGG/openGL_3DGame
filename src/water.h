#include "main.h"

#ifndef WATER_H
#define WATER_H

class Water
{
    public:
    Water() {}
    Water(float x, float y, float z,float size);
    glm::vec3 position;
    float rotation;
    float size;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    void left();
    void right();

    private:
    VAO* surface;
    VAO* base;

};

#endif // BOAT_H
