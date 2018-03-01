#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat base_vertex_buffer_data[] = {
        -1.0f, -2.0f, -1.0f,
        1.0f, -2.0f, -1.0f,
        -1.0f, 2.0f, -1.0f,

        -1.0f, 2.0f, -1.0f,
        1.0f, 2.0f, -1.0f,
        1.0f, -2.0f, -1.0f
    };
    GLfloat side_vertex_buffer_data[] = {
        -1.0f, -2.0f, -1.0f,
        -1.0f, 2.0f, -1.0f,
        -2.0f, 3.0f, 1.0f,

        -1.0f, -2.0f, -1.0f,
        -2.0f, 3.0f, 1.0f,
        -2.0f, -3.0f, 1.0f,

        1.0f, -2.0f, -1.0f,
        1.0f, 2.0f, -1.0f,
        2.0f, 3.0f, 1.0f,

        1.0f, -2.0f, -1.0f,
        2.0f, 3.0f, 1.0f,
        2.0f, -3.0f, 1.0f,

    };
    GLfloat face_vertex_buffer_data[] = {
        -2.0f, -3.0f, 1.0f,
        -1.0f, -2.0f, -1.0f,
        0.0f, -4.0f, 2.0f,

        2.0f, -3.0f, 1.0f,
        1.0f, -2.0f, -1.0f,
        0.0f, -4.0f, 2.0f,

        0.0f, -4.0f, 2.0f,
        -1.0f, -2.0f, -1.0f,
        1.0f, -2.0f, -1.0f,

         -2.0f, 3.0f, 1.0f,
        -1.0f, 2.0f, -1.0f,
        0.0f, 4.0f, 2.0f,

        2.0f, 3.0f, 1.0f,
        1.0f, 2.0f, -1.0f,
        0.0f, 4.0f, 2.0f,

        0.0f, 4.0f, 2.0f,
        -1.0f, 2.0f, -1.0f,
        1.0f, 2.0f, -1.0f,

    };

    this->base = create3DObject(GL_TRIANGLES, 2 * 3, base_vertex_buffer_data, COLOR_BLACK);
    this->side = create3DObject(GL_TRIANGLES, 4 * 3, side_vertex_buffer_data,COLOR_RED);
    this->face = create3DObject(GL_TRIANGLES, 6 * 3, face_vertex_buffer_data,COLOR_GREEN);
    
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->base);
    draw3DObject(this->side);
    draw3DObject(this->face);/*
    gluCylinder(this->quadratic,0.1f,0.1f,3.0f,32,32);
    glTranslatef(0.0f,5.0f, 0.0f);*/
}

void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
void Boat::right() 
{
    this->position.x += 0.5;
}
void Boat::left()
{
    this->position.x -= 0.5;
}
void Boat::up()
{
    this->position.y += 0.5;
}
void Boat::down()
{
    this->position.y -= 0.5;
}

