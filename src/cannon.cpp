#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = glm::vec3(0, 0, 0);
    this->accel = glm::vec3(0, 0, 0);

    GLfloat cannon_vertex_buffer_data[7000];
    int i = 0, flag = 0;
    float angle = 1;
    float radius = 0.3;
    for (float theta = 0; theta < 361.0; theta += angle, flag++)
    {
        cannon_vertex_buffer_data[i++] = 0.0 - radius * cos(theta * M_PI / 180.0);
        cannon_vertex_buffer_data[i++] = 3.0;
        cannon_vertex_buffer_data[i++] = 1.0 - radius * sin(theta * M_PI / 180.0);

        cannon_vertex_buffer_data[i++] =  0.0- radius * cos(theta * M_PI / 180.0);
        cannon_vertex_buffer_data[i++] = 6.0;
        cannon_vertex_buffer_data[i++] = 2.0 - radius * sin(theta * M_PI / 180.0);

        if (flag % 2 == 0)
        {
            cannon_vertex_buffer_data[i++] = 0.0 - radius * cos((theta + angle) * M_PI / 180.0);
            cannon_vertex_buffer_data[i++] = 6.0;
            cannon_vertex_buffer_data[i++] = 2.0 - radius * sin((theta + angle) * M_PI / 180.0);
        }
        else
        {
            cannon_vertex_buffer_data[i++] = 0.0 - radius * cos((theta - angle) * M_PI / 180.0);
            cannon_vertex_buffer_data[i++] = 3.0;
            cannon_vertex_buffer_data[i++] = 1.0 - radius * sin((theta - angle) * M_PI / 180.0);
            theta -= angle;
        }
    }
    this->cannon = create3DObject(GL_TRIANGLES, i/3, cannon_vertex_buffer_data, COLOR_BLACK); 
}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, -1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->cannon);
}

void Cannon::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void Cannon::tick()
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
}
void Cannon::jump()
{
    if(this->position.z <= 0)
        this->speed.z = 2; 
}
void Cannon::right()
{
    this->rotation += 0.5;
}
void Cannon::left()
{
    this->rotation -= 0.5;
}
void Cannon::up()
{
    this->position.z += 0.5; 
}
void Cannon::down()
{
    this->position.z -= 0.5;
}
void Cannon::forward()
{
    this->position.y += 0.5*cos(this->rotation*PI/180.0);
    this->position.x += 0.5*sin(this->rotation*PI/180.0);
}
void Cannon::back()
{
    this->position.y -= 0.5*cos(this->rotation*PI/180.0);
    this->position.x -= 0.5*sin(this->rotation*PI/180.0);
}

float net_calculate(float v_x, float v_y){
    return sqrt(v_x*v_x + v_y*v_y);
}
