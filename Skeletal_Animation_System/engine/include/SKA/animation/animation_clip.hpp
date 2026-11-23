#pragma once
#include "../common.hpp"
#include "skeleton.hpp"

namespace ska
{
	struct KeyVec3
	{
		float time;
		glm::vec3 value;
	};

	struct KeyQuat
	{
		float time;
		glm::quat value;
	};

	struct BoneTrack
	{
		int boneIndex = -1;
		std::vector<KeyVec3> positionKeys;
		std::vector<KeyQuat> rotationKeys;
		std::vector<KeyVec3> scaleKeys;
	};

	class AnimationClip
	{
		public:
			AnimationClip(std::string name, float duration, float ticksInSecond);

			void addTrack(BoneTrack track);
			std::vector<glm::mat4> sample(const Skeleton& skeleton, float timePerSecond) const;

			const std::string& getName() const { return name_; }
			float getDuration() const { return duration_; }
			float getTicksPerSecond() const { return ticksInSecond_; }
			float getDurationInSeconds() const { return duration_ / ticksInSecond_; }
			const std::vector<BoneTrack>& getTracks() const { return boneTracks_; }
		private:
			std::string name_;
			float duration_;
			float ticksInSecond_;
			std::vector<BoneTrack> boneTracks_;
	};
}