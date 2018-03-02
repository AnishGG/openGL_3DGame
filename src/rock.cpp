#include "rock.h"
#include "main.h"

Rock::Rock(float x, float y, float z, float rot, float rad) 
{
    this->position = glm::vec3(x, y, z);
    this->rotation = rot;
    static GLfloat base_vertex_buffer_data[30000];
    int i = 0, flag = 0;
    float change = 50;
    this->radius = rad;
    for (float alpha = 0; alpha < 181.0; alpha += 1)
    {
        glm::vec3 end1 = glm::vec3(x, radius*cos(alpha * PI / 180.0), z);
        glm::vec3 end2 = glm::vec3(x, radius*cos((alpha+1)*PI/180.0), z);

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
    this->object = create3DObject(GL_TRIANGLES, i / 3, base_vertex_buffer_data, COLOR_GRAY);
}

void Rock::draw(glm::mat4 VP) 
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 translate = glm::translate (glm::vec3(0,0,0));    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rock::set_position(float x, float y, float z) 
{
    this->position = glm::vec3(x, y, z);
}
