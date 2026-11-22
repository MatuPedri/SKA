#pragma once
#include "../common.hpp"

namespace ska
{
	struct BoneInfo {
		std::string name;
		int parent = -1;
		glm::mat4 localBind;
		glm::mat4 inversedBind;
		bool isBone = false;
	};

	class Skeleton {
	public:
		int addBone(const std::string& name, int parent, const glm::mat4& localBind, const glm::mat4& inversedBind, bool isBone);
		void setMeshNode(int index) { meshnode_ = index; }
		size_t getBoneCount() const { return bones_.size(); }
		const BoneInfo& getBone(size_t i) const { return bones_[i]; }
		int findBone(const std::string& name) const;

		std::vector<glm::mat4> bindLocals() const;
		std::vector<glm::mat4> computeGlobals(const std::vector<glm::mat4>& locals) const;
		std::vector<glm::mat4> computeSkinMatrices(const std::vector<glm::mat4>& globals) const;
	private:
		std::vector<BoneInfo> bones_;
		std::unordered_map<std::string, int> boneMap_;
		int meshnode_ = -1;
	};
}
