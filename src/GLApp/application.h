#pragma once

#include <iostream>

#include "GLRenderer/renderer.h"
#include "glfw_window_raii.h"


#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)


namespace GLApp {
	class Application
	{
		std::shared_ptr<Window> window{};
		std::unique_ptr<GLRenderer::Renderer> renderer{};

	private:
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		}
	public:
		Application(int initial_screen_width, int initial_screen_height, int opengl_version_major, int opengl_version_minor) {
			window = std::make_shared<Window>(initial_screen_width, initial_screen_height, opengl_version_major, opengl_version_minor);
			glfwSetFramebufferSizeCallback(window->glfw_window, framebuffer_size_callback);
			renderer = std::make_unique<GLRenderer::Renderer>(window);
		}
		Application(const Application&) = delete;           
		Application& operator=(const Application& rhs) = delete;
		void run() {
			while (!glfwWindowShouldClose(window->glfw_window)) {
				int width{};
				int height{};
				glfwGetWindowSize(window->glfw_window, &width, &height);
				renderer->render(width, height);
				glfw_frame_end(window->glfw_window);
			}
		}
	};
}

