#include "sail.h"
#include "main.h"

Sail::Sail(glm::vec3 one, glm::vec3 two, glm::vec3 three, glm::vec3 rotation_point) {
    glm::vec3 r = rotation_point;
    this->position = glm::vec3(r.x, r.y, r.z);
    this->rotation = 0;
    this->speed = glm::vec3(0, 0, 0);
    this->accel = glm::vec3(0, 0, 0);

    GLfloat base_vertex_buffer_data[] = {
        one.x  , one.y  , one.z,
        two.x  , two.y  , two.z,
        three.x, three.y, three.z
    };
    this->base = create3DObject(GL_TRIANGLES, 3, base_vertex_buffer_data, COLOR_WHITE);
}

void Sail::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, -1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
//     rotate          = rotate * glm::translate(this->position);
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->base);
}

void Sail::set_position(float x, float y, float z){
    this->position = glm::vec3(x, y, z);
}

void Sail::set_speed(glm::vec3 speed){
    this->speed = speed;
}

void Sail::tick(){
    this->position += this->speed;
    this->speed += this->accel;
    this->deaccelerate();
}

void Sail::deaccelerate(){
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

void Sail::jump(){
    if(this->position.z <= 0)
        this->speed.z = 2;
}

void Sail::right(){
    this->rotation += 0.5;
}

void Sail::left(){
    this->rotation -= 0.5;
}

void Sail::up(){
    this->position.z += 0.5;
}

void Sail::down(){
    this->position.z -= 0.5;
}

void Sail::forward(){
    if(fabs(speed.y) < 0.5)
        this->speed.y += 0.05*cos(this->rotation*PI/180.0);
    if(fabs(speed.x) < 0.5)
        this->speed.x += 0.05*sin(this->rotation*PI/180.0);
}

void Sail::back(){
    if(-fabs(speed.y) > -0.5)
        this->speed.y -= 0.05*cos(this->rotation*PI/180.0);
    if(-fabs(speed.x) > -0.5)
        this->speed.x -= 0.05*sin(this->rotation*PI/180.0);
}
