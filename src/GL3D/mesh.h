#pragma once

#include <span>

namespace GL3D {
	class ShaderProgram;
	class Mesh {
	public:
		size_t indices_size{};
		unsigned int vao = 0;
		unsigned int vbo = 0;
		unsigned int ebo = 0;
		Mesh(std::span<float> vertices, std::span<int> num_floats_per_attr, std::span<unsigned int> indices);
		Mesh(const Mesh& rhs) = delete;
		Mesh& operator=(const Mesh& rhs) = delete;
		~Mesh();
		void draw(const ShaderProgram& shader) const;
	private:
		// WARNING: vertex data must be float only
		void set_vertex_attributes(unsigned int vao, unsigned int vbo, std::span<int> num_floats_per_attr);
	};
}