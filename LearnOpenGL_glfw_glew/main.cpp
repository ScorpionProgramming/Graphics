#include <glew.h>
#include <glfw3.h>
#include <iostream>

//testweise
#include <fstream>
#include <string>
#include <iostream>

#include "Images\Color.h"
#include "Images\RGBImage.h"

#include "Math\Vector2f.h"
#include "Math\Vector3f.h"
#include "Math\Vector4f.h"
#include "Math\Matrix4f.h"

#include "Shader\Shader.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

/*GLfloat vertices[] = { -0.5f,-0.5f, 0.0f,
						0.5f, -0.5f, 0.0f,
						0.0f, 0.5f, 0.0f 
					};
					*/
/*
GLfloat vertices[] = {
	// First triangle
	0.5f, 0.5f, 0.0f, // Top Right
	0.5f, -0.5f, 0.0f, // Bottom Right
	-0.5f, 0.5f, 0.0f, // Top Left
	// Second triangle
	0.5f, -0.5f, 0.0f, // Bottom Right
	-0.5f, -0.5f, 0.0f, // Bottom Left
	-0.5f, 0.5f, 0.0f // Top Left
};
*/

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
	//0,1,4,
	//1,4,2,
	//2,3,4,
	//3,0,4
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

const char* fragmentShaderSource = 
"#version 330 core\n"
"out vec4 color;\n"
"uniform vec4 uniColor;\n"
"void main()\n"
"{\n"
"color = uniColor;\n"
"}\0";

int main()
{
	
	//RGBImage image;
	
	//image.loadFromDisk("Loading_Test/Images/Test_Circle.bmp");
	//image.saveToDisk("Loading_Test/Images/Test_Circle_write.bmp");
	
	//image.loadFromDisk("Loading_Test/Images/Test2.bmp");
	//image.saveToDisk("Loading_Test/Images/Test_write2.bmp");

	//image.loadFromDisk("Loading_Test/Images/WTF.bmp");
	//image.saveToDisk("Loading_Test/Images/WTF_write.bmp");

	glfwInit();
	//alle wichtigen optionen für GLEW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr,nullptr);
	//Prüfung ob der Bíldschirm korrekt erstellt wurden ist
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

	//ausführen von key events auf dem screen.
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

	std::cout << "\n\n" << std::endl;

	Shader shader = Shader("Shader/ShaderSource/shaderTest.vertex", "Shader/ShaderSource/shaderTest.fragment");

	GLuint shaderProgram = shader.getProgram();

	/*
	#---------------------------------------Shader-BEGINN-------------------------------------------------------------------------------------------------------------------#
	

	//VERTEX_SHADER
	//deklaration und initialisierung des shaders
	GLuint vertexShader;
	//welchen shader wollen wir COMPILIEREN (vertex shader)
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//wo liegt der shader den wir kompilieren wollen
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//shader kompilieren
	glCompileShader(vertexShader);
	
	//Prüfung ob die Compilation erfolgreich durchgelaufen ist.
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

	//Prüfung ob compile erfolgreich
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "FRAGMENT_SHADER::COMPILATION::ERROR\n" << infoLog << std::endl;
	}

	//SHADER Bauen
	GLuint shaderProgram;
	//gibt eine id von dem letzten erzeugten programm zurück
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

	//Shader löschen, weil sie nicht mehr benötigt werden!
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	
	#---------------------------------------Shader-ENDE---------------------------------------------------------------------------------------------------------------------#
	*/



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


	std::cout << " sizeof(vertices)/sizeof(GLfloat)/3 = " << sizeof(vertices) / sizeof(GLfloat) / 3 << std::endl;
	//main loop (game loop)
	GLfloat delta = 0;
	while (!glfwWindowShouldClose(window))
	{
		GLfloat timeValue = glfwGetTime();
		GLfloat currTime = timeValue;
		//Prüfen und events aufrufen
		glfwPollEvents();

		//rendering commands hier
		glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		GLfloat blueValue = (sin(timeValue) + 0.5);
		GLfloat redValue = (cos(timeValue) + 0.5);
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "uniColor");

		//std::cout << "TimeValue: " << 1/delta << std::endl;
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
	// speicher für die vao und vbo wieder freigeben
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//GLEW Abbrechen, und alle reservierten Daten freigeben
	glfwTerminate();
	return 0;
}

//die funktion wird IMMER aufgerufen, wenn eine Taste gedrückt oder losgelassen wird mit GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//wenn escape key gedrückt wurde sollte sich das Fenster schließen
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	//später in andere klasse auslagern und mit einem boolean versehen.
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	std::cout << "window: "<<window << "\nKey: " << key << "\nScancode: " << scancode << "\nAction: " << action << "\nMode: " << mode << std::endl;
}