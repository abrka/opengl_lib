#pragma once

#include <string>
#include <glm/fwd.hpp>
#include "shader.h"

namespace GL3D {
	class Texture;
	class ShaderProgram {
	public:
		unsigned int id{};

		// throws exception
		ShaderProgram(const Shader<VertexShaderTag>& vertex_shader, const Shader<FragmentShaderTag>& fragment_shader);
		ShaderProgram(const ShaderProgram& rhs) = delete;
		ShaderProgram& operator=(const ShaderProgram& rhs) = delete;
		~ShaderProgram();
		void bind() const;
		void unbind() const;

		// returns true if the uniform exists
		template<typename T>
		bool set_uniform(const std::string& uniformName, const T val) const {
			bind();
			int uniformLocation = glGetUniformLocation(id, uniformName.c_str());
			if (uniformLocation == -1) {
				return false;
			}
			set_shader_uniform_from_location(uniformLocation, val);
			unbind();
			return true;
		}
		bool set_texture(const std::string& uniformName, const Texture& tex, unsigned int textureUnit) const;
	private:
		std::string get_shader_program_link_error_str() const;
		void set_shader_uniform_from_location(int uniformLocation, float val) const;
		void set_shader_uniform_from_location(int uniformLocation, int val) const;
		void set_shader_uniform_from_location(int uniformLocation, glm::mat4 val) const;
		void set_shader_uniform_from_location(int uniformLocation, glm::mat3 val) const;
		void set_shader_uniform_from_location(int uniformLocation, glm::vec3 val) const;
	};
}