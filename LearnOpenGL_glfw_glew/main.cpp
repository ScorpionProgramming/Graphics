#include <glew.h>
#include <glfw3.h>
#include <iostream>

//testweise
#include <fstream>
#include <string>
#include <time.h>

#include "Images\Color.h"
#include "Images\RGBImage.h"

#include "Math\Vector2f.h"
#include "Math\Vector3f.h"
#include "Math\Vector4f.h"
#include "Math\Matrix4f.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

GLfloat vertices[] = {
	0.5f, 0.5f, 0.0f, // Top Right
	0.5f, -0.5f, 0.0f, // Bottom Right
	-0.5f, -0.5f, 0.0f, // Bottom Left
	-0.5f, 0.5f, 0.0f, // Top Left
	//0.0f, 0.0f, 0.0f //mid
};
GLuint indices[] = { // Note that we start from 0!
	0, 1, 3, // First Triangle
	1, 2, 3 // Second Triangle
};

//-------------shader laden einbauen-------------------
//const GLchar* fragmentShaderSource ="Shader/myFirstShader.fragment";
//const GLchar* vertexShaderSource ="Shader/myFirstShader.vertex";
//-----------------------------------------------------

// Shaders 
const char* vertexShaderSource = //GLchar* war vorher dadrin
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position, 1.0);\n"
"vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"uniform vec4 uniColor;\n"
"void main()\n"
"{\n"
"color = uniColor;\n"
"}\n\0";

int main()
{

	RGBImage image(500, 500);

	std::srand(time(NULL));
	double rand;
	rand = ((double)std::rand() / (RAND_MAX));
	std::cout << rand << std::endl;
	Color c0(rand, rand, rand);
	rand = ((double)std::rand() / (RAND_MAX));
	std::cout << rand << std::endl;
	Color c1(rand, rand, rand);
	rand = ((double)std::rand() / (RAND_MAX));
	std::cout << rand << std::endl;
	Color c2(rand, rand, rand);
	rand = ((double)std::rand() / (RAND_MAX));
	std::cout << rand << std::endl;
	Color c3(rand, rand, rand);


	for (unsigned int i = 0; i<image.height(); i++)
	{
		for (unsigned int j = 0; j<image.width(); j++)
		{
			float u = (float)j / (float)image.width();
			float v = (float)i / (float)image.height();
			Color cu0 = c0 *(1.0f - u) + c1*u;
			Color cu1 = c2 *(1.0f - u) + c3*u;
			Color co = cu0 *(1.0f - v) + cu1*v;
			image.setPixelColor(j, i, co);
		}
	}

	image.saveToDisk("Loading_Test/Images/TestImageBlackWhite.bmp");
	
	//RGBImage image;
	
	//image.loadFromDisk("Loading_Test/Images/Test_Circle.bmp");
	//image.saveToDisk("Loading_Test/Images/Test_Circle_write.bmp");
	
	//image.loadFromDisk("Loading_Test/Images/Test2.bmp");
	//image.saveToDisk("Loading_Test/Images/Test_write2.bmp");

	//image.loadFromDisk("Loading_Test/Images/WTF.bmp");
	//image.saveToDisk("Loading_Test/Images/WTF_write.bmp");

	glfwInit();
	//alle wichtigen optionen f�r GLEW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr,nullptr);
	//Pr�fung ob der B�ldschirm korrekt erstellt wurden ist
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	else {
		std::cout << "GLFW Window created succsessful!" << std::endl;
	}
	glfwMakeContextCurrent(window);

	//ausf�hren von key events auf dem screen.
	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;

	//gucken ob glew initialisiert werden konnte
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	else {
		std::cout << "Initialized GLEW succsessful!" << std::endl;
	}
	
	int width, height;
	glViewport(0, 0, 800, 600);
	glfwGetFramebufferSize(window, &width, &height);
	glfwSwapInterval(0);
	std::cout << "Size: "<< width << " " << height << std::endl;

	/*
	#---------------------------------------Shader-BEGINN-------------------------------------------------------------------------------------------------------------------#
	*/

	//VERTEX_SHADER
	//deklaration und initialisierung des shaders
	GLuint vertexShader;
	//welchen shader wollen wir COMPILIEREN (vertex shader)
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//wo liegt der shader den wir kompilieren wollen
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//shader kompilieren
	glCompileShader(vertexShader);
	/*
	* Pr�fung ob die Compilation erfolgreich durchgelaufen ist.
	*/
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "VERTEX_SHADER::COMPILATION::ERROR\n" << infoLog << std::endl;
	}

	//FRAGMENT_SHADER
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Pr�fung ob compile erfolgreich
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "FRAGMENT_SHADER::COMPILATION::ERROR\n" << infoLog << std::endl;
	}

	//SHADER Bauen
	GLuint shaderProgram;
	//gibt eine id von dem letzten erzeugten programm zur�ck
	shaderProgram = glCreateProgram();
	//shader ins programm laden
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//und dann linken
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "SHADER_PROGRAM::LINKING::FAILED::ERROR\n" << infoLog << std::endl;
	}

	//Shader l�schen, weil sie nicht mehr ben�tigt werden!
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//Buffer objekt erstellen
	GLuint VBO, VAO, EBO;
	//buffer generieren
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//1. bind vertex array
	glBindVertexArray(VAO);
		//2. kopieren der verticiesin den vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//2. kopieren der index daten in den element buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//3. attribut pointer setzen
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	/*
	#---------------------------------------Shader-ENDE---------------------------------------------------------------------------------------------------------------------#
	*/
	std::cout << " sizeof(vertices)/sizeof(GLfloat)/3 = " << sizeof(vertices) / sizeof(GLfloat) / 3 << std::endl;
	//main loop (game loop)
	GLfloat delta = 0;
	while (!glfwWindowShouldClose(window))
	{
		GLfloat timeValue = glfwGetTime();
		GLfloat currTime = timeValue;
		//Pr�fen und events aufrufen
		glfwPollEvents();

		//rendering commands hier
		glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		GLfloat blueValue = (sin(timeValue) + 0.5);
		GLfloat redValue = (cos(timeValue) + 0.5);
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "uniColor");

		std::cout << "TimeValue: " << 1/delta << std::endl;
		//drawTriangle
		glUseProgram(shaderProgram);

		glUniform4f(vertexColorLocation, redValue, 0.0f, blueValue, 1.0f);

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(GLfloat) / 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		
		//Swap buffers
		glfwSwapBuffers(window);

		delta = glfwGetTime() - currTime;
	}
	// speicher f�r die vao und vbo wieder freigeben
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//GLEW Abbrechen, und alle reservierten Daten freigeben
	glfwTerminate();
	return 0;
}

//die funktion wird IMMER aufgerufen, wenn eine Taste gedr�ckt oder losgelassen wird mit GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//wenn escape key gedr�ckt wurde sollte sich das Fenster schlie�en
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	//sp�ter in andere klasse auslagern und mit einem boolean versehen.
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	std::cout << "window: "<<window << "\nKey: " << key << "\nScancode: " << scancode << "\nAction: " << action << "\nMode: " << mode << std::endl;
}