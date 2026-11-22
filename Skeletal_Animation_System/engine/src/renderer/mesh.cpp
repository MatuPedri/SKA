#include <glad/glad.h>
#include "SKA/renderer/mesh.hpp"
#include <cstddef>

ska::Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indices)
{
	indexCount_ = static_cast<u32>(indices.size());
	indices_ = indices;
	vertices_ = vertices;

	glGenVertexArrays(1, &VAO_);
	glGenBuffers(1, &VBO_);
	glGenBuffers(1, &EBO_);

	glBindVertexArray(VAO_);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glVertexAttribIPointer(2, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, boneIds));
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, boneWeights));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
}

ska::Mesh::~Mesh()
{
	glDeleteBuffers(1, &VBO_);
	glDeleteBuffers(1, &EBO_);
	glDeleteVertexArrays(1, &VAO_);
}

void ska::Mesh::draw() const
{
	glBindVertexArray(VAO_);
	glDrawElements(GL_TRIANGLES, indexCount_, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void ska::Mesh::updateVertices(const std::vector<Vertex>& vertices)
{
	if(vertices.size() != vertices_.size())
	{
		return;
	}
	vertices_ = vertices;
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
}
