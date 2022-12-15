#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <glm/glm.hpp>

std::string get_file_contents( const char* filename );

class Shader
{
private:
	void compileErrors( unsigned int shader, const char* type, const char* name );

public:
	GLuint ID;
	Shader( const char* vertexFile, const char* fragmentFile );

	void Activate();
	void Delete();

	void SetFloatUniform1f( const char* uniform, float value );
	void SetFloatUniform3f( const char* uniform, float v0, float v1, float v2 );
	void SetFloatVecUniform3fv( const char* uniform, glm::vec3 v);
};

#endif // !SHADER_CLASS_H

