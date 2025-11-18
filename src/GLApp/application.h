#pragma once

#include <iostream>

#include "GLRenderer/renderer.h"
#include "glfw_util.h"



#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)


namespace GLApp {
	

	class Application
	{
		GLFWwindow* window{};
		std::unique_ptr<GLRenderer::Renderer> renderer{};

	private:
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		}
	public:
		Application(int initial_screen_width, int initial_screen_height) {
			window = glfw_init(initial_screen_width, initial_screen_height);
			// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
			renderer = std::make_unique<GLRenderer::Renderer>(window);
		}
		~Application()
		{
			imgui_end();
			glfw_end();
		}
		void run() {
			while (!glfwWindowShouldClose(window)) {
				int width{};
				int height{};
				glfwGetWindowSize(window, &width, &height);
				renderer->render(width,height);
				glfw_frame_end(window);
			}
		}
	};
}

