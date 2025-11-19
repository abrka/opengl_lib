#pragma once 

#include "GL3D/mesh.h"
#include "GL3D/shader.h"



#include "GLApp/glfw_window_raii.h"

#include "glad_util.h"
#include "imgui_util.h"
#include "opengl_util.h"

#include "shader_builder.h"
#include "font.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

namespace GLRenderer {

	class Renderer
	{
		std::shared_ptr<GLApp::Window> window{};
		std::unique_ptr<GL3D::Mesh> mesh{};
		std::unique_ptr<GL3D::ShaderProgram> debug_shader{};
		std::unique_ptr<Font> font{};
		std::unique_ptr<GL3D::ShaderProgram> font_shader{};

	public:
		Renderer(std::shared_ptr<GLApp::Window> window) : window(window) {
			glad_init();
			enable_gl_debug();
			imgui_init(window->glfw_window);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // this makes sure opengl can use bitmap textures with no alighment

			struct Vertex2 {
				glm::vec3 position{};
				glm::vec2 texCoord{};
			};
			Vertex2 quad_vertices[] = {
				{{-0.5, 0.5,0.0}, {0.0,1.0}},
				{{ 0.5, 0.5,0.0}, {1.0,1.0}},
				{{ 0.5,-0.5,0.0}, {1.0,0.0}},
				{{-0.5,-0.5,0.0}, {0.0,0.0}},
			};
			unsigned int quad_indices[] = {
				0,1,3,1,2,3
			};
			int num_floats_per_attr[] = { 3,2 };
			mesh = std::make_unique<GL3D::Mesh>(std::span<Vertex2>(quad_vertices), std::span<int>(num_floats_per_attr), std::span<unsigned int>(quad_indices));

			const std::string asset_dir = std::string(TOSTRING(ASSET_DIR)) + "/";
			try
			{
				debug_shader = ShaderBuilder::build(asset_dir + "shaders/debug_frag.glsl", asset_dir + "shaders/debug_vertex.glsl").value();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << "\n";
				exit(-1);
			}


			font_shader = ShaderBuilder::build(asset_dir + "shaders/font_frag.glsl", asset_dir + "shaders/vertex.glsl").value();

			FT_Library ft_library{};
			FT_Error err = FT_Init_FreeType(&ft_library);
			assert(err == 0);
			font = std::make_unique<Font>(&ft_library, asset_dir + "fonts/0xProtoNerdFontMono-Regular.ttf", 256);
			FT_Done_FreeType(ft_library);
		}

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer& rhs) = delete;

		~Renderer() {
			imgui_destroy();
		}
		void render() {
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


			mesh->draw(*debug_shader);

			auto [screen_width, screen_height] = window->get_width_and_height();
			render_text(text, *font, *font_shader, screen_width, screen_height, x, y, font_scale);

			imgui_frame_end();
		}

	};
}