#include "cylinder.h"
#include "main.h"

Cylinder::Cylinder(float x, float y, float z, float height, float radius) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotation_x = 0;
    this->speed = glm::vec3(0, 0, 0);
    this->accel = glm::vec3(0, 0, 0);
    glm::vec3 end1 = glm::vec3(x, 3.0 + y - height/2, 1.5 + z);
    glm::vec3 end2 = glm::vec3(x, 3.0 + y + height/2, 1.5 + z);

    GLfloat cannon_vertex_buffer_data[7000];
    int i = 0, flag = 0;
    float angle = 1;
    for (float theta = 0; theta < 361.0; theta += angle, flag++)
    {
        cannon_vertex_buffer_data[i++] = end1.x - radius * cos(theta * M_PI / 180.0);
        cannon_vertex_buffer_data[i++] = end1.y;
        cannon_vertex_buffer_data[i++] = end1.z - radius * sin(theta * M_PI / 180.0);

        cannon_vertex_buffer_data[i++] =  end2.x - radius * cos(theta * M_PI / 180.0);
        cannon_vertex_buffer_data[i++] = end2.y;
        cannon_vertex_buffer_data[i++] = end2.z - radius * sin(theta * M_PI / 180.0);

        if (flag % 2 == 0)
        {
            cannon_vertex_buffer_data[i++] = end2.x - radius * cos((theta + angle) * M_PI / 180.0);
            cannon_vertex_buffer_data[i++] = end2.y;
            cannon_vertex_buffer_data[i++] = end2.z - radius * sin((theta + angle) * M_PI / 180.0);
        }
        else
        {
            cannon_vertex_buffer_data[i++] = end1.x - radius * cos((theta - angle) * M_PI / 180.0);
            cannon_vertex_buffer_data[i++] = end1.y;
            cannon_vertex_buffer_data[i++] = end1.z - radius * sin((theta - angle) * M_PI / 180.0);
            theta -= angle;
        }
    }
    this->cannon = create3DObject(GL_TRIANGLES, i/3, cannon_vertex_buffer_data, COLOR_GREEN);
}

void Cylinder::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, -1));
    rotate              = rotate * glm::rotate((float) (this->rotation_x * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->cannon);
}

void Cylinder::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void Cylinder::tick()
{
    this->position += this->speed;
    this->speed += this->accel;
    this->deaccelerate();
}

void Cylinder::deaccelerate(){
    /* Changing the deaccelaration for the jump of the boat */
    if(this->position.z < 0){
        if(this->accel.z < 0){
            this->accel.z = 0;
            this->speed.z = 0;
        }
        if(this->position.z <= -1){
            this->speed.z = 0.1;
        }
    }
    if(this->position.z > 0){
        this->accel.z = -0.1;
    }
    /********************************************************/
    if(this->speed.x > 0.0001)
        speed.x -= 0.005;
    else if(this->speed.x < -0.0001)
        speed.x += 0.005;
    if(this->speed.y > 0.0001)
        speed.y -= 0.005;
    else if(speed.y < 0.0001)
        speed.y += 0.005;
}

void Cylinder::jump()
{
    if(this->position.z <= 0)
        this->speed.z = 2; 
}
void Cylinder::right()
{
    this->rotation += 0.5;
}
void Cylinder::left()
{
    this->rotation -= 0.5;
}
void Cylinder::up()
{
    this->position.z += 0.5; 
}
void Cylinder::down()
{
    this->position.z -= 0.5;
}
void Cylinder::forward()
{
    if(fabs(speed.y) < 0.5)
        this->speed.y += 0.05*cos(this->rotation*PI/180.0);
    if(fabs(speed.x) < 0.5)
        this->speed.x += 0.05*sin(this->rotation*PI/180.0);
}
void Cylinder::back()
{
    if(-fabs(speed.y) > -0.5)
        this->speed.y -= 0.05*cos(this->rotation*PI/180.0);
    if(-fabs(speed.x) > -0.5)
        this->speed.x -= 0.05*sin(this->rotation*PI/180.0);
}
