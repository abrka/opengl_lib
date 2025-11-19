#pragma once 

#include "glfw_util.h"


namespace GLApp {
	class Window {
	public:
		GLFWwindow* glfw_window{};

		Window(int window_width, int window_height, int opengl_version_major, int opengl_version_minor ) {
			glfw_window = glfw_init(window_width, window_height, opengl_version_major, opengl_version_minor);
		}
		Window(const Window&) = delete;
		Window& operator=(const Window& x) = delete;
		~Window() {
			glfw_destroy();
		}
		std::pair<int,int> get_width_and_height() {
			int width{};
			int height{};
			glfwGetWindowSize(glfw_window, &width, &height);
			return { width, height };
		}
		void frame_end() {
			glfw_frame_end(glfw_window);
		}
	};
}