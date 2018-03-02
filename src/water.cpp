#include "water.h"
#include "main.h"

Water::Water(float x, float y, float z,float siz) 
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->size = siz;
    GLfloat surface_vertex_buffer_data[] = {
        -size*1.0f, -size*1.0f, 0.0f,
        -size*1.0f, size*1.0f, 0.0f,
        size*1.0f,  size*1.0f, 0.0f,

        size*1.0f,  size*1.0f, 0.0f,
        size*1.0f,  -size*1.0f, 0.0f,
        -size*1.0f, -size*1.0f, 0.0f,
    };
    GLfloat base_vertex_buffer_data[] ={
        -size*1.0f, -size*1.0f, -10.0f,
        -size*1.0f, size*1.0f, -10.0f,
        size*1.0f,  size*1.0f, -10.0f,

        size*1.0f,  size*1.0f, -10.0f,
        size*1.0f,  -size*1.0f, -10.0f,
        -size*1.0f, -size*1.0f, -10.0f,

    };
    // Glfloat side_vertex_buffer_data[] ={

    // };
    this->surface = create3DObject(GL_TRIANGLES, 2 * 3, surface_vertex_buffer_data, COLOR_BLUE);
    this->base = create3DObject(GL_TRIANGLES, 2 * 3, base_vertex_buffer_data, COLOR_BLACK);
}

void Water::draw(glm::mat4 VP) 
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->base);
    draw3DObject(this->surface);
}

void Water::set_position(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
}

void Water::tick() 
{

}