#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = glm::vec3(0, 0, 0);
    this->accel = glm::vec3(0, 0, 0);
    this->is_cannon_added = 0;

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
    GLfloat pole_vertex_buffer_data[] = {
        0.1f, 1.9f, -1.0f,
        -0.1f, 1.9f, -1.0f,
        0.1f, 1.7f, -1.0f,

        -0.1f, 1.9f, -1.0f,
        -0.1f, 1.7f, -1.0f,
        0.1f, 1.7f, -1.0f,

        0.1f, 1.9f, 6.0f,
        -0.1f, 1.9f, 6.0f,
        0.1f, 1.7f, 6.0f,

        -0.1f, 1.9f, 6.0f,
        -0.1f, 1.7f, 6.0f,
        0.1f, 1.7f, 6.0f,

        0.1f, 1.9f, -1.0f,
        0.1f, 1.7f, -1.0f,
        0.1f, 1.9f, 6.0f,

        0.1f, 1.7f, -1.0f,
        0.1f, 1.7f, 6.0f,
        0.1f, 1.9f, 6.0f,

        -0.1f, 1.9f, -1.0f,
        -0.1f, 1.7f, -1.0f,
        -0.1f, 1.9f, 6.0f,

        -0.1f, 1.7f, -1.0f,
        -0.1f, 1.7f, 6.0f,
        -0.1f, 1.9f, 6.0f,

        0.1f, 1.9f, -1.0f,
        -0.1f, 1.9f, -1.0f,
        -0.1f, 1.9f, 6.0f,

        -0.1f, 1.9f, 6.0f,
        0.1f, 1.9f, 6.0f,
        0.1f, 1.9f, -1.0f,

        0.1f, 1.7f, -1.0f,
        -0.1f, 1.7f, -1.0f,
        -0.1f, 1.7f, 6.0f,

        -0.1f, 1.7f, 6.0f,
        0.1f, 1.7f, 6.0f,
        0.1f, 1.7f, -1.0f,

        

    };
    this->base = create3DObject(GL_TRIANGLES, 2 * 3, base_vertex_buffer_data, COLOR_BROWN3);
    this->side = create3DObject(GL_TRIANGLES, 4 * 3, side_vertex_buffer_data,COLOR_PINK);
    this->face = create3DObject(GL_TRIANGLES, 6 * 3, face_vertex_buffer_data, COLOR_YELLOW);
    this->pole = create3DObject(GL_TRIANGLES, 10 * 3, pole_vertex_buffer_data, COLOR_GREEN); 
}

void Boat::draw(glm::mat4 VP) {
    this->cannon.draw(VP);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, -1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->base);
    draw3DObject(this->side);
    draw3DObject(this->face);
    draw3DObject(this->pole);
}

void Boat::set_position(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
    this->cannon.set_position(x, y, z);
}

void Boat::tick() 
{
    this->position += this->speed;
    this->speed += this->accel;
    if(this->position.z < 0)
    {
        if(this->accel.z < 0)
        {
            this->accel.z = 0;
            this->speed.z = 0;
        }
        if(this->position.z <= -1)
        {
            this->speed.z = 0.1;
        }
    }
    if(this->position.z > 0)
    {
        this->accel.z = -0.1;
    }
    if(this->is_cannon_added)
        this->cannon.tick();
}

void Boat::add_cannon(float x, float y, float z){
    this->cannon = Cannon(x, y, z);
    this->is_cannon_added = 1;
}

void Boat::jump()
{
    if(this->position.z <= 0)
        this->speed.z = 2; 
    if(this->is_cannon_added)
        this->cannon.jump();
}
void Boat::right() 
{
    this->rotation += 0.5;
//    this->position.x += 0.5;
    if(this->is_cannon_added)
        this->cannon.right();
}
void Boat::left()
{
    this->rotation -= 0.5;
//    this->position.x -= 0.5;
    if(this->is_cannon_added)
        this->cannon.left();
}
void Boat::up()
{
    this->position.z += 0.5;
    if(this->is_cannon_added)
        this->cannon.up();
}
void Boat::down()
{
    this->position.z -= 0.5;
    if(this->is_cannon_added)
        this->cannon.down();
}
void Boat::forward()
{
        this->position.y += 0.5*cos(this->rotation*PI/180.0);
        this->position.x += 0.5*sin(this->rotation*PI/180.0);
    if(this->is_cannon_added)
        this->cannon.forward();
}
void Boat::back()
{
    this->position.y -= 0.5*cos(this->rotation*PI/180.0);
    this->position.x -= 0.5*sin(this->rotation*PI/180.0);
    if(this->is_cannon_added)
        this->cannon.back();
}
