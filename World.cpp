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
    this->rectangle = new Rectangle( *this->primitives, 0.2f, 0.7f );

    this->circle = new Circle();
}

void World::Start() {
    
    this->circle->scale = glm::vec3( 0.15, 0.15, 0.15 );
}

void World::Update() {
    this->camera->UpdateMatrix( 60.0f, 0.1f, 100.0f );
    this->circle->ApplyForce( glm::vec3( 0, gravity, 0 ) );

    if ( glfwGetKey( &this->window, GLFW_KEY_SPACE ) == GLFW_PRESS ) {
        this->circle->ApplyForce( glm::vec3( 0, this->jumpForce, 0 ) );
	}

    this->circle->Update();
    this->circle->DrawInstance( *shaderProgram, *camera );

    this->rectangle->Draw( *shaderProgram, *camera );

}

void World::Destroy() {
    
}

World::~World() {
    delete camera;
    delete shaderProgram;
    delete circle;
    delete rectangle;
    delete primitives;
}