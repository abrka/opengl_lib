#pragma once
#include "Texture.h"
#include "Renderbuffer.h"

class FrameBuffer {
public:

	unsigned int id{};

	FrameBuffer() {
		glGenFramebuffers(1, &id);
	}

	void attach_texture(const Texture& Tex, const GLenum AttachToWhat, const unsigned int MipmapLevel = 0) {
		glBindFramebuffer(GL_FRAMEBUFFER, id);
		glFramebufferTexture2D(GL_FRAMEBUFFER, AttachToWhat, GL_TEXTURE_2D, Tex.id, MipmapLevel);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void atttach_render_buffer(const RenderBuffer& RenderBuffer) {
		glBindFramebuffer(GL_FRAMEBUFFER, id);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RenderBuffer.id);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	void bind() const{
		glBindFramebuffer(GL_FRAMEBUFFER, id);
	}

	void unbind() const{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	bool check_status() const {
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
			return false;
		}
		else {
			return true;
		}
	}
};