#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

//#include <GLFW/glfw3.h>
#include "Circle.h"
#include "Camera.h"
#include "Rectangle.h"
#include "Primitives.h"
#include "PillarManager.h"


class World {
    Camera* camera;
    Shader* shaderProgram;
    Primitives* primitives;
    Circle* circle;

    Rectangle* groundRectangle;
    Rectangle* ceilRectangle;
    PillarManager* pillarManager;


    GLFWwindow& window;
    
    public:
        const float gravity = -0.0025;
        const float jumpForce = 0.015;
        const float spawnInterval = 2.0f;
        World( GLFWwindow& window, int windowWidth, int windowHeight );
        void Start();
        void Update();
        void Destroy();
        bool IsDead();
        void Restart();

        virtual ~World();
};


#endif 