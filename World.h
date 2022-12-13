#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

//#include <GLFW/glfw3.h>
#include "Circle.h"
#include "Camera.h"
#include "Rectangle.h"
#include "Primitives.h"



class World {
    Camera* camera;
    Shader* shaderProgram;
    Primitives* primitives;
    Circle* circle;
    Rectangle* rectangle;

    GLFWwindow& window;
    
    public:
        float gravity = -0.0025;
        float jumpForce = 0.015;
        World( GLFWwindow& window, int windowWidth, int windowHeight );
        void Start();
        void Update();
        void Destroy();

        virtual ~World();
};


#endif 