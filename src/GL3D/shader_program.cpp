#include "shader_program.h"

#include <exception>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"

namespace GL3D {
	// throws exception
	ShaderProgram::ShaderProgram(const Shader<VertexShaderTag>& vertex_shader, const Shader<FragmentShaderTag>& fragment_shader) {
		id = glCreateProgram();
		glAttachShader(id, vertex_shader.id);
		glAttachShader(id, fragment_shader.id);
		glLinkProgram(id);
		std::string err_msg = get_shader_program_link_error_str();
		if (!err_msg.empty()) {
			throw std::runtime_error{ "shader link error in id" + std::to_string(id) + "error:" + err_msg };
		}
	}

	ShaderProgram::~ShaderProgram()
	{
		glUseProgram(0);
		glDeleteProgram(id);
	}

	void ShaderProgram::bind() const {
		glUseProgram(id);
	}
	void ShaderProgram::unbind() const {
		glUseProgram(0);
	}
	std::string ShaderProgram::get_shader_program_link_error_str() const {
		int  success;
		char infoLog[512];
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(id, 512, NULL, infoLog);
			return std::string(infoLog, 512);
		}
		return "";
	}
	bool ShaderProgram::set_texture(const std::string& uniformName, const Texture& tex, unsigned int textureUnit) const {
		tex.activate(textureUnit);
		return set_uniform(uniformName, (int)textureUnit);
	}

	void ShaderProgram::set_shader_uniform_from_location(int uniformLocation, float val) const {
		glUniform1f(uniformLocation, val);
	}
	void ShaderProgram::set_shader_uniform_from_location(int uniformLocation, int val) const {
		glUniform1i(uniformLocation, val);
	}
	void ShaderProgram::set_shader_uniform_from_location(int uniformLocation, glm::mat4 val) const {
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
	}
	void ShaderProgram::set_shader_uniform_from_location(int uniformLocation, glm::mat3 val) const {
		glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(val));
	}
	void ShaderProgram::set_shader_uniform_from_location(int uniformLocation, glm::vec3 val) const {
		glUniform3f(uniformLocation, val.x, val.y, val.z);
	}
}