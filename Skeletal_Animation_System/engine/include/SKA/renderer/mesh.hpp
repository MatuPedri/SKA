#pragma once
#include "../common.hpp"
#include "vertex.hpp"

namespace ska
{
	class Mesh
	{
		public:
			Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
			~Mesh();
			Mesh(const Mesh&) = delete;
			Mesh& operator=(const Mesh&) = delete;

			void draw() const;
			void updateVertices(const std::vector<Vertex>& vertices);
			const std::vector<Vertex>& getVertices() const { return vertices_; }
			const std::vector<u32>& getIndices() const { return indices_; }

		private:
			u32 VAO_ = 0;
			u32 VBO_ = 0;
			u32 EBO_ = 0;
			u32 indexCount_ = 0;

			std::vector<Vertex> vertices_;
			std::vector<u32> indices_;
	};
}