#pragma once


namespace GL3D {
	class Texture;
	class Renderbuffer;
	class Framebuffer {
	public:
		unsigned int id{};

		Framebuffer();
		Framebuffer(const Framebuffer& rhs) = delete;
		Framebuffer& operator=(const Framebuffer& rhs) = delete;
		~Framebuffer();
		void attach_texture(const Texture& texture, unsigned int mipmap_level = 0);
		void attach_renderbuffer(const Renderbuffer& renderbuffer);
		void bind() const;
		void unbind() const;
		bool get_status() const;
	};
}