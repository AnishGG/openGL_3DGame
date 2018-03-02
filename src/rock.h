#include "main.h"

#ifndef ROCK_H
#define ROCK_H

class Rock
{
  public:
    Rock() {}
    Rock(float x, float y, float z, float rot, float siz);
    glm::vec3 position;
    // glm::vec3 speed;
    // glm::vec3 accel;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t bounding_box();

  private:
    VAO *object;
    // VAO *base;
    // VAO *side;
    // VAO *face;
    // VAO *pole;
};

#endif // BOAT_H
