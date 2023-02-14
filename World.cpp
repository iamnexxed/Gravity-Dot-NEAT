#include "World.h"

World::World( GLFWwindow& window, int windowWidth, int windowHeight ) :
    window(window) {
    this->camera = new Camera( 
        windowWidth, 
        windowHeight, 
        glm::vec3( 0.0f, 0.0f, 5.0f ) 
    );
    this->shaderProgram = new Shader( "sprite.vert", "sprite.frag" );
    this->shaderProgram->Activate();
    this->shaderProgram->SetFloatVecUniform3fv( "baseColor", glm::vec3( 1.0f, 1.0f, 1.0f ) );
    this->primitives = new Primitives();

    this->groundRectangle = new Rectangle( *this->primitives, 10.0f, 0.4f );
    this->groundRectangle->Translate( glm::vec3( 0, -2.7f, 0 ) );

    this->ceilRectangle = new Rectangle( *this->primitives, 10.0f, 0.4f );
    this->ceilRectangle->Translate( glm::vec3( 0, 2.7f, 0 ) );

    this->circle = new Circle( 0.15f );
    this->pillarManager = new PillarManager( *this->primitives, glm::vec3 ( 5.0f, 0, 0 ) );
    this->rects = this->pillarManager->GetAllRectangles();

    // Construct NeuroEvolution Object
    this->neuroEvolution = new NeuroEvolution();
    std::cout << "\nWorld Constructor";
}

void World::Start() {
    std::cout << "\nWorld Start";
    this->neuroEvolution->Initiate();
    this->neuroEvolution->Speciate();
}

void World::Update() {

    if( this->IsDead() ) {
        // If there are no dot organisms left restart the level
        this->Restart();
    }

    // Play the game
    
    // Update Calls
    this->circle->ApplyForce( glm::vec3( 0, gravity, 0 ) );




    if ( 
        glfwGetKey( &this->window, GLFW_KEY_SPACE ) == GLFW_PRESS && 
        !this->circle->hasBrain 
    ) {
        this->circle->ApplyForce( glm::vec3( 0, this->jumpForce, 0 ) );
	}

    this->camera->UpdateMatrix( 60.0f, 0.1f, 100.0f );
    this->circle->Update();
    // Update PillarManager
    this->pillarManager->Update();

    // Draw Calls
    this->circle->DrawInstance( *shaderProgram, *camera );
    this->groundRectangle->Draw( *shaderProgram, *camera );
    this->ceilRectangle->Draw( *shaderProgram, *camera );
    // Draw PillarManager
    this->pillarManager->Draw( *shaderProgram, *camera );
}

void World::Destroy() {
    std::cout << "\nWorld Destroy";
}

void World::Restart() {
    this->circle->ResetPosition();
    // Reset Pillars
    // Reset PillarManager
    this->pillarManager->Reset();
}

bool World::IsDead() {
    // if the organism collides 
        // Evaluate the fitness of the organism based on the distance traveled, the energy spent and the brain size
        // Remove the organism from the scene

    // If all the organisms have collided
        // Perform Speciation
        
        // Increment Generation
        // Perform crossover of the best parents
        // Perform mutation on the new offsprings

    if( this->circle->CheckCollision( *this->groundRectangle ) || 
        this->circle->CheckCollision( *this->ceilRectangle ) 
    ) {
        //this->shaderProgram->SetFloatVecUniform3fv( "baseColor", glm::vec3( 1.0f, 0.0f, 0.0f ) );
        return true;
    }

    for( int i = 0; i < this->rects.size(); ++i ) {
        if( this->circle->CheckCollision( *this->rects[i] ) ) {
            //this->shaderProgram->SetFloatVecUniform3fv( "baseColor", glm::vec3( 1.0f, 0.0f, 0.0f ) );
           return true;
        }
    }

    //this->shaderProgram->SetFloatVecUniform3fv( "baseColor", glm::vec3( 1.0f, 1.0f, 1.0f ) );
    return false;
}

World::~World() {
    delete this->camera;
    delete this->shaderProgram;
    delete this->circle;
    delete this->groundRectangle;
    delete this->ceilRectangle;
    delete this->primitives;
    delete this->pillarManager;
}