#pragma once 

#include <utility>

struct GLFWwindow;

namespace GLExternalRAII {
	class Window {
	public:
		GLFWwindow* glfw_window{};

		Window(int window_width, int window_height, int opengl_version_major, int opengl_version_minor);
		Window(const Window&) = delete;
		Window& operator=(const Window& x) = delete;
		~Window();
		bool is_running() const;
		std::pair<int, int> get_width_and_height();
		void frame_end();
	};
}