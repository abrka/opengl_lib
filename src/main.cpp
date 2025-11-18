#include <iostream>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "glad_util.h"
#include "glfw_util.h"
#include "opengl_util.h"
#include "imgui_util.h"

#include "frame_buffer.h"
#include "mesh.h"
#include "render_buffer.h"
#include "shader.h"
#include "texture.h"
#include "font.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action,
	int mods);
void processInput(GLFWwindow* window);


// settings
const unsigned int initial_screen_width = 800;
const unsigned int initial_screen_height = 800;

static unsigned int current_screen_width = initial_screen_width;
static unsigned int current_screen_height = initial_screen_height;
static bool CursorEnabled = false;

const std::string asset_dir = std::string(TOSTRING(ASSET_DIR)) + "/";

int main() {



	GLFWwindow* window = glfw_init(initial_screen_width, initial_screen_height);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetKeyCallback(window, key_callback);

	glad_init();
	enable_gl_debug();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // this makes sure opengl can use bitmap textures with no alighment

	imgui_init(window);

	FT_Library ft_library{};
	FT_Error err = FT_Init_FreeType(&ft_library);
	assert(err == 0);
	Font font{ &ft_library, asset_dir + "fonts/0xProtoNerdFontMono-Regular.ttf", 256 };
	FT_Done_FreeType(ft_library);


	struct Vertex2 {
		glm::vec3 position{};
		glm::vec2 texCoord{};
	};
	std::vector<Vertex2> quadVertices{
		{{-0.5, 0.5,0.0}, {0.0,1.0}},
		{{ 0.5, 0.5,0.0}, {1.0,1.0}},
		{{ 0.5,-0.5,0.0}, {1.0,0.0}},
		{{-0.5,-0.5,0.0}, {0.0,0.0}},
	};
	std::vector<unsigned int> quadIndices{
		0,1,3,1,2,3
	};


	Mesh QuadMesh{ quadVertices, {3,2}, quadIndices };

	ShaderProgram FontShader{ asset_dir + "shaders/font_frag.glsl", asset_dir + "shaders/vertex.glsl" };

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window)) {
		// input
		// -----
		processInput(window);

		// (Your code calls glfwPollEvents())
		// ...
		// Start the Dear ImGui frame
		imgui_frame_init();
		// ImGui::ShowDemoWindow(); // Show demo window! :)
		static float font_scale{ 1 };
		static float font_pos[2] = {0,0};
		ImGui::Begin("Font");
		ImGui::SliderFloat("font scale", &font_scale, 1, 100);
		ImGui::SliderFloat2("font pos", font_pos, 0, current_screen_width);
		ImGui::End();
		// render
		// ------



		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_BLEND); // enable blending function
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);





		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Render both front and back faces as lines
		const std::string text = "adksdlf";
		float x = font_pos[0];
		float y = font_pos[1];
		render_text(text, font, FontShader, current_screen_width, current_screen_height, x, y, font_scale);



		// Rendering
		// (Your code clears your framebuffer, renders your other stuff etc.)

		// render imgui here 

		// render imgui end

		imgui_frame_end();
		glfw_frame_end(window);
	}
	imgui_end();
	glfw_end();
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
	current_screen_width = width;
	current_screen_height = height;
	glViewport(0, 0, width, height);
}

