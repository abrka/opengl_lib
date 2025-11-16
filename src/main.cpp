#include <iostream>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GladUtil.h"
#include "GlfwUtil.h"
#include "GlUtils.h"
#include "ImguiUtil.h"

#include "Framebuffer.h"
#include "Mesh.h"
#include "Renderbuffer.h"
#include "Shader.h"
#include "Texture.h"


#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action,
	int mods);
void processInput(GLFWwindow* window);


// settings
const unsigned int SCR_WIDTH = 1080;
const unsigned int SCR_HEIGHT = 800;
static bool CursorEnabled = false;


int main() {

	GLFWwindow* window = GlfwInit(SCR_WIDTH, SCR_HEIGHT);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetKeyCallback(window, key_callback);

	GladInit();
	EnableGlDebug();
	ImguiInit(window);

	struct Vertex2 {
		glm::vec3 position{};
		glm::vec2 texCoord{};
	};
	std::vector<Vertex2> quadVertices{
		Vertex2{glm::vec3{-1.0f, 1.0f, 0.0f}, glm::vec2{0.0f, 1.0f}},
		Vertex2{glm::vec3{-1.0f, -1.0f, 0.0f}, glm::vec2{0.0f, 0.0f}},
		Vertex2{glm::vec3{1.0f, -1.0f, 0.0f}, glm::vec2{1.0f, 0.0f}},
		Vertex2{glm::vec3{-1.0f, 1.0f, 0.0f}, glm::vec2{0.0f, 1.0f}},
		Vertex2{glm::vec3{1.0f, -1.0f, 0.0f}, glm::vec2{1.0f, 0.0f}},
		Vertex2{glm::vec3{1.0f, 1.0f, 0.0f}, glm::vec2{1.0f, 1.0f}}
	};
	std::vector<unsigned int> quadIndices{
		0,1,2,3,4,5
	};
	GlMesh QuadMesh{ quadVertices, {3,2}, quadIndices };



	std::string asset_dir = std::string(TOSTRING(ASSET_DIR)) + "/";

	GlShaderProgram SampleShader{ asset_dir + "shaders/sample_frag.glsl", asset_dir + "shaders/vertex.glsl" };
	GlShaderProgram ScreenShader{ asset_dir + "shaders/screen_frag.glsl", asset_dir + "shaders/screen_vertex.glsl" };
	GlFramebuffer ScreenFBO{};
	GlTexture ScreenFBOTex{ GL_RGB,    GL_RGB,
						   SCR_WIDTH, SCR_HEIGHT,
						   NULL,      TextureSpec{false, GL_CLAMP_TO_EDGE} };
	GlRenderBuffer ScreenRBO{ GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT };
	ScreenFBO.AttachTexture(ScreenFBOTex, GL_COLOR_ATTACHMENT0);
	ScreenFBO.AttachRenderBuffer(ScreenRBO);
	ScreenFBO.CheckStatus();

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window)) {
		// input
		// -----
		processInput(window);

		// (Your code calls glfwPollEvents())
		// ...
		// Start the Dear ImGui frame
		ImguiFrameInit();
		ImGui::ShowDemoWindow(); // Show demo window! :)

		// render
		// ------

		ScreenFBO.Bind();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_BLEND); // enable blending function
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		glm::mat4 model{ 1.0f };
		model = glm::scale(model, { 0.1f, 0.1f, 0.1f });
		SampleShader.SetUniform("uModel", model);
		QuadMesh.Draw(SampleShader);


		ScreenFBO.Unbind();

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ScreenShader.SetTexture("screenTexture", ScreenFBOTex, 0);
		QuadMesh.Draw(ScreenShader);
		ScreenShader.Unbind();

		// Rendering
		// (Your code clears your framebuffer, renders your other stuff etc.)
		
		// render imgui here 

		// render imgui end

		ImguiFrameEnd();
		GlfwFrameEnd(window);
	}
	ImguiEnd();
	GlfwEnd();
	return 0;
}



void key_callback(GLFWwindow* window, int key, int scancode, int action,
	int mods) {
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) {
		if (CursorEnabled) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			CursorEnabled = false;
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			CursorEnabled = true;
		}
	}
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void cursor_position_callback(GLFWwindow* window, double xposIn,
	double yposIn) {
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width
	// and height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

