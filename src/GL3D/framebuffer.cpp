#include "framebuffer.h"

#include <glad/glad.h>
#include "renderbuffer.h"
#include "texture.h"

namespace GL3D {
	Framebuffer::Framebuffer() {
		glGenFramebuffers(1, &id);
	}
	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &id);
	}
	void Framebuffer::attach_texture(const Texture& texture, unsigned int mipmap_level) {
		bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, mipmap_level);
		unbind();
	}
	void Framebuffer::attach_renderbuffer(const Renderbuffer& renderbuffer) {
		bind();
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer.id);
		unbind();
	}
	void Framebuffer::bind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, id);
	}
	void Framebuffer::unbind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	bool Framebuffer::get_status() const {
		return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	}
}