#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace GLRenderer {
	void imgui_init(GLFWwindow* window)
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |=
			ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		io.ConfigFlags |=
			ImGuiConfigFlags_NavEnableGamepad;            // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // IF using Docking Branch

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(
			window, true); // Second param install_callback=true will install GLFW
		// callbacks and chain to existing ones.
		ImGui_ImplOpenGL3_Init();
	}


	void imgui_frame_init()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		// ImGui::DockSpaceOverViewport();
		ImGui::DockSpaceOverViewport(0, 0, ImGuiDockNodeFlags_PassthruCentralNode);
	}

	void imgui_frame_end()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void imgui_destroy()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}