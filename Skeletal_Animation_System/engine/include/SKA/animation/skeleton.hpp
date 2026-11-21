#pragma once
#include "../common.hpp"

namespace ska
{
	struct BoneInfo {
		std::string name;
		int parent = -1;
		glm::mat4 localBind;
		glm::mat4 inversedBind;
		bool isBone;
	};

	struct Skeleton {
		std::vector<BoneInfo> bones;
		std::unordered_map<std::string, int> boneMap;
	};
}
