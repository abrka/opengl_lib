#pragma once

#include "glad/glad.h"
#include <iostream>
#include <cassert>

struct TextureSpec {
	GLenum InternalTexFormat{ GL_RGB };
	GLenum TextureFormat{ GL_RGB };
	bool GenerateMipmap{ true };
	GLenum WrapMode{ GL_REPEAT };
	GLenum TextureDataType{ GL_UNSIGNED_BYTE };
	GLenum FilterType{ GL_LINEAR };
};


class GlTexture {

public:
	unsigned int ID{};
	unsigned int width{};
	unsigned int height{};
	GLenum TextureFormat{};

	void LoadTexture( unsigned int _width, unsigned int _height, unsigned char* _TextureData, TextureSpec _TexSpec) {

		assert(_TextureData);

		width = _width;
		height = _height;
		TextureFormat = _TexSpec.TextureFormat;

		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _TexSpec.WrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _TexSpec.WrapMode);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _TexSpec.FilterType);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _TexSpec.FilterType);


		glTexImage2D(GL_TEXTURE_2D, 0, _TexSpec.InternalTexFormat, _width, _height, 0, _TexSpec.TextureFormat, _TexSpec.TextureDataType, _TextureData);

		if (_TexSpec.GenerateMipmap) {
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	
	}

	void Bind() const {
		glBindTexture(GL_TEXTURE_2D, ID);
	}
	void Unbind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Activate(const unsigned int TextureUnit) const {
		glActiveTexture(GL_TEXTURE0 + TextureUnit);
		glBindTexture(GL_TEXTURE_2D, ID);
	}
};