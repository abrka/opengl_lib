#pragma once


#include <glad/glad.h>
#include "renderbuffer.h"
#include "texture.h"

namespace GL3D {
	class Framebuffer {
	public:

		unsigned int id{};

		Framebuffer() {
			glGenFramebuffers(1, &id);
		}
		Framebuffer(const Framebuffer& rhs) = delete;
		Framebuffer& operator=(const Framebuffer& rhs) = delete;
		~Framebuffer()
		{
			glDeleteFramebuffers(1, &id);
		}
		void attach_texture(const Texture& texture, const unsigned int mipmap_level = 0) {
			bind();
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, mipmap_level);
			unbind();
		}
		void attach_renderbuffer(const Renderbuffer& renderbuffer) {
			bind();
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer.id);
			unbind();
		}

		void bind() const {
			glBindFramebuffer(GL_FRAMEBUFFER, id);
		}

		void unbind() const {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		bool get_status() const {
			return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		}
	};
}