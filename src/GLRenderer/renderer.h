#pragma once 

#include "GL3D/mesh.h"
#include "GL3D/shader.h"


#include "glad_util.h"
#include "imgui_util.h"
#include "opengl_util.h"

#include "font.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

namespace GLRenderer {

	class Renderer
	{
		const std::string asset_dir = std::string(TOSTRING(ASSET_DIR)) + "/";
		std::unique_ptr<Font> font{};
		std::unique_ptr<GL3D::ShaderProgram> font_shader{};

	public:
		Renderer(GLFWwindow* window) {
			glad_init();
			enable_gl_debug();
			imgui_init(window);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // this makes sure opengl can use bitmap textures with no alighment

			struct Vertex2 {
				glm::vec3 position{};
				glm::vec2 texCoord{};
			};
			std::vector<Vertex2> quad_vertices{
				{{-0.5, 0.5,0.0}, {0.0,1.0}},
				{{ 0.5, 0.5,0.0}, {1.0,1.0}},
				{{ 0.5,-0.5,0.0}, {1.0,0.0}},
				{{-0.5,-0.5,0.0}, {0.0,0.0}},
			};
			std::vector<unsigned int> quad_indices{
				0,1,3,1,2,3
			};
			GL3D::Mesh quad_mesh{ quad_vertices, {3,2}, quad_indices };
			
			font_shader = std::make_unique<GL3D::ShaderProgram>( asset_dir + "shaders/font_frag.glsl", asset_dir + "shaders/vertex.glsl" );
			
			FT_Library ft_library{};
			FT_Error err = FT_Init_FreeType(&ft_library);
			assert(err == 0);
			font = std::make_unique<Font>(& ft_library, asset_dir + "fonts/0xProtoNerdFontMono-Regular.ttf", 256 );
			FT_Done_FreeType(ft_library);
		}

		void render(int screen_width, int screen_height) {
			imgui_frame_init();

			ImGui::ShowDemoWindow(); // Show demo window! :)
			static float font_scale{ 1 };
			static float font_pos[2] = { 0,0 };
			ImGui::Begin("Font");
			ImGui::SliderFloat("font scale", &font_scale, 1, 100);
			ImGui::SliderFloat2("font pos", font_pos, 0, 800);
			ImGui::End();

			glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glEnable(GL_BLEND); // enable blending function
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			const std::string text = "adksdlf";
			float x = font_pos[0];
			float y = font_pos[1];

			// render_text(text, *font, *font_shader, screen_width, screen_height, x, y, font_scale);

			imgui_frame_end();
		}

	};
}