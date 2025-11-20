#pragma once
#include "glad/glad.h"

namespace GL3D {
	class Renderbuffer {
	public:
		unsigned int id{};

		Renderbuffer(GLenum internal_format, unsigned int width, unsigned int height) {
			glGenRenderbuffers(1, &id);
			bind();
			glRenderbufferStorage(GL_RENDERBUFFER, internal_format, width, height);
			unbind();
		}
		Renderbuffer(const Renderbuffer& rhs) = delete;
		Renderbuffer& operator=(const Renderbuffer& rhs) = delete;
		~Renderbuffer() {
			glDeleteRenderbuffers(1, &id);
		}
		void bind() const {
			glBindRenderbuffer(GL_RENDERBUFFER, id);
		}
		void unbind() const {
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}
	};
}