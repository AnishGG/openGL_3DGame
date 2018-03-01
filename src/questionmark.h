#include "main.h"
#include "cannon.h"
#include "sphere.h"

#ifndef QUESTIONMARK_H
#define QUESTIONMARK_H


class QuestionMark {
public:
    QuestionMark() {}
    QuestionMark(float x, float y, float z, float radius);
    glm::vec3 position, end1, end2;
    float rotation, breadth, height_lower_part;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(glm::mat4 VP);
    double speed;
    void left();
    void right();
    void down();
    void up();
    int count;
    float helper;
private:
    VAO *object;
    Cannon make[10101];
    Sphere sphere;
};

#endif // QUESTIONMARK_H
