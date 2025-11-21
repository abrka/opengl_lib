#pragma once

#include <glad/glad.h>

#include "GLExternalRAII/glfw_window_raii.h"

#include "GLExternalUtils/glad_util.h"
#include "GLExternalUtils/imgui_util.h"
#include "GLExternalUtils/opengl_util.h"

namespace GLRenderer {
	class RendererBase {
	protected:
		std::shared_ptr<GLExternalRAII::Window> window{};
	public:
		RendererBase(std::shared_ptr<GLExternalRAII::Window> window) : window(window) {
			GLExternalUtils::glad_init();
			GLExternalUtils::enable_gl_debug();
			GLExternalUtils::imgui_init(window->glfw_window);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // this makes sure opengl can use bitmap textures with no alighment
		}
		RendererBase(const RendererBase&) = delete;
		RendererBase& operator=(const RendererBase& rhs) = delete;

		virtual ~RendererBase() {
			GLExternalUtils::imgui_destroy();
		}
		virtual void render_user() = 0;
		void render() {
			GLExternalUtils::imgui_frame_init();
			render_user();
			GLExternalUtils::imgui_frame_end();
			window->frame_end();
		}
		void on_window_resize(int width, int height) {
			glViewport(0, 0, width, height);
		}
	};
}