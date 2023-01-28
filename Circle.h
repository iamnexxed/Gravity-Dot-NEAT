#ifndef CIRCLE_CLASS_H
#define CIRCLE_CLASS_H

#include "Primitives/Utils.h"
#include "Mesh.h"
#include "Rectangle.h"
#include "NeuralNetwork.h"

class Circle {
    private:
        const int step = 10;
        Mesh *circleMesh;
        glm::vec3 velocity = glm::vec3( 0.0f, 0.0f, 0.0f );
        glm::vec3 initialPosition = glm::vec3(-3.3, 0, 0);
        NeuralNetwork *brain;

    public:
        float radius = 1.0f;
        glm::vec3 translation = glm::vec3( 0.0f, 0.0f, 0.0f );
		glm::vec3 scale = glm::vec3( 1.0f, 1.0f, 1.0f );

        Circle( float rad );
        void CreateBrain();
        void MoveTo( glm::vec3 position );
        void DrawInstance( Shader& shader, Camera& camera );
        void ApplyForce( glm::vec3 force );
        void Update();
        void Translate( glm::vec3 translationVec );
        void ResetPosition();
        // void CheckDeath();
        bool CheckCollision( const Rectangle& rect );
};


#endif 