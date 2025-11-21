#pragma once

#include <glad/glad.h>

#include "GLExternalRAII/glfw_window_raii.h"

#include "GLExternalUtils/glad_util.h"
#include "GLExternalUtils/imgui_util.h"
#include "GLExternalUtils/opengl_util.h"

namespace GLRenderer {
	class RendererBase {
	protected:
		std::shared_ptr<GLApp::Window> window{};
	public:
		RendererBase(std::shared_ptr<GLApp::Window> window) : window(window) {
			glad_init();
			enable_gl_debug();
			imgui_init(window->glfw_window);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // this makes sure opengl can use bitmap textures with no alighment
		}
		RendererBase(const RendererBase&) = delete;
		RendererBase& operator=(const RendererBase& rhs) = delete;

		virtual ~RendererBase() {
			imgui_destroy();
		}
		virtual void render_user() = 0;
		void render() {
			imgui_frame_init();
			render_user();
			imgui_frame_end();
		}
		void on_window_resize(int width, int height) {
			glViewport(0, 0, width, height);
		}
	};
}