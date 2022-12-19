#include "World.h"

World::World( GLFWwindow& window, int windowWidth, int windowHeight ) :
    window(window) {
    this->camera = new Camera( 
        windowWidth, 
        windowHeight, 
        glm::vec3( 0.0f, 0.0f, 5.0f ) 
    );
    this->shaderProgram = new Shader( "sprite.vert", "sprite.frag" );
    shaderProgram->Activate();

    this->primitives = new Primitives();

    this->groundRectangle = new Rectangle( *this->primitives, 10.0f, 0.4f );
    this->groundRectangle->Translate( glm::vec3( 0, -2.7f, 0 ) );

    this->ceilRectangle = new Rectangle( *this->primitives, 10.0f, 0.4f );
    this->ceilRectangle->Translate( glm::vec3( 0, 2.7f, 0 ) );

    this->circle = new Circle( 0.15f );
    this->pillarManager = new PillarManager( *this->primitives, glm::vec3 ( 5.0f, 0, 0 ) );
   

}

void World::Start() {
}

void World::Update() {

    if( IsDead() ) {
        // Restart Level
        this->Restart();
    }
    
    // Update Calls
    this->circle->ApplyForce( glm::vec3( 0, gravity, 0 ) );
    //this->rectangle->Translate( glm::vec3( gravity, 0, 0 ) );
    if ( glfwGetKey( &this->window, GLFW_KEY_SPACE ) == GLFW_PRESS ) {
        this->circle->ApplyForce( glm::vec3( 0, this->jumpForce, 0 ) );
	}

    // // Forward
	// if (glfwGetKey(&this->window, GLFW_KEY_W) == GLFW_PRESS)
	// {
	// 	this->circle->Translate( glm::vec3( 0, this->jumpForce, 0 ) );
	// }
	// // Left
	// if (glfwGetKey(&this->window, GLFW_KEY_A) == GLFW_PRESS)
	// {
	// 	this->circle->Translate( glm::vec3( -this->jumpForce, 0, 0 ) );
	// }
	// // Backward
	// if (glfwGetKey(&this->window, GLFW_KEY_S) == GLFW_PRESS)
	// {
	// 	this->circle->Translate( glm::vec3( 0, -this->jumpForce, 0 ) );
	// }
	// // Right
	// if (glfwGetKey(&this->window, GLFW_KEY_D) == GLFW_PRESS)
	// {
	// 	this->circle->Translate( glm::vec3( this->jumpForce, 0, 0 ) );
	// }

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
    
}

void World::Restart() {
    this->circle->ResetPosition();
    // Reset Pillars
    // Reset PillarManager
    this->pillarManager->Reset();
}

bool World::IsDead() {
    if( this->circle->CheckCollision( *this->groundRectangle ) || 
        this->circle->CheckCollision( *this->ceilRectangle ) 
    ) {
        //std::cout << "Collision with rect. ";
        this->shaderProgram->SetFloatVecUniform3fv( "baseColor", glm::vec3( 1.0f, 0.0f, 0.0f ) );
        return true;
    }

    this->shaderProgram->SetFloatVecUniform3fv( "baseColor", glm::vec3( 1.0f, 1.0f, 1.0f ) );
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