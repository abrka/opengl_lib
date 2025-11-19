#pragma once

#include <string_view>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "texture.h"

namespace GL3D {
	class ShaderProgram {

	public:
		unsigned int id{};

		ShaderProgram(const std::string& frag_shader_str, const std::string& vertex_shader_str) {
			
			const char* vertex_shader_c_str = vertex_shader_str.c_str();
			unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex_shader_id, 1, &vertex_shader_c_str, NULL);
			glCompileShader(vertex_shader_id);
			print_shader_compile_error(vertex_shader_id);


			const char* frag_shader_c_str = frag_shader_str.c_str();
			unsigned int frag_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(frag_shader_id, 1, &frag_shader_c_str, NULL);
			glCompileShader(frag_shader_id);
			print_shader_compile_error(frag_shader_id);


			id = glCreateProgram();
			glAttachShader(id, vertex_shader_id);
			glAttachShader(id, frag_shader_id);
			glLinkProgram(id);
			print_shader_program_link_error(id);
			glDeleteShader(vertex_shader_id);
			glDeleteShader(frag_shader_id);
		}

		ShaderProgram(const ShaderProgram& rhs) = delete;
		ShaderProgram& operator=(const ShaderProgram& rhs) = delete;

		~ShaderProgram()
		{
			glUseProgram(0);
			glDeleteProgram(id);
		}

		void bind() const {
			glUseProgram(id);
		}
		void unbind() const {
			glUseProgram(0);
		}

	private:
		static void print_shader_compile_error(unsigned int ShaderID) {
			int  success;
			char infoLog[512];
			glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(ShaderID, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
		}


		static void print_shader_program_link_error(unsigned int ShaderProgramID) {
			int  success;
			char infoLog[512];
			glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(ShaderProgramID, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::LINKER ERROR\n" << infoLog << std::endl;
			}
		}


	public:

		template<typename T>
		void set_uniform(const std::string& uniformName, T val) {
			bind();
			int uniformLocation = glGetUniformLocation(id, uniformName.c_str());
			if (uniformLocation == -1) {
				std::cerr << "the uniform youre setting: " << uniformName << " does not exist/it is the wrong type/ it is not used by all shaders/it was discarded by the shader compiler because it is unused\n";
			}
			set_shader_uniform_from_location(id, uniformLocation, val);
		}
		void set_texture(const std::string& uniformName, const Texture& tex, unsigned int textureUnit) {
			tex.activate(textureUnit);
			set_uniform(uniformName, (int)textureUnit);
		}


	private:
		void set_shader_uniform_from_location(unsigned int shaderProgram, int uniformLocation, float val) {
			glUniform1f(uniformLocation, val);
		}
		void set_shader_uniform_from_location(unsigned int shaderProgram, int uniformLocation, int val) {
			glUniform1i(uniformLocation, val);
		}
		void set_shader_uniform_from_location(unsigned int shaderProgram, int uniformLocation, glm::mat4 val) {
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
		}
		void set_shader_uniform_from_location(unsigned int shaderProgram, int uniformLocation, glm::mat3 val) {
			glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
		}
		void set_shader_uniform_from_location(unsigned int shaderProgram, int uniformLocation, glm::vec3 val) {
			glUniform3f(uniformLocation, val.x, val.y, val.z);
		}


	};
}