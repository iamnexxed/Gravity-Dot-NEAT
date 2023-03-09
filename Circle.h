#ifndef CIRCLE_CLASS_H
#define CIRCLE_CLASS_H

#include "Helpers/Utils.h"
#include "Mesh.h"
#include "Rectangle.h"
#include "NeuralNetwork.h"
#include "Line.h"

class Circle {
    private:
        Mesh *circleMesh;
        glm::vec3 velocity = glm::vec3( 0.0f, 0.0f, 0.0f );
        glm::vec3 initialPosition = glm::vec3(-3.3, 0, 0);

        std::vector<Line> lines;

        NeuralNetwork *brain;
        float aliveTime = 0.0f;
        int pillarsCrossed = 0;

        void createSprite( float rad );

    public:
        bool isAlive;
        int id = -1;
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
            float yGroundDistance,
            float yPillar
        );
        bool CheckCollision( const Rectangle& rect );
        void CrossedPillar();

        float CalculateFitness();

        void DrawDebugView( Shader& shader, Camera& camera );
        void DrawDebugView( 
            Shader& shader1, Shader& shader2, Shader& shader3, Camera& camera 
        );
};


#endif 