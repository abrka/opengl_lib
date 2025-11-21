#pragma once


#include <exception>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "texture.h"

namespace GL3D {
	class ShaderProgram {
	public:
		unsigned int id{};

		// throws exception
		ShaderProgram(const Shader<VertexShaderTag>& vertex_shader, const Shader<FragmentShaderTag>& fragment_shader) {
			id = glCreateProgram();
			glAttachShader(id, vertex_shader.id);
			glAttachShader(id, fragment_shader.id);
			glLinkProgram(id);
			std::string err_msg = get_shader_program_link_error_str(id);
			if (!err_msg.empty()) {
				throw std::runtime_error{ "shader link error in id" + std::to_string(id) + "error:" + err_msg };
			}
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

		// returns true if the uniform exists
		template<typename T>
		bool set_uniform(const std::string& uniformName, T val) {
			bind();
			int uniformLocation = glGetUniformLocation(id, uniformName.c_str());
			if (uniformLocation == -1) {
				return false;
			}
			set_shader_uniform_from_location(uniformLocation, val);
			unbind();
			return true;
		}
		void set_texture(const std::string& uniformName, const Texture& tex, unsigned int textureUnit) {
			tex.activate(textureUnit);
			set_uniform(uniformName, (int)textureUnit);
		}


	private:
		void set_shader_uniform_from_location(int uniformLocation, float val) {
			glUniform1f(uniformLocation, val);
		}
		void set_shader_uniform_from_location(int uniformLocation, int val) {
			glUniform1i(uniformLocation, val);
		}
		void set_shader_uniform_from_location(int uniformLocation, glm::mat4 val) {
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
		}
		void set_shader_uniform_from_location(int uniformLocation, glm::mat3 val) {
			glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
		}
		void set_shader_uniform_from_location(int uniformLocation, glm::vec3 val) {
			glUniform3f(uniformLocation, val.x, val.y, val.z);
		}


	};
}