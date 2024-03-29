#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "ShaderClass.h"

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	
	glm::vec3 Up = glm::vec3(0.0f, -1.0f, 0.0f); // Make camera face such that up is positive Y
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	// Prevents camera from jumping around when first clicking left click
	bool firstClick = true;

	// Width and height of the window
	int width;
	int height;

	const float defaultSpeed = 0.01f;
	float speed = 0.0001f;
	float sensitivity = 100.0f;

	Camera(int width, int height, glm::vec3 position);

	void Matrix(Shader& shader, const char* uniform);
	void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);


	void Inputs(GLFWwindow* window);
};

#endif // !CAMERA_CLASS_H

