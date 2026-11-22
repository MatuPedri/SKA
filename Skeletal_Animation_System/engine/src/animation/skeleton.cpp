#include "SKA/animation/skeleton.hpp"

int ska::Skeleton::addBone(const std::string& name, int parent, const glm::mat4& localBind, const glm::mat4& inversedBind, bool isBone)
{
	const int index = static_cast<int>(bones_.size());
	assert(parent >= -1 && parent < index);

	BoneInfo b;
	b.name = name;
	b.parent = parent;
	b.localBind = localBind;
	b.inversedBind = inversedBind;
	b.isBone = isBone;

	bones_.push_back(b);
	boneMap_[name] = index;

	return index;
}

int ska::Skeleton::findBone(const std::string& name) const
{
	std::unordered_map<std::string, int>::const_iterator it = boneMap_.find(name);
	if (it != boneMap_.end()) {
		return it->second;
	}
	return -1;
}

std::vector<glm::mat4> ska::Skeleton::bindLocals() const
{
	std::vector<glm::mat4> locals(bones_.size());
	for(size_t i = 0; i < bones_.size(); i++){
		locals[i] = bones_[i].localBind;
	}

	return locals;
}

std::vector<glm::mat4> ska::Skeleton::computeGlobals(const std::vector<glm::mat4>& locals) const
{
	std::vector<glm::mat4> globals(bones_.size());
	for(size_t i = 0; i < bones_.size(); i++){
		const BoneInfo& b = bones_[i];
		globals[i] = (b.parent < 0) ? locals[i] : globals[b.parent] * locals[i];
	}	
	return globals;
}

std::vector<glm::mat4> ska::Skeleton::computeSkinMatrices(const std::vector<glm::mat4>& globals) const
{
	assert(meshnode_ >= 0 && meshnode_);
	const glm::mat4 meshInv = glm::inverse(globals[meshnode_]);
	std::vector<glm::mat4> skinMatrices(bones_.size(), glm::mat4(1.0f));
	for(size_t i = 0; i < bones_.size(); i++){
		if (bones_[i].isBone) {
			const BoneInfo& b = bones_[i];
			skinMatrices[i] = meshInv * globals[i] * b.inversedBind;
		}
	}
	return skinMatrices;
}
