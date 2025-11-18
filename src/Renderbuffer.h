#pragma once
#include "glad/glad.h"

class RenderBuffer {
public:
	unsigned int id{};

	RenderBuffer(GLenum InternalFormat, unsigned int width, unsigned int height) {
		glGenRenderbuffers(1, &id);
		glBindRenderbuffer(GL_RENDERBUFFER, id);
		glRenderbufferStorage(GL_RENDERBUFFER, InternalFormat, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0); // 0
	}
	void bind() const{
		glBindRenderbuffer(GL_RENDERBUFFER, id);
	}
	void unbind() const {
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
};