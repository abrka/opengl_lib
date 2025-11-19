#pragma once

#include <span>
#include <iostream>
#include <cassert>

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

		Texture(unsigned int _width, unsigned int _height, std::span<unsigned char> _texture_data, TextureSpec _tex_spec) : width(_width), height(_height), texture_spec(_tex_spec) {

			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _tex_spec.wrap_mode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _tex_spec.wrap_mode);
			// set texture filtering parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _tex_spec.filter_type);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _tex_spec.filter_type);


			glTexImage2D(GL_TEXTURE_2D, 0, _tex_spec.internal_texture_format, _width, _height, 0, _tex_spec.texture_format, _tex_spec.texture_data_type, _texture_data.data());

			if (_tex_spec.generate_mipmap) {
				glGenerateMipmap(GL_TEXTURE_2D);
			}

		}

		Texture(const Texture& rhs) = delete;
		Texture& operator=(const Texture& rhs) = delete;

		~Texture()
		{
			glDeleteTextures(1, &id);
		}

		void bind() const {
			glBindTexture(GL_TEXTURE_2D, id);
		}
		void unbind() const {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void activate(const unsigned int TextureUnit) const {
			glActiveTexture(GL_TEXTURE0 + TextureUnit);
			glBindTexture(GL_TEXTURE_2D, id);
		}
	};
}