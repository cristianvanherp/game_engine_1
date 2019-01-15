#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	int success;
	char infoLog[512];

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

	//Defining and compiling vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Defining and compiling fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		getchar();
	}

	//Shader program
	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertexShader);
	glAttachShader(this->ID, fragmentShader);
	glLinkProgram(this->ID);
	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		getchar();
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::use() {
	glUseProgram(this->ID);
}

void ShaderProgram::setBool(const std::string &name, bool value) {
	glUniform1i(glGetUniformLocation((GLuint)this->ID, name.c_str()), value);
}

void ShaderProgram::setInt(const std::string &name, int value) {
	glUniform1i(glGetUniformLocation((GLuint)this->ID, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string &name, float value) {
	glUniform1f(glGetUniformLocation((GLuint)this->ID, name.c_str()), value);
}