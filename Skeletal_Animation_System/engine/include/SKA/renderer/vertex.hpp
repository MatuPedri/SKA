#pragma once
#include "../common.hpp"

namespace ska
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::ivec4 boneIds{ 0 };
		glm::vec4 boneWeights{ 0.0f };
	};
}