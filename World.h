#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

//#include <GLFW/glfw3.h>
#include "Circle.h"
#include "Camera.h"




class World {
    Camera* camera;
    Shader* shaderProgram;
    Circle* circle;
    GLFWwindow* window;
    public:
        float gravity =  -0.0025;
        World( GLFWwindow* window, int windowWidth, int windowHeight );
        void Start();
        void Update();
        void Destroy();

        virtual ~World();
};


#endif 