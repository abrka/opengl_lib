#pragma once 

#include <functional>
#include <utility>

struct GLFWwindow;

namespace GLExternalRAII {
	class Window {
	public:
		GLFWwindow* glfw_window{};
		std::function<void(int width, int height)> framebuffer_size_callback{};
		std::function<void(int key, int scancode, int action, int mods)> key_callback{};

		Window(int window_width, int window_height, int opengl_version_major, int opengl_version_minor);
		Window(const Window&) = delete;
		Window& operator=(const Window& x) = delete;
		~Window();
		bool is_running() const;
		std::pair<int, int> get_width_and_height();
		void frame_end();
	private:
		static void glfw_framebuffer_size_callback(GLFWwindow* glfw_window, int width, int height);
		static void glfw_key_callback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);
	};
}