#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float y, float z, float height, float radius){
    this->end1 = glm::vec3(x, y + height/2, z);
    this->end2 = glm::vec3(x, y - height/2, z);
    this->position = glm::vec3(x, y, z);
//    this->rotation = 0;
    static GLfloat base_vertex_buffer_data[10010];
    int i = 0, flag = 0;
    float change = 1;
    for(float theta = 0;theta < 361.0; theta += change, flag++){
        base_vertex_buffer_data[i++] = end1.x - radius*cos(theta * PI / 180.0);
        base_vertex_buffer_data[i++] = end1.y;
        base_vertex_buffer_data[i++] = end1.z - radius*sin(theta * PI / 180.0);

        base_vertex_buffer_data[i++] = end2.x - radius*cos(theta * PI / 180.0);
        base_vertex_buffer_data[i++] = end2.y;
        base_vertex_buffer_data[i++] = end2.z - radius*sin(theta * PI / 180.0);

        if(flag % 2 == 0){
            base_vertex_buffer_data[i++] = end2.x - radius*cos((theta + change) * PI / 180.0);
            base_vertex_buffer_data[i++] = end2.y;
            base_vertex_buffer_data[i++] = end2.z - radius*sin((theta + change) * PI / 180.0);
        }
        else{
            base_vertex_buffer_data[i++] = end1.x - radius*cos((theta - change) * PI / 180.0);
            base_vertex_buffer_data[i++] = end1.y;
            base_vertex_buffer_data[i++] = end1.z - radius*sin((theta - change) * PI / 180.0);
            theta -= change;
        }
    }
    this->object = create3DObject(GL_TRIANGLES, i/3, base_vertex_buffer_data,COLOR_RED);

}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    rotate              = rotate * glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate              = rotate * glm::translate(glm::vec3(-position.x, -position.y, -position.z));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cannon::rotate_about_point(glm::mat4 VP, glm::vec3 point, float rotation){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate              = rotate * glm::translate(glm::vec3(-point.x, -point.y, -point.z));
    rotate              = rotate * glm::rotate((float) (this->rotation_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    rotate              = rotate * glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate              = rotate * glm::translate(glm::vec3(-position.x, -position.y, -position.z));




    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Cannon::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannon::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
void Cannon::right()
{
    this->position.x += 0.5;
}
void Cannon::left()
{
    this->position.x -= 0.5;
}
void Cannon::up()
{
    this->position.z += 0.5;
}
void Cannon::down()
{
    this->position.z -= 0.5;
}
