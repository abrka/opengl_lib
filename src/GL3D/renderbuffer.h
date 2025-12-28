#pragma once

#include <glad/glad.h>

namespace GL3D {
	class Renderbuffer {
	public:
		unsigned int id{};

		Renderbuffer(GLenum internal_format, unsigned int width, unsigned int height);
		Renderbuffer(const Renderbuffer& rhs) = delete;
		Renderbuffer& operator=(const Renderbuffer& rhs) = delete;
		~Renderbuffer();
		void bind() const;
		void unbind() const;
	};
}