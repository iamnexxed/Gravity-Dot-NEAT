#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

//#include <GLFW/glfw3.h>
#include "Circle.h"
#include "Camera.h"
#include "Rectangle.h"
#include "Primitives.h"
#include "PillarManager.h"
#include "NeuroEvolution.h"


class World {
    Camera* camera;
    Shader* shaderProgram;
    Shader* selectShader;

    Shader* shader1;
    Shader* shader2;
    Shader* shader3;

    Primitives* primitives;
    GLFWwindow& window;

    // Neuroevolution object pointer
    NeuroEvolution* neuroEvolution;

    Rectangle* groundRectangle;
    Rectangle* ceilRectangle;
    PillarManager* pillarManager;
    std::vector<Rectangle*> rects;

    std::vector<Circle*> circles;
    int lifeCount;

    void clearCircles();

    public:
        const float gravity = -0.0025;
        const float spawnInterval = 2.0f;
        const float organismRadius = 0.15f;

        bool ShouldPlayWorld = true;

        World( GLFWwindow& window, int windowWidth, int windowHeight );
        void Start();
        void Update();
        void Destroy();
        bool IsDead();
        void Restart();
        void Initiate();

        virtual ~World();
};


#endif 