#pragma once

#include <memory>
#include <filesystem>

#include <tl/expected.hpp>

#include "GL3D/shader_program.h"
#include "utils.h"

namespace GLRenderer {
	namespace ShaderBuilder {
		enum class ShaderBuilderErrorType {
			frag_shader_compile_error,
			vert_shader_compile_error,
			shader_link_error,
			frag_shader_file_not_found,
			vert_shader_file_not_found
		};
		struct ShaderBuilderError {
			ShaderBuilderErrorType err{};
			std::string err_msg{};
		};
		tl::expected<std::unique_ptr<GL3D::ShaderProgram>, ShaderBuilderError> build(std::filesystem::path frag_shader_filepath, std::filesystem::path vertex_shader_filepath) {
			auto frag_shader_source_str = GLUtils::read_string_from_filepath(frag_shader_filepath);
			if (!frag_shader_source_str.has_value()) {
				return tl::unexpected(ShaderBuilderError{ ShaderBuilderErrorType::frag_shader_file_not_found, "" });
			}
			auto vert_shader_source_str = GLUtils::read_string_from_filepath(vertex_shader_filepath);
			if (!vert_shader_source_str.has_value()) {
				return tl::unexpected(ShaderBuilderError{ ShaderBuilderErrorType::vert_shader_file_not_found, "" });
			}
			std::unique_ptr<GL3D::Shader<GL3D::VertexShaderTag>> vertex_shader{};
			try
			{
				vertex_shader = std::make_unique<GL3D::Shader<GL3D::VertexShaderTag>>( vert_shader_source_str.value() );
			}
			catch (const std::exception& e)
			{
				return tl::unexpected(ShaderBuilderError{ ShaderBuilderErrorType::vert_shader_compile_error, e.what() });
			}

			std::unique_ptr<GL3D::Shader<GL3D::FragmentShaderTag>> fragment_shader{};
			try
			{
				fragment_shader = std::make_unique<GL3D::Shader<GL3D::FragmentShaderTag>>(frag_shader_source_str.value());
			}
			catch (const std::exception& e)
			{
				return tl::unexpected(ShaderBuilderError{ ShaderBuilderErrorType::frag_shader_compile_error, e.what() });
			}
			std::unique_ptr<GL3D::ShaderProgram> shader_program{};
			try {
				shader_program = std::make_unique<GL3D::ShaderProgram>(*vertex_shader, *fragment_shader);
			}
			catch (const std::exception& e)
			{
				return tl::unexpected(ShaderBuilderError{ ShaderBuilderErrorType::shader_link_error, e.what() });
			}
			return shader_program;
		}
	};
}