#ifndef PILLAR_CLASS_H
#define PILLAR_CLASS_H

#include "Rectangle.h"
#include "Helpers/Mathematics.h"

// The pillar moves w.r.t. the origin which is located at top left corner of the screen
class Pillar {
    private:

        glm::vec3 translation;
        glm::vec3 currentVelocity;
        glm::vec3 initialPosition;
        
        bool shouldMove;

        const float acceleration = 0.001f;

        const float yBoundDistance = 2.0f;
        const float respawnXLocation = -5.0f;
        const glm::vec3 initialVelocity = glm::vec3( -0.02f, 0, 0 );

    public:
        const float pillarWidth = 0.5f;
        const float pillarHeight = 4.5f;
        const float gapDistance = 1.2f;

        bool IsSelected = false;

        bool IsInQueue = false;

        Rectangle* upperRect;
        Rectangle* lowerRect;
        Pillar( const Primitives& primitives, glm::vec3 iPosition );
        void Spawn();
        void Update();
        void Draw( Shader& shader, Camera& camera );
        void Reset();
        void MoveRectangles();
        void IncreaseVelocity();
        float GetXPos();
        float GetYPos();
        bool CanMove();
        float GetCurrentVelocity();

};

#endif