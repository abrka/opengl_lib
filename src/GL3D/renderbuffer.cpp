#include "renderbuffer.h"

#include <glad/glad.h>

namespace GL3D {
	Renderbuffer::Renderbuffer(GLenum internal_format, unsigned int width, unsigned int height) {
		glGenRenderbuffers(1, &id);
		bind();
		glRenderbufferStorage(GL_RENDERBUFFER, internal_format, width, height);
		unbind();
	}
	Renderbuffer::~Renderbuffer() {
		glDeleteRenderbuffers(1, &id);
	}
	void Renderbuffer::bind() const {
		glBindRenderbuffer(GL_RENDERBUFFER, id);
	}
	void Renderbuffer::unbind() const {
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}