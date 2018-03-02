#include "sphere.h"
#include "main.h"

Sphere::Sphere(float x, float y, float z, float radius){
    this->speed = glm::vec3(0, 0, 0);
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    static GLfloat base_vertex_buffer_data[5000100];
    int i = 0, flag = 0;
    float change = 10;
    for(float alpha = 0;alpha < 181.0; alpha+=1){
        this->end1 = glm::vec3(x, radius*cos(alpha * PI / 180.0), z);
        this->end2 = glm::vec3(x, radius*cos((alpha+1)*PI/180.0), z);

        float c_radius = radius * sin(alpha * PI / 180.0);
        float d_radius = radius * sin((alpha+1) * PI / 180.0);

        flag = 0;
        for(float theta = 0;theta < 361.0; theta += change, flag++){
            base_vertex_buffer_data[i++] = c_radius*cos(theta * PI / 180.0);
            base_vertex_buffer_data[i++] = end1.y;
            base_vertex_buffer_data[i++] = c_radius*sin(theta * PI / 180.0);

            base_vertex_buffer_data[i++] = d_radius*cos(theta * PI / 180.0);
            base_vertex_buffer_data[i++] = end2.y;
            base_vertex_buffer_data[i++] = d_radius*sin(theta * PI / 180.0);

            if(flag % 2 == 0){
                base_vertex_buffer_data[i++] = d_radius*cos((theta + change) * PI / 180.0);
                base_vertex_buffer_data[i++] = end2.y;
                base_vertex_buffer_data[i++] = d_radius*sin((theta + change) * PI / 180.0);
            }
            else{
                base_vertex_buffer_data[i++] = c_radius*cos((theta - change) * PI / 180.0);
                base_vertex_buffer_data[i++] = end1.y;
                base_vertex_buffer_data[i++] = c_radius*sin((theta - change) * PI / 180.0);
                theta -= change;
            }
        }
    }
    this->object = create3DObject(GL_TRIANGLES, i/3, base_vertex_buffer_data,COLOR_RED);

}

void Sphere::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Sphere::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Sphere::tick() {
    this->position += this->speed;
    this->decelarate();
}

void Sphere::decelarate(){
    if(this->speed.z > AIR_TERMINAL_SPEED){
        this->speed.z -= AIR_DEACCELARATION;
    }
    /* Setting limits for speed in x and y direction */
    if(this->speed.x > 0.005)
        this->speed.x -= 0.005;
    else if(this->speed.x < -0.005)
        this->speed.x += 0.005;
    else
        this->speed.x = 0;
    if(this->speed.y > 0.005)
        this->speed.y -= 0.005;
    else if(this->speed.y < -0.005)
        this->speed.y += 0.005;
    else
        this->speed.y = 0;
    /**************************************************/
}

void Sphere::set_speed(float x, float y, float z){
    this->speed = glm::vec3(x, y, z);
}

void Sphere::right()
{
    this->position.x += 0.5;
}
void Sphere::left()
{
    this->position.x -= 0.5;
}
void Sphere::up()
{
    this->position.z += 0.5;
}
void Sphere::down()
{
    this->position.z -= 0.5;
}
