#include "Shader.h"

Shader::Shader(const GLchar * vertexShaderPath, const GLchar * fragmentShaderPath)
{
	const char* vertexShaderSource = load(vertexShaderPath).c_str();
	const char* fragmentShaderSource = load(fragmentShaderPath).c_str();

	/*
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
	* Prüfung ob die Compilation erfolgreich durchgelaufen ist.
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

	//Prüfung ob compile erfolgreich
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "FRAGMENT_SHADER::COMPILATION::ERROR\n" << infoLog << std::endl;
	}

	//SHADER Bauen
	//GLuint shaderProgram; //steht jetzt am anfang
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
}

void Shader::Use()
{
	glUseProgram(shaderProgram);
}

GLuint Shader::getProgram()
{
	return shaderProgram;
}

Shader::~Shader()
{
}

std::string Shader::load(std::string dateipfad)
{
	std::stringstream ss;
	std::ifstream datei(dateipfad);

	if (!datei) {
		std::cerr << dateipfad << " konnte nicht geöffnet werden" << std::endl;
	}
	else {
		/*
		Datei zeileweise auslesen und hinter jeder Zeile einen Zeilenumbruch schreiben.
		*/
		while(datei){
			std::string zeile;
			std::getline(datei, zeile);
			ss << zeile;
		}
	}
	datei.close();

	std::string ausgabe = ss.str();

	std::cout << ss.str() << std::endl;

	return ausgabe.c_str();
}

std::string Shader::loadNeu(char * dateipfad)
{
	std::string shaderCode;
	std::ifstream datei(dateipfad, std::ios::in);

	if (!datei.good()) {
		std::cout << dateipfad << " konnte nicht geöffnet werden." << std::endl;
		std::terminate();
	}

	datei.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)datei.tellg());
	datei.seekg(0, std::ios::beg);
	datei.read(&shaderCode[0], shaderCode.size());
	datei.close();

	std::cout << shaderCode << std::endl;

	return shaderCode;
}
