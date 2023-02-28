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
    std::cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ World Constructed ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
}

void World::Start() {
    //std::cout << "\nWorld Start";
    this->Initiate();
    // this->neuroEvolution->Initiate();
    // this->neuroEvolution->Speciate();
    // this->neuroEvolution->CrossOver();
    // this->neuroEvolution->SaveGenomesToJSON();
}

void World::Update() {
    // If all the organisms have collided
    if( this->IsDead() ) {
        // Perform Speciation 
        // Increment Generation
        // Perform crossover of the best parents
        // Perform mutation on the new offsprings
        // Restart the world with the  new offsprings
        // If there are no dot organisms left restart the level
        this->Restart();
    }

    // Play the game
    
    // Update Calls

    // Apply Gravity on all organisms
    this->circle->ApplyForce( glm::vec3( 0, gravity, 0 ) );

    if ( 
        glfwGetKey( &this->window, GLFW_KEY_SPACE ) == GLFW_PRESS && 
        !this->circle->hasBrain 
    ) {
        this->circle->Jump();
	} 

    this->camera->UpdateMatrix( 60.0f, 0.1f, 100.0f );
    
    // For each organism make a decision as to jump or not
    // Update all organisms
    this->circle->Update();

    // Update PillarManager
    this->pillarManager->Update();

    // Draw Calls

    // Draw all organisms
    this->circle->DrawInstance( *shaderProgram, *camera );

    // Draw ground
    this->groundRectangle->Draw( *shaderProgram, *camera );
    // Draw ceiling
    this->ceilRectangle->Draw( *shaderProgram, *camera );
    // Draw Pillars
    this->pillarManager->Draw( *shaderProgram, *camera );
}

void World::Destroy() {
    std::cout << "\nWorld Destroy";
}

void World::Restart() {
    // Reset the positions of all the organisms
    this->circle->ResetPosition();
    // Reinitialize setup
    this->Initiate();
    // Reset Pillars
    // Reset PillarManager
    this->pillarManager->Reset();
}

bool World::IsDead() {

    // For all organisms
        // if the organism collides 
            // Reduce the living count
            // Evaluate the fitness of the organism based on the distance traveled, the energy spent and the brain size
            // Set the genome index fitness
            // Remove the organism from the scene
    
    // If living count is zero return true

   

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

void World::Initiate() {
    // For each genome in the neuroevolution
        // Create a new circle with a brain and store it in the circle array
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