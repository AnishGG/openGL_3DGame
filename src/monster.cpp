#include "monster.h"
#include "main.h"

Monster::Monster(float x, float y, float z, float rad){
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->part[0] = Sphere(x - rad, y, z, rad);
    this->part[1] = Sphere(x + rad, y, z, rad);
    this->part[2] = Sphere(x, y, z + (float)(sqrt(2)*rad), rad);
}

void Monster::draw(glm::mat4 VP){
//    Matrices.model = glm::mat4(1.0f);
//    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
//    // glm::mat4 translate = glm::translate (glm::vec3(0,0,0));    // glTranslatef
//    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 1));
//    Matrices.model *= (translate * rotate);
//    glm::mat4 MVP = VP * Matrices.model;
//    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i = 0;i < 3; i++)
        this->part[i].draw(VP);
}

void Monster::set_position(float x, float y, float z){
    this->position = glm::vec3(x, y, z);
}

bounding_box_t Monster::bounding_box() {
    float w, h, l;
    float x = this->position.x;
    float y = this->position.y;
    float z = this->position.z;
    w = h = l = 2*this->radius;
    bounding_box_t bbox = {x,y,z,w,h,l};
    return bbox;
}
