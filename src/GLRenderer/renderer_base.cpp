#include "renderer_base.h"

#include <glad/glad.h>
#include "GLExternalRAII/glfw_window_raii.h"
#include "GLExternalUtils/glad_util.h"
#include "GLExternalUtils/imgui_util.h"
#include "GLExternalUtils/opengl_util.h"

namespace GLRenderer {
	RendererBase::RendererBase(GLExternalRAII::Window& window) : window(&window) {
		GLExternalUtils::glad_init();
		GLExternalUtils::enable_gl_debug();
		GLExternalUtils::imgui_init(window.glfw_window);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // this makes sure opengl can use bitmap textures with no alighment
	}
	RendererBase::~RendererBase() {
		GLExternalUtils::imgui_destroy();
	}
	void RendererBase::render() {
		GLExternalUtils::imgui_frame_init();
		render_user();
		GLExternalUtils::imgui_frame_end();
		window->frame_end();
	}
}