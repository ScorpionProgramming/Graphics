#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glew.h>
#include <glfw3.h>


class Shader
{
public:
	//SHADER Bauen
	GLuint shaderProgram;

	Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
	void Use();
	GLuint getProgram();
	~Shader();

private:
	const char* load(std::string dateipfad);
};

