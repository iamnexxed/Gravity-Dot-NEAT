#ifndef PILLAR_CLASS_H
#define PILLAR_CLASS_H

#include "Rectangle.h"

class Pillar {
    private:
        //const Primitives& primitives;
        Rectangle* upperRect;
        Rectangle* lowerRect;
        glm::vec3 translation;
        float currentVelocity;
        const float acceleration = 0.001f;
        const float pillarWidth = 0.2f;
        const float pillarHeight = 0.7f;

    public:
        float initialVelocity;
        float gapDistance;
        Pillar( const Primitives& primitives, float initialVelocity, float gap );
        void Spawn();
        void Update();
        void Draw( Shader& shader, Camera& camera );
        void Reset();
};

#endif