#include "main.h"
#include "timer.h"
#include "boat.h"
#include "water.h"
#include "rock.h"
#include "cannon.h"
#include "monster.h"
#include "score.h"
#include "digit.h"
#include "display.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

long long time_count;
Boat boat1;
Water water1;
Boat boat2;
Cannon cannon1;
Score score;
Display display;
vector<Rock> rocks(250);
vector<Monster> monsters(5);

glm::vec3 eye,target,up;

int defView = 0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

double getRandDouble(double l, double r)
{
    return l + (((double)rand()) / RAND_MAX) * (r - l);
}

Timer t60(1.0 / 60);
Timer t1(1.0/1.0);


/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() 
{
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    switch (defView)
    {
    case 0:
        eye = glm::vec3(boat1.position.x, boat1.position.y - 15, boat1.position.z + 10);
        target = glm::vec3(boat1.position.x, boat1.position.y + 5, boat1.position.z);
        up = glm::vec3(0, 0, 1);
        break;
    case 1:
        eye = glm::vec3(boat1.position.x, boat1.position.y + 2*cos(boat1.rotation*PI/180.0), boat1.position.z + 3);
        target = glm::vec3(boat1.position.x + 2*sin(boat1.rotation*PI/180.0), (boat1.position.y + 4.0*cos(boat1.rotation*PI/180.0)), boat1.position.z + 2 + fabs(sin(boat1.rotation*PI/180.0)));
        up = glm::vec3(0, 0, 1);
        break;
    case 2:
        eye = glm::vec3(boat1.position.x, boat1.position.y - 20, boat1.position.z + 50);
        target = glm::vec3(boat1.position.x, boat1.position.y, boat1.position.z);
        up = glm::vec3(0, 0, 1);
        break;
    case 3:
        eye = glm::vec3(-20, -50, 50);
        target = glm::vec3(boat1.position.x, boat1.position.y, boat1.position.z);
        up = glm::vec3(0, 0, 1);
        break;
    }
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    Matrices.projection = glm::perspective(1.0f, 1.0f, 0.1f, 500.0f);
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    for(int i = 0;i < monsters.size(); i++){
        monsters[i].draw(VP);
    }
    water1.draw(VP);
    boat1.draw(VP);
    for(int i=0;i<rocks.size();i++){
        rocks[i].draw(VP);
    }
    /* To render the score of the player */
    char test[10];
    sprintf(test, "%d", score.get_score());
    display.store(test, 10, 3);
    display.draw(VP);
}

void myfun(GLFWwindow *window){
    int view = glfwGetKey(window, GLFW_KEY_C);
    if(view){
        defView = (defView + 1)%4;
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int Up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int forward = glfwGetKey(window, GLFW_KEY_W);
    int back = glfwGetKey(window, GLFW_KEY_S);
    int jump = glfwGetKey(window, GLFW_KEY_SPACE);
    int fire = glfwGetKey(window, GLFW_KEY_F);
    int rotate = glfwGetKey(window, GLFW_KEY_B);
    if(fire){
        glm::vec3 hell = boat1.release_fireball();
    }
    if(rotate){
        boat1.rotation += 0.1;
        boat1.cannon.rotation += 0.1;
    }
    if (left) {
        boat1.left();
    }
    if(right){
        boat1.right();
    }
    if(Up){
        boat1.up();
    }
    if(down){
        boat1.down();
    }
    if(forward){
        boat1.forward();
    }
    if(back){
        boat1.back();
    }
    if(jump){
        boat1.jump();
    }
}

void tick_elements() {
    boat1.tick();
    int count = 0;
    for(int i = 0;i < rocks.size(); i++){
        if(detect_collision(boat1.bounding_box(), rocks[i].bounding_box())){
            boat1.set_speed(glm::vec3(0, 0, 0));
            boat1.stop_wind();
            count++;
            if(!boat1.is_collided)
                score.subtract(1);
        }
    }
    /* To handle multiple subtraction of score by collision with only one rock */
    if(count == 0)
        boat1.is_collided = 0;
    else
        boat1.is_collided = 1;
    /**************************************************************************/
    if(boat1.is_fireball_present){
        for(int i = 0;i < monsters.size(); i++){
            if(detect_collision(boat1.fireball.bounding_box(), monsters[i].bounding_box())){
                cout << "Monster Killed" << endl;
                monsters.erase(monsters.begin() + i);
                score.add(5);
            }
        }
    }
    cout << score.get_score() << endl;
    for(int i = 0;i < monsters.size(); i++){
        if(detect_collision(boat1.bounding_box(), monsters[i].bounding_box())){
            monsters.erase(monsters.begin() + i);
            score.subtract(2);
        }
    }
}

//8930375999

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    time_count = 0;
    water1 = Water(0, 0, -2,500);
    boat1 = Boat(0, 0, 0);
    boat1.add_cannon(0, 0, 0, 3);
    boat1.add_poal(0, 0, 0, 8, 0.1);
    boat1.add_sail();

    /* Initialising monsters */
    for(int i = 0;i < monsters.size(); i++){
        monsters[i] = Monster(getRandDouble(-water1.size / 5, water1.size / 5),
                              getRandDouble(-water1.size / 5, water1.size / 5),
                              0,
                              getRandDouble(1, 3));
    }
    /************************/
    /* Initialising rocks */
    for(int i=0;i<rocks.size();i++){
        rocks[i] = Rock( 
            getRandDouble(-water1.size, water1.size), 
            getRandDouble(-water1.size, water1.size), 
            -2, 
            getRandDouble(0,360),
            getRandDouble(2, 5)
            );
    }
    /*********************************/
    /* Initialising the score displaying part */
    score = Score();
    display = Display();
    eye = glm::vec3(boat1.position.x, boat1.position.y - 15, boat1.position.z + 10);
    target = glm::vec3(boat1.position.x, boat1.position.y + 5, boat1.position.z);
    up = glm::vec3(0, 0, 1);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv){
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)){
        // Process timers

        if (t60.processTick()){
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }
        if(t1.processTick()){
            time_count++;
            myfun(window);
            /* To initiate the wind effect uncomment this*/
//            if(time_count % 10 == 0)
//                boat1.stop_wind();
//            else if(time_count % 5 == 0)
//                boat1.blow_wind();
            /*********************************************/
        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
        return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
            (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
            (abs(a.z - b.z) * 2 < (a.length + b.length));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    // Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
