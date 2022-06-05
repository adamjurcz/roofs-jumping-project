#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string getFileString(const char* filename);


class ShaderProgram {
private:
	GLuint shaderID;
	GLuint vertexShader;
	GLuint geometryShader;
	GLuint fragmentShader;
	GLuint loadShader(GLenum shaderType, const char* fileName);
	void compileErrors(GLuint shader, const char* type);
public:
	ShaderProgram(const char* vertexShaderFile, const char* geometryShaderFile, const char* fragmentShaderFile);
	~ShaderProgram();
	void activate();
	void deactivate();

    inline void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    inline void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    inline void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    inline void setVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
    }
    inline void setVec2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(shaderID, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    inline void setVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
    }
    inline void setVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(shaderID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    inline void setVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
    }
    inline void setVec4(const std::string& name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(shaderID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    inline void setMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    inline void setMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    inline void setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

	GLuint getShaderID();
};

#endif
