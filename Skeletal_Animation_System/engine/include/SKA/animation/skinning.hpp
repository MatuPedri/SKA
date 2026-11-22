#pragma once
#include "../common.hpp"
#include "../renderer/mesh.hpp"
#include "../renderer/vertex.hpp"

namespace ska
{
	class CpuSkinner {
		public:
			explicit CpuSkinner(const Mesh& mesh);
			void skin(const std::vector<glm::mat4>& skinMatrices, Mesh& mesh);
		private:
			std::vector<Vertex> bindPose_;
			std::vector<Vertex> skinned_;
	};
}