#include "Circle.h"

Circle::Circle( float rad ) {

    this->createSprite( rad );
    this->hasBrain = false;
}

Circle:: Circle( Genome& genome, float rad ) {
    this->createSprite( rad );
    this->hasBrain = true;
    this->CreateBrain( genome );
}

void Circle::createSprite( float rad ) {
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

void Circle::Jump() {
    this->velocity = glm::vec3( 0, 0, 0 );
    this->ApplyForce( glm::vec3( 0, this->JUMPFORCE, 0 ) );
}

void Circle::Update() {
    this->translation += this->velocity;
    // Increase alive time
}

void Circle::Translate( glm::vec3 translationVec ) {
    this->translation += translationVec;
}

void Circle::ResetPosition() {
    this->MoveTo( glm::vec3( this->translation.x, 0, 0 ) );
    this->velocity = glm::vec3( 0, 0, 0 );
}

bool Circle::Predict( 
    float xDistance, 
    float yUpperPillarDistance, 
    float yLowerPillarDistance, 
    float yCeilDistance,
    float yGroundDistance
) {
    // Normalize all the parameters

    // Create a vector array

    // Neural Network prediction

    // If the output[0] is greater than the jump threshold return true

    return false;
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

void Circle::CreateTestBrain() {
    Genome g1( 3, 1 );
    g1.AddNode( LayerType::Hidden );
    g1.CreateConnection( 2, 3, 1, false );
    g1.CreateConnection( 0, 3, 1, true );
    g1.CreateConnection( 1, 3, 1, true );
    g1.CreateConnection( 2, 4, 1, true );
    g1.CreateConnection( 4, 3, 1, true );
    g1.CreateConnection( 0, 4, 1, true );

    Genome g2( 3, 1 );
    g2.AddNode( LayerType::Hidden );
    g2.CreateConnection( 2, 3, 1, true );
    g2.CreateConnection( 0, 3, 1, true );
    g2.CreateConnection( 1, 3, 1, false );
    g2.CreateConnection( 2, 4, 1, true );
    g2.CreateConnection( 4, 3, 1, true );
    g2.CreateConnection( 1, 4, 1, true );

    Genome g3( 3, 1 );
    g3.AddNode( LayerType::Hidden );
    g3.CreateConnection( 2, 3, 1, true );
    g3.CreateConnection( 0, 3, 1, true );

    Genome g4( 3, 1 );
    g4.AddNode( LayerType::Hidden );
    g4.CreateConnection( 2, 3, 1, true );
    g4.CreateConnection( 0, 3, 1, true );
  
    std::cout << "\nIs G1 compatible with G4 ? " << g1.IsCompatible( g4 );
    std::cout << "\nIs G1 compatible with G2 ? " << g1.IsCompatible( g2 );

    Genome *offspring = g1.CrossOver( g4 );
    //offspring.ShowNodeData();

    this->brain = new NeuralNetwork( *offspring );
    //this->brain->ShowLayers();
    std::vector<float> inputs = { 0.5f, 0.2f, 0.3f };
    std::vector<float> outputs = this->brain->Predict( inputs );
    //std::cout << "\nSize of outputs: " << outputs.size();
    Utils::showFloatVector( outputs );
    std::cout << "\n\n";
}

float Circle::CalculateFitness() {
    // Fitness function
    // return A * aliveTime + B / hidden_nodes_in_brain
    return 0;
}

void Circle::CreateBrain( Genome& genome ) {
    this->brain = new NeuralNetwork( genome );
}