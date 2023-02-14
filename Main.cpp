// Execution command on MacOS
// /usr/bin/clang++ -std=c++17 -ILibraries/include -g **.cpp glad.cc -o Main -LLibraries/lib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit && ./Main

// GLM Reference: https://openframeworks.cc//documentation/glm/detail_func_geometric/#!show_glm::cross


#include "Model.h"


#include "Physics/physics.h"

#include "Primitives/Mathematics.h"

#include <cmath>

#include "Globals.h"

#include "World.h"


static void glfwError( int id, const char *description )
{
	std::cout << description << std::endl;
}

int main()
{
	glfwSetErrorCallback( &glfwError );
	// Init GLFW
	glfwInit();

	// Tell GLFW which version we are using
	// For Windows/Linux
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	// //glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// For MacOS
	// https://www.glfw.org/faq.html#14---what-platforms-are-supported-by-glfw
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	// Create window object
	GLFWwindow* window = glfwCreateWindow( WIDTH, HEIGHT, WINDOW_NAME, NULL, NULL );

	if ( window == NULL )
	{
		std::cout << "Failed to initialize GLFW windows!\n";
		glfwTerminate();
		return -1;
	}
	// Use created GLFW window
	glfwMakeContextCurrent( window );

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	srand( time( NULL ) );

	// Enables the depth buffer
	glEnable( GL_DEPTH_TEST );

	//glViewport( 0, 0, WIDTH, HEIGHT );

	World world( *window, WIDTH, HEIGHT );
	//std::cout << "\nWorld Constructed.";
	world.Start();

	// For terminal to show the lines correctly
	std::cout << "\n\n";
	// Only close when user decides to close the window
	while ( !glfwWindowShouldClose( window ) )
	{
		glClearColor( kBG_COLOR_R, kBG_COLOR_G, kBG_COLOR_B, kBG_COLOR_A );

		// Clear the depth buffer and the color buffer bit
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		world.Update();
		
		glfwSwapBuffers( window );
		// Process all the events
		glfwPollEvents(); // If not done window will go to not responding
	}


	world.Destroy();
	// Destroy Window
	glfwDestroyWindow( window );
	// End GLFW
	glfwTerminate();
	// std::cin.get();
	return 0;
}


