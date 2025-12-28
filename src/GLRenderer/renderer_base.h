#pragma once

namespace GLExternalRAII {
	class Window;
}

namespace GLRenderer {
	class RendererBase {
	public:
		RendererBase(GLExternalRAII::Window& window);
		RendererBase(const RendererBase&) = delete;
		RendererBase& operator=(const RendererBase& rhs) = delete;
		virtual ~RendererBase();
		void render();
		virtual void render_user() = 0;
	protected:
		GLExternalRAII::Window* window{};
	};
}