#pragma once

#include <span>
#include <vector>
#include <memory>
#include <numeric>

#include <glad/glad.h>

#include "shader_program.h"

namespace GL3D {
	class Mesh {

	public:
		size_t indices_size{};

		unsigned int vao = 0;
		unsigned int vbo = 0;
		unsigned int ebo = 0;


		Mesh(std::span<float> vertices, std::span<int> num_floats_per_attr, std::span<unsigned int> indices)
		{

			indices_size = indices.size();

			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &ebo);

			glGenBuffers(1, &vbo);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);


			set_vertex_attributes(vao, vbo, num_floats_per_attr);
			glBindVertexArray(0);

		};

		Mesh(const Mesh& rhs) = delete;
		Mesh& operator=(const Mesh& rhs) = delete;

		~Mesh() {
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ebo);
		}

		void draw(const ShaderProgram& shader) const {


			shader.bind();
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			shader.unbind();
		};



	private:
		// WARNING: vertex data must be float only
		void set_vertex_attributes(unsigned int vao, unsigned int vbo, std::span<int> num_floats_per_attr) {
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			int stride = std::accumulate(num_floats_per_attr.begin(), num_floats_per_attr.end(), 0) * sizeof(float);
			int offset = 0;
			for (int i = 0; i < num_floats_per_attr.size(); i++)
			{
				glVertexAttribPointer(i, num_floats_per_attr[i], GL_FLOAT, GL_FALSE, stride, (void*)(offset));
				glEnableVertexAttribArray(i);
				offset += num_floats_per_attr[i] * sizeof(float);
			}
			glBindVertexArray(0);
		}

	};
}