#pragma once

#include <exception>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace GLRenderer {
	struct FTLibraryRAII {
		FT_Library ft_library_raw{};
		FTLibraryRAII() {
			FT_Error err = FT_Init_FreeType(&ft_library_raw);
			if (err != 0) {
				throw std::runtime_error{ "free type library not correctly initialzed" };
			}
		}

		FTLibraryRAII(const FTLibraryRAII& rhs) = delete;
		FTLibraryRAII& operator=(const FTLibraryRAII& rhs) = delete;

		~FTLibraryRAII()
		{
			FT_Done_FreeType(ft_library_raw);
		}
	};
}