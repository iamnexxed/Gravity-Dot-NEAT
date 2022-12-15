#ifndef RECTANGLE_CLASS_H
#define RECTANGLE_CLASS_H

#include <glm/glm.hpp>
#include "Mesh.h"
#include "Primitives.h"

class Rectangle {
    private:
        const Primitives& primitives;

        Mesh* rectMesh;

        void UpdateBounds();

    public:
        glm::mat4 matrix 		= glm::mat4( 1.0f );
        glm::vec3 translation 	= glm::vec3( 0.0f, 0.0f, 0.0f );
        glm::quat rotation 		= glm::quat( 1.0f, 0.0f, 0.0f, 0.0f );
        glm::vec3 scale 		= glm::vec3( 1.0f, 1.0f, 1.0f );

        glm::vec3 minBound;
        glm::vec3 maxBound;

        float width;
        float height;

        Rectangle( const Primitives& primitives, float width, float height );
        void Draw( Shader& shader, Camera& camera );
        void Translate( glm::vec3 diplacementVec );
};

#endif