#ifndef CIRCLE_CLASS_H
#define CIRCLE_CLASS_H

#include "Primitives/Utils.h"
#include "Mesh.h"
#include "Rectangle.h"
#include "NeuralNetwork.h"

class Circle {
    private:
        const int step = 10;
        const float JUMPFORCE = 0.045;
        Mesh *circleMesh;
        glm::vec3 velocity = glm::vec3( 0.0f, 0.0f, 0.0f );
        glm::vec3 initialPosition = glm::vec3(-3.3, 0, 0);
        NeuralNetwork *brain;
        float aliveTime = 0.0f;

        void createSprite( float rad );

    public:
        float radius = 1.0f;
        glm::vec3 translation = glm::vec3( 0.0f, 0.0f, 0.0f );
		glm::vec3 scale = glm::vec3( 1.0f, 1.0f, 1.0f );

        bool hasBrain;

        Circle( float rad );
        Circle( Genome& genome, float rad );
        void CreateTestBrain();
        void CreateBrain( Genome& genome );
        void MoveTo( glm::vec3 position );
        void DrawInstance( Shader& shader, Camera& camera );
        void ApplyForce( glm::vec3 force );
        void Jump();
        void Update();
        void Translate( glm::vec3 translationVec );
        void ResetPosition();
        bool Predict( 
            float xDistance, 
            float yUpperPillarDistance, 
            float yLowerPillarDistance, 
            float yCeilDistance,
            float yGroundDistance
        );
        bool CheckCollision( const Rectangle& rect );

        float CalculateFitness();
};


#endif 