#pragma once

#include <exception>
#include <stdexcept>
#include <string>
#include <cassert>

#include <glad/glad.h>

namespace GL3D {
	struct VertexShaderTag {};
	struct FragmentShaderTag {};
	
	template<typename ShaderType>
	static int create_opengl_shader_object() {
		static_assert("This type of shader is not supported. use VertexShaderTag or FragmentShaderTag");
		assert(false);
		return -1;
	}
	template<>
	static int create_opengl_shader_object<VertexShaderTag>() {
		return glCreateShader(GL_VERTEX_SHADER);
	}
	template<>
	static int create_opengl_shader_object<FragmentShaderTag>() {
		return glCreateShader(GL_FRAGMENT_SHADER);
	}

	template<typename ShaderType>
	class Shader {
	public:
		unsigned int id{};
		// throws exception
		Shader(const std::string& shader_source_str) {
			const char* shader_source_c_str = shader_source_str.c_str();
			id = create_opengl_shader_object<ShaderType>();
			glShaderSource(id, 1, &shader_source_c_str, NULL);
			glCompileShader(id);
			std::string err_msg = get_shader_compile_error_str();
			if (!err_msg.empty()) {
				throw std::runtime_error( "vertex shader compile error in source:\n" + shader_source_str + "\nerror :" + err_msg );
			}
		}
		Shader(const Shader& rhs) = delete;
		Shader& operator=(const Shader& rhs) = delete;
		~Shader()
		{
			glDeleteShader(id);
		}
	private:
		std::string get_shader_compile_error_str() {
			int  success;
			char infoLog[512];
			glGetShaderiv(id, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(id, 512, NULL, infoLog);
				return std::string(infoLog, 512);
			}
			return "";
		}
	};

}