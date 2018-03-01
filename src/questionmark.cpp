#include "questionmark.h"
#include "main.h"

// Here radius is the radius of the cylinder of the questionmark

QuestionMark::QuestionMark(float x, float y, float z, float radius){
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->breadth  = 0.08;
    this->height_lower_part = 0.9;
    this->count = 0;
    this->helper = 0;
    for(float alpha = 0; alpha < 180.0; alpha += 1){
        glm::vec3 pos = glm::vec3(x + radius*sin(alpha*PI/180.0), y, z + radius*cos(alpha*PI/180.0));
        make[this->count] = Cannon(pos.x, pos.y, pos.z, 0.1/*radius*alpha*/, this->breadth);
        make[this->count].rotation_x += 90;
        make[this->count].rotation_y -= (90 - alpha);
        this->count += 1;
    }
    float h = this->height_lower_part;
    glm::vec3 lower = glm::vec3(x + radius*sin(180*PI/180.0), y, z + radius*cos(180*PI/180.0) - h/2);
    make[this->count] = Cannon(lower.x, lower.y, lower.z, this->height_lower_part, this->breadth);
    make[this->count].rotation_x += 90.0;
    this->count += 1;
    this->sphere = Sphere(lower.x , lower.y, lower.z - h - 0.6, this->breadth);
}

void QuestionMark::draw(glm::mat4 VP) {
    for(int i = 0;i < this->count; i++){
        make[i].draw(VP);
    }
    this->sphere.draw(VP);
}

void QuestionMark::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void QuestionMark::tick(glm::mat4 VP) {
    for(int i = 0;i < this->count; i++){
        make[i].rotate_about_point(VP, this->position, this->helper+=0.001);
    }
}
void QuestionMark::right()
{
    this->position.x += 0.5;
}
void QuestionMark::left()
{
    this->position.x -= 0.5;
}
void QuestionMark::up()
{
    this->position.z += 0.5;
}
void QuestionMark::down()
{
    this->position.z -= 0.5;
}
