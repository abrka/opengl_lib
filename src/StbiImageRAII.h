#pragma once
#include <filesystem>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

class StbiImage {
public:
	int width;
	int height;
	int num_channels;
	unsigned char* data;

	StbiImage(const std::filesystem::path path) {
		data = stbi_load(path.string().c_str(), &width, &height, &num_channels, 0);
		if (not data) {
			std::cout << "failed to load image data the path was " << path << std::endl;
			assert(false && "failed to load image data");
		}
	}
	~StbiImage() {
		stbi_image_free(data);
	}
	
};