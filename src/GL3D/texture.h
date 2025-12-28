#pragma once

#include <span>
#include <glad/glad.h>

namespace GL3D {
	struct TextureSpec {
		GLenum internal_texture_format{ GL_RGB };
		GLenum texture_format{ GL_RGB };
		bool generate_mipmap{ true };
		GLenum wrap_mode{ GL_REPEAT };
		GLenum texture_data_type{ GL_UNSIGNED_BYTE };
		GLenum filter_type{ GL_LINEAR };
	};

	class Texture {
	public:
		unsigned int id{};
		unsigned int width{};
		unsigned int height{};
		TextureSpec texture_spec{};

		Texture(unsigned int _width, unsigned int _height, std::span<unsigned char> _texture_data, TextureSpec _tex_spec);
		Texture(const Texture& rhs) = delete;
		Texture& operator=(const Texture& rhs) = delete;
		~Texture();
		void bind() const;
		void unbind() const;
		void activate(const unsigned int TextureUnit) const;
	};
}