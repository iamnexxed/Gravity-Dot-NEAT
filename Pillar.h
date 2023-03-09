#ifndef PILLAR_CLASS_H
#define PILLAR_CLASS_H
#include "Globals.h"
#include "Rectangle.h"
#include "Helpers/Mathematics.h"

// The pillar moves w.r.t. the origin which is located at top left corner of the screen
class Pillar {
    private:
        glm::vec3 translation;
        glm::vec3 currentVelocity;
        glm::vec3 initialPosition;
        bool shouldMove;

    public:
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