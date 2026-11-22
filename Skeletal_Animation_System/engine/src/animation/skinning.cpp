#include "SKA//animation/skinning.hpp"

ska::CpuSkinner::CpuSkinner(const Mesh& mesh)
{
	bindPose_ = mesh.getVertices();
	skinned_.resize(bindPose_.size());
}

void ska::CpuSkinner::skin(const std::vector<glm::mat4>& skinMatrices, Mesh& mesh)
{
	for(size_t i = 0; i < bindPose_.size(); ++i) {
		const Vertex& v = bindPose_[i];
		glm::mat4 M(0.0f);		// matriz de transformación ponderada
		for(int k = 0; k < 4; ++k) {
			if (v.boneWeights[k] > 0.0f) {
				M += skinMatrices[v.boneIds[k]] * v.boneWeights[k];
			}
		}
		skinned_[i] = v;	// copiamos el resto de atributos
		skinned_[i].position = glm::vec3(M * glm::vec4(v.position, 1.0f));
		skinned_[i].normal = glm::normalize(glm::mat3(M) * v.normal);
	}
	mesh.updateVertices(skinned_);
}
