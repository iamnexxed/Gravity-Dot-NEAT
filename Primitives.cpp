#include "Primitives.h"

Primitives::Primitives() {
    this->circleMesh = this->CreateCircleMesh();
    this->rectangleMesh = this->CreateRectangleMesh();
}

Mesh* Primitives::CreateCircleMesh() {
    const int step = 10;
    std::vector<Vertex> circle_vertices = { 
        Vertex { 
            glm::vec3( 0.0f, 0.0f, 0.0f ),	
            glm::vec3( 1.0f, 0.0f, 0.0f ),	
            glm::vec3( 1.0f, 1.0f, 1.0f ),		
            glm::vec2( 0.0f, 0.0f )
        }
    };

    for( int i = 0; i < 360; i += step ) {

        circle_vertices.push_back(
            Vertex { 
                glm::vec3( 
                    std::cos( i * glm::pi<float>() / 180 ),	    
                    std::sin( i * glm::pi<float>() / 180 ),		
                    0.0f
                ),	
                glm::vec3( 0.0f, 0.0f, 1.0f ),
                glm::vec3( 1.0f, 1.0f, 1.0f ),		
                glm::vec2( 0.0f, 0.0f ) 
            }
        );
    }

    std::vector<GLuint> indices;
    for( int i = 1; i < circle_vertices.size() - 1; i ++ ) {
        indices.push_back( i );
        indices.push_back( i + 1 );
        indices.push_back( 0 );
    }

    indices.push_back( circle_vertices.size() - 1 );
    indices.push_back( 1 );
    indices.push_back( 0 );

    

    return new Mesh( circle_vertices, indices, tex );
}

Mesh* Primitives::CreateRectangleMesh() {
    return new Mesh( plane_vertices, plane_indices, tex );
}

void Primitives::DrawCircle(
    Shader& shader, 
    Camera& camera,
    glm::mat4 matrix,        
    glm::vec3 translation,  
    glm::quat rotation,      
    glm::vec3 scale,        
    bool isWire            
) const {
    this->circleMesh->DrawInstance(
        shader, 
        camera, 
        matrix, 
        translation,
        rotation,
        scale,
        isWire
    );
}

void Primitives::DrawRectangle (
    Shader& shader, 
    Camera& camera,
    glm::mat4 matrix,
    glm::vec3 translation,
    glm::quat rotation,
    glm::vec3 scale,
    bool isWire
) const {
    this->rectangleMesh->DrawInstance(
        shader, 
        camera, 
        matrix, 
        translation,
        rotation,
        scale,
        isWire
    );
}