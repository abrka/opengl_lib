#include <iostream>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H


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
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
static bool CursorEnabled = false;

const std::string asset_dir = std::string(TOSTRING(ASSET_DIR)) + "/";

int main() {

	FT_Library ft_library{};
	FT_Error err = FT_Init_FreeType(&ft_library);
	assert(err == 0);
	FT_Face ft_face{};
	std::string ttf_filepath = asset_dir + "fonts/0xProtoNerdFontMono-Regular.ttf";
	err = FT_New_Face(ft_library, ttf_filepath.c_str(), 0, &ft_face);
	assert(err == 0);
	err = FT_Set_Char_Size(
		ft_face,
		0,				/* char_width in 1/64 of points  */
		16 * 64,		/* char_height in 1/64 of points */
		SCR_WIDTH,      /* horizontal device resolution  */
		SCR_HEIGHT);    /* vertical device resolution    */
	assert(err == 0);
	err = FT_Load_Char(ft_face, 'M', FT_LOAD_RENDER);
	assert(err == 0);

	FT_Bitmap ft_bitmap = ft_face->glyph->bitmap;

	GLFWwindow* window = GlfwInit(SCR_WIDTH, SCR_HEIGHT);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetKeyCallback(window, key_callback);

	GladInit();
	EnableGlDebug();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	ImguiInit(window);

	
	TextureSpec font_tex_spec{};
	font_tex_spec.InternalTexFormat = GL_RED;
	font_tex_spec.TextureFormat = GL_RED;
	font_tex_spec.GenerateMipmap = false;
	font_tex_spec.WrapMode = GL_CLAMP_TO_BORDER;
	font_tex_spec.FilterType = GL_NEAREST;
	GlTexture font_tex{ ft_bitmap.width, ft_bitmap.rows, ft_bitmap.buffer, font_tex_spec };

	FT_Done_Face(ft_face);
	FT_Done_FreeType(ft_library);

	struct Vertex2 {
		glm::vec3 position{};
		glm::vec2 texCoord{};
	};
	std::vector<Vertex2> quadVertices{
		{{-1.0, 1.0,0.0}, {0.0,1.0}},
		{{ 1.0, 1.0,0.0}, {1.0,1.0}},
		{{ 1.0,-1.0,0.0}, {1.0,0.0}},
		{{-1.0,-1.0,0.0}, {0.0,0.0}},
	};
	std::vector<unsigned int> quadIndices{
		0,1,3,1,2,3
	};


	GlMesh QuadMesh{ quadVertices, {3,2}, quadIndices };


	GlShaderProgram SampleShader{ asset_dir + "shaders/sample_frag.glsl", asset_dir + "shaders/vertex.glsl" };
	GlShaderProgram ScreenShader{ asset_dir + "shaders/screen_frag.glsl", asset_dir + "shaders/screen_vertex.glsl" };
	GlFramebuffer ScreenFBO{};
	GlTexture ScreenFBOTex{SCR_WIDTH, SCR_HEIGHT,
						   NULL,      TextureSpec{GL_RGB, GL_RGB, false, GL_CLAMP_TO_EDGE} };
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
		//ImGui::ShowDemoWindow(); // Show demo window! :)

		// render
		// ------

		ScreenFBO.Bind();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_BLEND); // enable blending function
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		glm::mat4 model{ 1.0f };
		//model = glm::scale(model, { 0.1f, 0.1f, 0.1f });
		SampleShader.SetUniform("uModel", model);
		SampleShader.SetTexture("font_texture", font_tex, 0);
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

