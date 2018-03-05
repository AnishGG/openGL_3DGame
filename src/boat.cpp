#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->wind_speed = glm::vec3(0, 0, 0);
    this->rotation = 0;
    this->speed = glm::vec3(0, 0, 0);
    this->accel = glm::vec3(0, 0, 0);
    this->is_cannon_added = 0;
    this->is_pole_added = 0;
    this->is_fireball_present = 0;
    this->is_sail_added = 0;
    this->is_wind_blowing = 0;
    this->is_collided = 0;

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

    this->base = create3DObject(GL_TRIANGLES, 2 * 3, base_vertex_buffer_data, COLOR_BROWN3);
    this->side = create3DObject(GL_TRIANGLES, 4 * 3, side_vertex_buffer_data,COLOR_PINK);
    this->face = create3DObject(GL_TRIANGLES, 6 * 3, face_vertex_buffer_data, COLOR_YELLOW);
}

void Boat::draw(glm::mat4 VP) {
    if(this->is_cannon_added)
        this->cannon.draw(VP);
    if(this->is_pole_added)
        this->pole.draw(VP);
    if(this->is_fireball_present)
        this->fireball.draw(VP);
    if(this->is_sail_added)
        this->sail.draw(VP);
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
}

void Boat::set_position(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
    this->cannon.set_position(x, y, z);
    this->pole.set_position(x, y, z);
}

void Boat::set_speed(glm::vec3 speed){
    this->speed = speed;
    this->pole.speed = speed;
    this->cannon.speed = speed;
}

void Boat::tick() 
{
    this->position += this->speed + this->wind_speed;
    if(this->is_sail_added){
        this->sail.position = this->position;
        this->sail.rotation = this->rotation;
    }
    if(this->is_cannon_added){
        this->cannon.position = this->position;
        this->cannon.rotation = this->rotation;
    }
    if(this->is_pole_added){
        this->pole.position = this->position;
        this->pole.rotation = this->rotation;
    }
    this->speed += this->accel;
    this->deaccelerate();
    if(this->is_fireball_present){
        if(this->fireball.position.z < -1.5)
            this->is_fireball_present = 0;
        this->fireball.tick();
    }
}

void Boat::deaccelerate(){
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

void Boat::blow_wind(){
    float net_speed = 0.2;
    float angle = rand() % 360 + 1;
    this->wind_speed.x = net_speed * cos(angle * PI / 180.0);
    this->wind_speed.y = net_speed * sin(angle * PI / 180.0);
    this->is_wind_blowing = 1;
    this->sail.rotation = angle;
}

void Boat::stop_wind(){
    this->wind_speed = glm::vec3(0, 0, 0);
    this->is_wind_blowing = 0;
}

void Boat::add_cannon(float x, float y, float z, float height){
    this->cannon = Cannon(x, y, z, height);
    this->is_cannon_added = 1;
}

void Boat::add_poal(float x, float y, float z, float height, float radius){
    this->pole = Cylinder(x, y, z, height, radius);
    this->is_pole_added = 1;
    this->pole.rotation_x = 90;
}

void Boat::add_sail(){
    glm::vec3 pole_end1 = glm::vec3(this->pole.position.x, this->pole.position.z - 1.5, 3.0 + this->pole.position.y - this->pole.height/2 + 0.9);
    glm::vec3 pole_end2 = glm::vec3(this->pole.position.x, this->pole.position.z - 1.5, 3.0 + this->pole.position.y + this->pole.height/2);
    glm::vec3 third = glm::vec3(this->pole.position.x, 1.5 + this->pole.position.z, 3.0 + this->pole.position.y - this->pole.height/2 + 0.9);
    glm::vec3 rotation_cord = this->position;
    this->sail = Sail(pole_end1, pole_end2, third, rotation_cord);
    this->is_sail_added = 1;
}

glm::vec3 Boat::release_fireball(){
    if(this->is_fireball_present && fireball.position.z > -1.0){
        return glm::vec3(0, 0, 0);
    }
    glm::vec3 pos = this->cannon.get_extreme();
    this->fireball = Sphere(pos.x, pos.y, pos.z, 1.0);
    float s_x = FIRE_BALL_SPEED*sin(this->rotation*PI/180.0) + this->speed.x;
    float s_y = FIRE_BALL_SPEED*cos(this->rotation*PI/180.0) + this->speed.y;
    float s_z = 0.2 + std::min(this->speed.z, (float)0.4);
    this->fireball.set_speed(s_x, s_y, s_z);
    this->is_fireball_present = 1;
    return pos;
}

void Boat::jump()
{
    if(this->position.z <= 0)
        this->speed.z = 2; 
}
void Boat::right() 
{
    this->rotation += 0.6;
}
void Boat::left()
{
    this->rotation -= 0.6;
}
void Boat::up()
{
    this->position.z += 0.5;
}
void Boat::down()
{
    this->position.z -= 0.5;
}
void Boat::forward()
{
    if(fabs(speed.y) < 0.5)
        this->speed.y += 0.05*cos(this->rotation*PI/180.0);
    if(fabs(speed.x) < 0.5)
        this->speed.x += 0.05*sin(this->rotation*PI/180.0);
}
void Boat::back()
{
    if(-fabs(speed.y) > -0.5)
        this->speed.y -= 0.05*cos(this->rotation*PI/180.0);
    if(-fabs(speed.x) > -0.5)
        this->speed.x -= 0.05*sin(this->rotation*PI/180.0);
}

bounding_box_t Boat::bounding_box() {
    float x = this->position.x;
    float y = this->position.y;
    float z = this->position.z;
    float w = 4;
    float h = 3;
    float l = 8;
    bounding_box_t bbox = { x,y,z,w,h,l};
    return bbox;
}
