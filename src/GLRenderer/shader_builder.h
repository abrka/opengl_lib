#pragma once

#include <memory>
#include <filesystem>
#include <expected>

#include "GL3D/shader_program.h"
#include "utils.h"

namespace GLRenderer {
	namespace ShaderBuilder {
		enum class ShaderBuilderError {
			frag_shader_file_not_found,
			vert_shader_file_not_found
		};
		std::expected<std::unique_ptr<GL3D::ShaderProgram>, ShaderBuilderError> build(std::filesystem::path frag_shader_filepath, std::filesystem::path vertex_shader_filepath) {
			auto frag_shader_str = GLUtils::read_string_from_filepath(frag_shader_filepath);
			if (!frag_shader_str.has_value()) {
				return std::unexpected(ShaderBuilderError::frag_shader_file_not_found);
			}
			auto vert_shader_str = GLUtils::read_string_from_filepath(vertex_shader_filepath);
			if (!vert_shader_str.has_value()) {
				return std::unexpected(ShaderBuilderError::vert_shader_file_not_found);
			}
			auto vertex_shader = GL3D::Shader<GL3D::VertexShaderTag>{ vert_shader_str.value()};
			auto fragment_shader = GL3D::Shader<GL3D::FragmentShaderTag>{ frag_shader_str.value() };
			auto shader_program = std::make_unique<GL3D::ShaderProgram>(vertex_shader, fragment_shader);
			return shader_program;
		}
	};
}