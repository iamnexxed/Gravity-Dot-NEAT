#ifndef CIRCLE_CLASS_H
#define CIRCLE_CLASS_H

#include "Mesh.h"

class Circle {
    private:
        const int step = 10;
        Mesh *circleMesh;
        glm::vec3 velocity = glm::vec3( 0.0f, 0.0f, 0.0f );
        glm::vec3 initialPosition = glm::vec3(-3.3, 0, 0);

    public:
        glm::vec3 translation = glm::vec3( 0.0f, 0.0f, 0.0f );
		glm::vec3 scale = glm::vec3( 1.0f, 1.0f, 1.0f );

        Circle();
        void DrawInstance( Shader& shader, Camera& camera );
        void ApplyForce( glm::vec3 force );
        void Update();
        // void CheckDeath();
        // void CheckCollision(Rectangle other)
};


#endif 