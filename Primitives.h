#ifndef PRIMITIVE_CLASS_H
#define PRIMITIVE_CLASS_H

#include <glad/glad.h>
#include "Mesh.h"


class Primitives {
	private:


	std::vector<Vertex> plane_vertices = { 
		//			COORDINATES				/			NORMALS				/			COLORS					/		TEXTURE COORDINATES
		Vertex{ glm::vec3( -1.0f,  1.0f, 0.0f ),	glm::vec3( 0.0f, 1.0f, 0.0f ),	glm::vec3( 1.0f, 1.0f, 0.0f ),		glm::vec2( 0.0f, 0.0f ) },
		Vertex{ glm::vec3( -1.0f, -1.0f, 0.0f ),	glm::vec3( 0.0f, 1.0f, 0.0f ),	glm::vec3( 0.0f, 1.0f, 1.0f ),		glm::vec2( 0.0f, 1.0f ) },
		Vertex{ glm::vec3(  1.0f, -1.0f, 0.0f ),	glm::vec3( 0.0f, 1.0f, 0.0f ),	glm::vec3( 1.0f, 0.0f, 1.0f ),		glm::vec2( 1.0f, 1.0f ) },
		Vertex{ glm::vec3(  1.0f,  1.0f, 0.0f ),	glm::vec3( 0.0f, 1.0f, 0.0f ),	glm::vec3( 1.0f, 0.5f, 0.4f ),		glm::vec2( 1.0f, 0.0f ) }
	};

	std::vector<GLuint> plane_indices = {
		0, 3, 2,	
		0, 2, 1	
	};

	std::vector<Vertex> triangle_vertices = {
		//			COORDINATES						/			NORMALS				/			COLORS					/		TEXTURE COORDINATES
		Vertex{ glm::vec3( -0.5f,	 0.0f,		0.0f ),	glm::vec3( 0.0f, 1.0f, 0.0f ),	glm::vec3( 1.0f, 1.0f, 0.0f ),		glm::vec2( 0.0f, 0.0f ) },
		Vertex{ glm::vec3(  0.5f,	 0.0f,		0.0f ),	glm::vec3( 0.0f, 1.0f, 0.0f ),	glm::vec3( 0.0f, 1.0f, 1.0f ),		glm::vec2( 0.0f, 1.0f ) },
		Vertex{ glm::vec3(  0.0f,	-0.5f,		0.0f ),	glm::vec3( 0.0f, 1.0f, 0.0f ),	glm::vec3( 1.0f, 0.0f, 1.0f ),		glm::vec2( 1.0f, 1.0f ) },
	};

	std::vector<GLuint> triangle_indices = {	
		0, 2, 1	
	};

	std::vector<Texture> tex;

    public:
		Mesh* circleMesh;
		Mesh* rectangleMesh;

		Primitives();
		Mesh* CreateCircleMesh();
		Mesh* CreateRectangleMesh();
		void DrawCircle (
			Shader& shader, 
			Camera& camera,
			glm::mat4 matrix 		= glm::mat4( 1.0f ),
			glm::vec3 translation 	= glm::vec3( 0.0f, 0.0f, 0.0f ),
			glm::quat rotation 		= glm::quat( 1.0f, 0.0f, 0.0f, 0.0f ),
			glm::vec3 scale 		= glm::vec3( 1.0f, 1.0f, 1.0f ),
			bool isWire 			= false
		);

		void DrawRectangle (
			Shader& shader, 
			Camera& camera,
			glm::mat4 matrix 		= glm::mat4( 1.0f ),
			glm::vec3 translation 	= glm::vec3( 0.0f, 0.0f, 0.0f ),
			glm::quat rotation 		= glm::quat( 1.0f, 0.0f, 0.0f, 0.0f ),
			glm::vec3 scale 		= glm::vec3( 1.0f, 1.0f, 1.0f ),
			bool isWire 			= false
		);

};

#endif