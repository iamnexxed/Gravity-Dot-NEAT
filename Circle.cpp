#include "Circle.h"

Circle::Circle( float rad ) {

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
    this->radius = rad;
    this->scale.x = rad;
    this->scale.y = rad;
    
    Genome newGene( 3, 1 );
    if( newGene.AddRandomConnection() ) {
        std::cout << "\nAdded Random connection 1..";
    }

    if( newGene.AddRandomConnection() ) {
        std::cout << "\nAdded Random connection 2..";
    }

    if( newGene.AddRandomConnection() ) {
        std::cout << "\nAdded Random connection 3..";
    }

    newGene.ShowNodeData();

    this->brain = new NeuralNetwork( newGene );
    this->brain->ShowLayers();
    std::vector<float> inputs = { 0.5f, 0.2f, 0.3f };
    std::vector<float> outputs = this->brain->Predict( inputs );
    //std::cout << "\nSize of outputs: " << outputs.size();
    Utils::showFloatVector( outputs );
    std::cout << "\n\n";
}


void Circle::MoveTo( glm::vec3 position ) {
    this->translation = position;
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

void Circle::Translate( glm::vec3 translationVec ) {
    this->translation += translationVec;
}

void Circle::ResetPosition() {
    this->MoveTo( glm::vec3( this->translation.x, 0, 0 ) );
    this->velocity = glm::vec3( 0, 0, 0 );
}

bool Circle::CheckCollision( const Rectangle& rect ) {
    glm::vec3 circleDistance;

    circleDistance.x = std::abs( this->translation.x - rect.translation.x );
    circleDistance.y = std::abs( this->translation.y - rect.translation.y );

    if( circleDistance.x > ( rect.width / 2 + this->radius ) ) return false;
    if( circleDistance.y > ( rect.height / 2 + this->radius ) ) return false;

    if( circleDistance.x <= rect.width / 2 ) return true;
    if( circleDistance.y <= rect.height / 2 ) return true;

    float cornerDistanceSquared = 
        std::pow( circleDistance.x - rect.width / 2, 2 ) + 
        std::pow( circleDistance.y - rect.height / 2, 2 );

    return cornerDistanceSquared <= std::pow( this->radius, 2 );
}