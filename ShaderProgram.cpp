#include "ShaderProgram.h"

std::string getFileString(const char* fileName) {
	std::ifstream tp(fileName);
	if (tp) {
		tp.seekg(0, std::ios::end);
		size_t size = tp.tellg();
		std::string string(size, ' ');
		tp.seekg(0);
		tp.read(&string[0], size);
		return string;
	}
	else {
		throw(errno);
	}
}

GLuint ShaderProgram::loadShader(GLenum shaderType, const char* fileName) {
	GLuint shader = glCreateShader(shaderType);
	std::string shaderCode = getFileString(fileName);
	const char* shaderSource = shaderCode.c_str();
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	return shader;
}

void ShaderProgram::compileErrors(GLuint shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}

ShaderProgram::ShaderProgram(const char* vertexShaderFile, const char* geometryShaderFile, const char* fragmentShaderFile) {
	vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderFile);
	compileErrors(vertexShader, "vertex shader");

	if (geometryShaderFile != NULL) {
		geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryShaderFile);
	}
	else {
		geometryShader = 0;
	}
	compileErrors(geometryShader, "geometry shader");

	fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderFile);
	compileErrors(fragmentShader, "fragment shader");

	shaderID = glCreateProgram();

	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	if (geometryShaderFile != NULL) glAttachShader(shaderID, geometryShader);
	glLinkProgram(shaderID);
	compileErrors(shaderID, "main shader");

}

ShaderProgram::~ShaderProgram() {
	glDetachShader(shaderID, vertexShader);
	if (geometryShader != 0) glDetachShader(shaderID, geometryShader);
	glDetachShader(shaderID, fragmentShader);

	glDeleteShader(vertexShader);
	if (geometryShader != 0) glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);

	glDeleteProgram(shaderID);
}

GLuint ShaderProgram::getShaderID() {
	return shaderID;
}

void ShaderProgram::activate() {
	glUseProgram(shaderID);
}

void ShaderProgram::deactivate() {
	glDeleteProgram(shaderID);
}

