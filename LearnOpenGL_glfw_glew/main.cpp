#include <glew.h>
#include <glfw3.h>
#include <iostream>

//testweise
#include <fstream>
#include <string>
#include <iostream>

#include <time.h>

#include "Images\Color.h"
#include "Images\RGBImage.h"

#include "Math\Vector2f.h"
#include "Math\Vector3f.h"
#include "Math\Vector4f.h"
#include "Math\Matrix4f.h"

#include "Shader\Shader.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


GLfloat vertices[] = {
	0.5f, 0.5f, 0.0f, // Top Right
	0.5f, -0.5f, 0.0f, // Bottom Right
	-0.5f, -0.5f, 0.0f, // Bottom Left
	-0.5f, 0.5f, 0.0f, // Top Left
	//0.0f, 0.0f, 0.0f //mid
};

GLfloat color[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f
};

//Texturkoordinaten
GLuint textCoord[] = {
	1.0f,1.0f,
	1.0f, 0.0f, 
	0.0f, 0.0f, 
	0.0f, 1.0f
};

GLfloat verticesData[] = {
	// Positions          // Colors           // Texture Coords
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
};

GLuint indices[] = { // Note that we start from 0!
	0, 1, 3, // First Triangle
	1, 2, 3 // Second Triangle
};

int main()
{
	//loading textures
	RGBImage wall = RGBImage();
	RGBImage container = RGBImage();
	RGBImage awesomeface = RGBImage();
	wall.loadFromDisk("Loading_Test/Images/wall.bmp");
	container.loadFromDisk("Loading_Test/Images/container.bmp");
	awesomeface.loadFromDisk("Loading_Test/Images/awesomeface.bmp");
	//wall.saveToDisk("Loading_Test/Images/wall_save.bmp");
	//container.saveToDisk("Loading_Test/Images/container_save.bmp");
	awesomeface.saveToDisk("Loading_Test/Images/awesomeface_save.bmp");
	//---------------------------------------------------------------------------

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
	
	//scene + viewport
	int width, height;
	glViewport(0, 0, 800, 600);
	glfwGetFramebufferSize(window, &width, &height);
	glfwSwapInterval(0);
	std::cout << "Size: "<< width << " " << height << std::endl;

	std::cout << "\n\n" << std::endl;

	Shader shader = Shader("Shader/ShaderSource/shaderTest.vertex", "Shader/ShaderSource/shaderTest.fragment");
	GLuint shaderProgram = shader.getProgram();

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
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
		//2. kopieren der index daten in den element buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		// TexCoord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	glBindVertexArray(0);
	
	//Textur erstellen
	GLuint texture;
	glGenTextures(1, &texture);
	//Textur an puffer binden
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Textur generieren
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, container.width(), container.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, container.getCharImage()); //das image ist der char* im format BGRBGRBGR...

	glGenerateMipmap(GL_TEXTURE_2D);

	//unbind buffer
	glBindTexture(GL_TEXTURE_2D, 0);


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

		glBindTexture(GL_TEXTURE_2D, texture);

		//GLfloat blueValue = (sin(timeValue) + 0.5);
		//GLfloat redValue = (cos(timeValue) + 0.5);
		//GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "uniColor");

		std::cout << "" << (int)(1/delta) <<" fps"<< std::endl;
		//drawTriangle
		shader.Use();

		//glUniform4f(vertexColorLocation, redValue, 0.0f, blueValue, 1.0f);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		//Swap buffers
		glfwSwapBuffers(window);

		delta = glfwGetTime() - currTime;
	}
	// speicher für die vao und vbo und ebo wieder freigeben
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
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