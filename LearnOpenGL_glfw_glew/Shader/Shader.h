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

	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void Use();
	GLuint getProgram();
	~Shader();

private:
	std::string load(std::string dateipfad);
};

