#include "Circle.h"

Circle::Circle() {

    std::vector<Vertex> circle_vertices = { 
        Vertex { 
            glm::vec3( 0.0f, 0.0f, 0.0f ),	
            glm::vec3( 1.0f, 0.0f, 0.0f ),	
            glm::vec3( 1.0f, 1.0f, 1.0f ),		
            glm::vec2( 0.0f, 0.0f )
        }
    };

    for( int i = 0; i < 360; i += this->step ) {

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

    std::vector<Texture> tex;

    this->circleMesh = new Mesh( circle_vertices, indices, tex );
    this->translation = this->initialPosition;
}

void Circle::DrawInstance( Shader& shader, Camera& camera ) {
    this->circleMesh->DrawInstance ( 
        shader, 
        camera,
        this->circleMesh->matrix, 
        this->translation,
        this->circleMesh->rotation,
        this->scale
	);
}

void Circle::ApplyForce( glm::vec3 force ) {
    this->velocity += force;
}

void Circle::Update() {
    this->translation += this->velocity;
}