#pragma once

#include <map>
#include <cassert>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Texture.h"

struct GlFontFace {
	GlTexture face_texture{};
	FT_Glyph_Metrics face_metrics{};
	GlFontFace(FT_Bitmap* ft_bitmap) {
		TextureSpec font_tex_spec{};
		font_tex_spec.InternalTexFormat = GL_RED;
		font_tex_spec.TextureFormat = GL_RED;
		font_tex_spec.GenerateMipmap = false;
		font_tex_spec.WrapMode = GL_CLAMP_TO_BORDER;
		font_tex_spec.FilterType = GL_NEAREST;
		GlTexture font_tex{ ft_bitmap.width, ft_bitmap.rows, ft_bitmap.buffer, font_tex_spec };
	}
};
namespace std
{
	template<> struct less<GlFontFace>
	{
		bool operator() (const GlFontFace& lhs, const GlFontFace& rhs) const
		{
			assert(lhs.face_texture.ID != rhs.face_texture.ID);
			return lhs.face_texture.ID < rhs.face_texture.ID;
		}
	};
}

struct GlFont {
	std::map<FT_ULong, GlFontFace> charcode_to_face_map{};

	GlFont(FT_Library* ft_library, const std::string& font_file_path) {
		FT_Face ft_face{};
		err = FT_New_Face(ft_library, font_file_path.c_str(), 0, &ft_face);
		assert(err == 0);
		err = FT_Set_Char_Size(
			ft_face,
			0,				/* char_width in 1/64 of points  */
			16 * 64,		/* char_height in 1/64 of points */
			300,      /* horizontal device resolution  */
			300);    /* vertical device resolution    */
		assert(err == 0);


		FT_UInt char_idx{};
		FT_ULong charcode = FT_Get_First_Char(ft_face, &char_idx);
		err = FT_Load_Glyph(ft_face, char_idx, FT_LOAD_DEFAULT);
		assert(err == 0);
		err = FT_Render_Glyph(ft_face->glyph, FT_RENDER_MODE_NORMAL);
		assert(err == 0);
		FT_Bitmap ft_bitmap = ft_face->glyph->bitmap;
		faces[charcode] = GlFontFace{ ft_bitmap };

		while ((charcode = FT_Get_Next_Char(ft_face, charcode, &char_idx)) != 0) {
			err = FT_Load_Glyph(ft_face, char_idx, FT_LOAD_DEFAULT);
			assert(err == 0);
			err = FT_Render_Glyph(ft_face->glyph, FT_RENDER_MODE_NORMAL);
			assert(err == 0);
			FT_Bitmap ft_bitmap = ft_face->glyph->bitmap;
			faces[charcode] = GlFontFace{ ft_bitmap };
		}

		FT_Done_Face(ft_face);
	}
};