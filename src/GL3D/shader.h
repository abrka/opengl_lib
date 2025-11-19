#pragma once


#include <exception>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_utils.h"
#include "texture.h"

namespace GL3D {
	

	struct VertexShaderTag {};
	struct FragmentShaderTag {};

	template<typename ShaderType>
	class Shader {

	public:
		unsigned int id{};

	private:
		template<typename T>
		int create_opengl_shader_object() {
			static_assert("This type of shader is not supported. use VertexShaderTag or FragmentShaderTag");
			assert(false);
			return -1;
		}
		template<>
		int create_opengl_shader_object<VertexShaderTag>() {
			return glCreateShader(GL_VERTEX_SHADER);
		}
		template<>
		int create_opengl_shader_object<FragmentShaderTag>() {
			return glCreateShader(GL_FRAGMENT_SHADER);
		}
	public:
		// throws exception
		Shader(const std::string& shader_source_str) {
			const char* shader_source_c_str = shader_source_str.c_str();
			id = create_opengl_shader_object<ShaderType>();
			glShaderSource(id, 1, &shader_source_c_str, NULL);
			glCompileShader(id);
			std::string err_msg = get_shader_compile_error_str(id);
			if (!err_msg.empty()) {
				throw std::runtime_error{ "vertex shader compile error in source:\n" + shader_source_str + "\nerror :" + err_msg };
			}
		}

		Shader(const Shader& rhs) = delete;
		Shader& operator=(const Shader& rhs) = delete;

		~Shader()
		{
			glDeleteShader(id);
		}


	};
}