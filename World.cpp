#include "World.h"

World::World( GLFWwindow* window, int windowWidth, int windowHeight ) {
    this->window = window;
    this->camera = new Camera ( windowWidth, windowHeight, glm::vec3( 0.0f, 0.0f, 5.0f ) );
    this->shaderProgram = new Shader( "sprite.vert", "sprite.frag" );
    shaderProgram->Activate();
}

void World::Start() {
    this->circle = new Circle();
    this->circle->scale = glm::vec3(0.15, 0.15, 0.15);
}

void World::Update() {
    camera->UpdateMatrix( 60.0f, 0.1f, 100.0f );
    circle->ApplyForce( glm::vec3( 0, gravity, 0 ) );

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		 circle->ApplyForce( glm::vec3( 0, 0.015, 0 ) );
	}
    
    circle->Update();
    circle->DrawInstance( *shaderProgram, *camera );
}

void World::Destroy() {
    
}

World::~World() {
   delete circle;
   delete camera;
   delete shaderProgram;
}