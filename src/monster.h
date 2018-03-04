#include "main.h"
#include "sphere.h"

#ifndef MONSTER_H
#define MONSTER_H

class Monster
{
  public:
    Monster() {}
    Monster(float x, float y, float z, float siz);
    glm::vec3 position;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t bounding_box();
    Sphere part[4];

  private:
    VAO *object;
};

#endif // BOAT_H
