#ifndef RECTANGLE_CLASS_H
#define RECTANGLE_CLASS_H

#include <glm/glm.hpp>
#include "Mesh.h"
#include "Primitives.h"

class Rectangle {
    private:
        glm::vec3 minBound;
        glm::vec3 maxBound;
        glm::vec3 center;
        float width;
        float height;

        Mesh* rectMesh;

        

    public:
        glm::mat4 matrix 		= glm::mat4( 1.0f );
        glm::vec3 translation 	= glm::vec3( 0.0f, 0.0f, 0.0f );
        glm::quat rotation 		= glm::quat( 1.0f, 0.0f, 0.0f, 0.0f );
        glm::vec3 scale 		= glm::vec3( 1.0f, 1.0f, 1.0f );
        Rectangle( glm::vec3 min, glm::vec3 max );
        Rectangle( glm::vec3 center, float width, float height );
        void Draw( Primitives& primitive, Shader& shader, Camera& camera );
};

#endif