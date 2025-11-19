#pragma once 

#include <string>

#include <glad/glad.h>


namespace GL3D {
	static std::string get_shader_compile_error_str(unsigned int ShaderID) {
		int  success;
		char infoLog[512];
		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ShaderID, 512, NULL, infoLog);
			return std::string(infoLog, 512);
		}
		return "";
	}


	static std::string get_shader_program_link_error_str(unsigned int ShaderProgramID) {
		int  success;
		char infoLog[512];
		glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ShaderProgramID, 512, NULL, infoLog);
			return std::string(infoLog, 512);
		}
		return "";
	}
}