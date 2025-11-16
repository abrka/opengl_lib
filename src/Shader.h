#pragma once
#include <string>
#include "glad/glad.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture.h"

class GlShaderProgram {

public:
	unsigned int ID{ 0 };

	GlShaderProgram(const std::string& FragPath, const std::string& VertexPath) {

		std::ifstream VertexFile{ VertexPath };

		if (not VertexFile.is_open()) {
			std::cout << "couldnt open vertex file from shader program " <<ID<< "the path was "<< VertexPath;
			return;
		}

		std::stringstream VertexStream;
		VertexStream << VertexFile.rdbuf();
		std::string VertexSrc = VertexStream.str();
		const char* VertexSrcCStr = VertexSrc.c_str();

		unsigned int VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(VertexShaderID, 1, &VertexSrcCStr, NULL);
		glCompileShader(VertexShaderID);
		PrintShaderCompileErrors(VertexShaderID);


		std::ifstream FragFile{ FragPath };

		if (not VertexFile.is_open()) {
			std::cout << "couldnt open fragment file from shader program " << ID << "the path was " << FragPath;
			return;
		}

		std::stringstream FragStream;
		FragStream << FragFile.rdbuf();
		std::string FragSrc = FragStream.str();
		const char* FragSrcCStr = FragSrc.c_str();

		unsigned int FragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(FragShaderID, 1, &FragSrcCStr, NULL);
		glCompileShader(FragShaderID);
		PrintShaderCompileErrors(FragShaderID);


		ID = glCreateProgram();
		glAttachShader(ID, VertexShaderID);
		glAttachShader(ID, FragShaderID);
		glLinkProgram(ID);
		PrintShaderProgramLinkErrors(ID);
		glDeleteShader(VertexShaderID);
		glDeleteShader(FragShaderID);
	}


	void Bind() const {
		glUseProgram(ID);
	}
	void Unbind() const {
		glUseProgram(0);
	}

	static void PrintShaderCompileErrors(unsigned int ShaderID) {
		int  success;
		char infoLog[512];
		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ShaderID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}


	static void PrintShaderProgramLinkErrors(unsigned int ShaderProgramID){
		int  success;
		char infoLog[512];
		glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ShaderProgramID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::LINKER ERROR\n" << infoLog << std::endl;
		}
	}




	template<typename T>
	void SetUniform(const std::string& uniformName, T val) {
		Bind();
		int uniformLocation = glGetUniformLocation(ID, uniformName.c_str());
		if (uniformLocation == -1) {
			std::cerr << "the uniform youre setting: " << uniformName << " does not exist/it is the wrong type/ it is not used by all shaders/it was discarded by the shader compiler because it is unused\n";
		}
		setShaderUniformFromLocation(ID, uniformLocation, val);
	}
	void SetTexture(const std::string& uniformName, const GlTexture& tex, unsigned int textureUnit) {
		tex.Activate(textureUnit);
		SetUniform(uniformName, (int)textureUnit);
	}

	GlShaderProgram(const GlShaderProgram& rhs) = delete;
	GlShaderProgram& operator=(const GlShaderProgram& rhs) = delete;

private:
	void setShaderUniformFromLocation(unsigned int shaderProgram, int uniformLocation, float val) {
		glUniform1f(uniformLocation, val);
	}
	void setShaderUniformFromLocation(unsigned int shaderProgram, int uniformLocation, int val) {
		glUniform1i(uniformLocation, val);
	}
	void setShaderUniformFromLocation(unsigned int shaderProgram, int uniformLocation, glm::mat4 val) {
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
	}
	void setShaderUniformFromLocation(unsigned int shaderProgram, int uniformLocation, glm::mat3 val) {
		glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
	}
	void setShaderUniformFromLocation(unsigned int shaderProgram, int uniformLocation, glm::vec3 val) {
		glUniform3f(uniformLocation, val.x, val.y, val.z);
	}

	
};