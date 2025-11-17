#pragma once

#include <string>
#include <map>
#include <cassert>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"

struct GlFontFace {
	GlTexture face_texture{};
	FT_Vector face_advance{};
	FT_Int face_bitmap_top{};
	FT_Int face_bitmap_left{};
	GlFontFace(FT_GlyphSlot& ft_glyph) : face_advance(ft_glyph->advance), face_bitmap_left(ft_glyph->bitmap_left), face_bitmap_top(ft_glyph->bitmap_top) {
		TextureSpec font_tex_spec{};
		font_tex_spec.InternalTexFormat = GL_RED;
		font_tex_spec.TextureFormat = GL_RED;
		font_tex_spec.GenerateMipmap = false;
		font_tex_spec.WrapMode = GL_CLAMP_TO_BORDER;
		font_tex_spec.FilterType = GL_NEAREST;
		FT_Bitmap* ft_bitmap = &ft_glyph->bitmap;
		face_texture.LoadTexture(ft_bitmap->width, ft_bitmap->rows, ft_bitmap->buffer, font_tex_spec);
	}
};


struct GlFont {
	std::map<FT_ULong, GlFontFace> charcode_to_face_map{};

	GlFont(FT_Library* ft_library, const std::string& font_file_path, FT_UInt font_height) {
		FT_Face ft_face{};
		FT_Error err = FT_New_Face(*ft_library, font_file_path.c_str(), 0, &ft_face);
		assert(err == 0);
		//err = FT_Set_Char_Size(ft_face, 0, char_height * 64, horiz_res, vert_res);
		err = FT_Set_Pixel_Sizes(ft_face, 0, font_height);
		assert(err == 0);

		for (char c = 33; c < 126; c++)
		{
			err = FT_Load_Char(ft_face, c, FT_LOAD_RENDER);
			assert(err == 0);
			charcode_to_face_map.insert({ c, GlFontFace(ft_face->glyph) });
		}


		FT_Done_Face(ft_face);
	}
};

void RenderText(const std::string& text, GlFont& font, GlShaderProgram& FontShader, float current_screen_width, float current_screen_height, float x, float y, float font_scale)
{
	for (auto c = text.begin(); c != text.end(); c++)
	{
		GlFontFace& font_face = font.charcode_to_face_map.at(*c);
		FontShader.SetTexture("font_texture", font_face.face_texture, 0);
		glm::mat4 projection = glm::ortho(0.0f, (float)current_screen_width, 0.0f, (float)current_screen_height);
		FontShader.SetUniform("matrix", projection);

		float advance = font_face.face_advance.x;
		float bearing_x = font_face.face_bitmap_left;
		float bearing_y = font_face.face_bitmap_top;
		float size_x = font_face.face_texture.width;
		float size_y = font_face.face_texture.height;

		float xpos = x + bearing_x * font_scale;
		float ypos = y - (size_y - bearing_y) * font_scale;

		float w = size_x * font_scale;
		float h = size_y * font_scale;

		struct Vertex2 {
			glm::vec3 position{};
			glm::vec2 texCoord{};
		};
		std::vector<Vertex2> vertices = {
			{ { xpos,     ypos + h,0.0 },{ 0.0f, 0.0f } },
			{ { xpos,     ypos,    0.0 },{ 0.0f, 1.0f } },
			{ { xpos + w, ypos,    0.0 },{ 1.0f, 1.0f } },
			{ { xpos,     ypos + h,0.0 },{ 0.0f, 0.0f } },
			{ { xpos + w, ypos,    0.0 },{ 1.0f, 1.0f } },
			{ { xpos + w, ypos + h,0.0 },{ 1.0f, 0.0f } }
		};
		std::vector<unsigned int> indices{ 0,1,2,3,4,5 };
		GlMesh font_mesh{ vertices,{ 3,2 }, indices };
		font_mesh.Draw(FontShader);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += ((int)advance >> 6) * font_scale; // bitshift by 6 to get value in pixels (2^6 = 64)
	}
}