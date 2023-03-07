#include "Circle.h"

Circle::Circle( float rad ) {

    this->createSprite( rad );
    this->hasBrain = false;
}

Circle:: Circle( Genome& genome, float rad ) {
    this->createSprite( rad );
    this->id = genome.id;
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

    this->lines.resize(3);
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
    // this->aliveTime += this->DELTA;
    this->aliveTime += 1;
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
    float yGroundDistance,
    float yPillar
) {
    // std::cout << "\nGot inputs: ";
    // std::cout << "\n - xDist: " << xDistance;
    // std::cout << "\n - yUpperPillarDistance: " << yUpperPillarDistance;
    // std::cout << "\n - yLowerPillarDistance: " << yLowerPillarDistance;
    // std::cout << "\n - this->velocity.y: " << this->velocity.y;

    glm::vec3 point = this->translation;
    point.x += xDistance;

    this->lines[0].setPoints(
        this->translation, point // <<<<<<<<<<<<<<<<<<<<<<<< DEBUG SHADER 1
    );


    point = this->translation;
    point.y += yUpperPillarDistance;

    this->lines[1].setPoints(
        this->translation, point // <<<<<<<<<<<<<<<<<<<<<<<< DEBUG SHADER 2
    );

    point = this->translation;
    point.y += yLowerPillarDistance;

    this->lines[2].setPoints(
        this->translation, point // <<<<<<<<<<<<<<<<<<<<<<<< DEBUG SHADER 3
    );

    // Normalize all the parameters
    xDistance = Mathematics::Map( 
        xDistance, 
        0, 
        this->MAXWIDTH,
        -1.0f,
        1.0f
    );
    yUpperPillarDistance = Mathematics::Map( 
        yUpperPillarDistance, 
        -this->MAXHEIGHT / 2, 
        this->MAXHEIGHT / 2,
        -1.0f,
        1.0f
    );
    yLowerPillarDistance = Mathematics::Map( 
        yLowerPillarDistance, 
        -this->MAXHEIGHT / 2, 
        this->MAXHEIGHT / 2,
        -1.0f,
        1.0f
    );
    //yCeilDistance /= this->MAXHEIGHT;
    //yGroundDistance /= this->MAXHEIGHT;
    float y = Mathematics::Map( 
        this->velocity.y, 
        -this->MAXHEIGHT / 2, 
        this->MAXHEIGHT / 2,
        -1.0f,
        1.0f
    );

    // Create a vector array
    const std::vector<float> inputs = {
        xDistance,
        yUpperPillarDistance,
        yLowerPillarDistance,
        //std::abs( translation.y - yPillar),
        //yCeilDistance,
        //yGroundDistance,
        this->velocity.y,
        //y,
        1.0f
     };

    // Neural Network prediction
    std::vector<float> output = this->brain->Predict( inputs );
    // If the output[0] is greater than the jump threshold return true
    return ( output.size() > 0 && output[0] > this->JUMP_PREDICTION_THRES );   
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
    // return A * aliveTime + B / nodes_in_brain
    int nodeCount = this->brain->GetNodeCount();
    if( this->hasBrain && nodeCount > 0 )
        //return this->A_PARAM * this->aliveTime + this->B_PARAM / nodeCount;
        return this->aliveTime + this->pillarsCrossed * 100; //<<<<<<<<<<<<<<<<
    return 0;
}

void Circle::CreateBrain( Genome& genome ) {
    this->brain = new NeuralNetwork( genome );
    this->hasBrain = true;
    this->isAlive = true;
}

void Circle::CrossedPillar() {
    this->pillarsCrossed++;
    //std::cout << "\nId: " << this->id << ", Pillar Crossed!";
}

void Circle::DrawDebugView( Shader& shader, Camera& camera ) {
    for(int i = 0; i < this->lines.size(); ++i) {
        this->lines[i].Draw(shader, camera);
    }
}
 void Circle::DrawDebugView( 
            Shader& shader1, Shader& shader2, Shader& shader3, Camera& camera 
) {
    this->lines[0].Draw(shader1, camera);
    this->lines[1].Draw(shader2, camera);
    this->lines[2].Draw(shader3, camera);
}