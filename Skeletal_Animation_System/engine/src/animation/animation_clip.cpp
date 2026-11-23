#include "SKA/animation/animation_clip.hpp"
#include <cassert>
#include <algorithm>
#include <cmath>

static glm::vec3 sampleVec3(const std::vector<ska::KeyVec3>& keys, float time)
{
	if (keys.size() == 1 || time <= keys.front().time) return keys.front().value;
	if (time >= keys.back().time) return keys.back().value;

	size_t i = 0;
	while(time >= keys[i + 1].time) i++;

	float f = (time - keys[i].time) / (keys[i + 1].time - keys[i].time);

	return glm::mix(keys[i].value, keys[i + 1].value, f);
}

static glm::quat sampleQuat(const std::vector<ska::KeyQuat>& keys, float time)
{
	if (keys.size() == 1 || time <= keys.front().time) return keys.front().value;
	if (time >= keys.back().time) return keys.back().value;

	size_t i = 0;
	while(time >= keys[i + 1].time) i++;

	float f = (time - keys[i].time) / (keys[i + 1].time - keys[i].time);

	return glm::slerp(keys[i].value, keys[i + 1].value, f);
}

ska::AnimationClip::AnimationClip(std::string name, float duration, float ticksInSecond)
{
	name_ = std::move(name);
	duration_ = duration;
	ticksInSecond_ = ticksInSecond;
}

template<typename Key>
static bool validateKeys(const std::vector<Key>& keys)
{
	return !keys.empty() && std::is_sorted(keys.begin(), keys.end(), [](const Key& a, const Key& b) { return a.time < b.time; });
}

void ska::AnimationClip::addTrack(BoneTrack track)
{
	assert(track.boneIndex >= 0);
	assert(validateKeys(track.positionKeys));
	assert(validateKeys(track.rotationKeys));
	assert(validateKeys(track.scaleKeys));
	boneTracks_.push_back(std::move(track));
}

std::vector<glm::mat4> ska::AnimationClip::sample(const Skeleton& skeleton, float timePerSecond) const
{
	std::vector<glm::mat4> locals = skeleton.bindLocals();  // base en reposo

	float ticks = timePerSecond * ticksInSecond_;
	if(duration_ > 0.0f) {
		ticks = fmod(ticks, duration_);
	}

	for(const BoneTrack& track : boneTracks_) {
		glm::vec3 pos = sampleVec3(track.positionKeys, ticks);
		glm::quat rot = sampleQuat(track.rotationKeys, ticks);
		glm::vec3 scale = sampleVec3(track.scaleKeys, ticks);
		glm::mat4 localTransform = glm::translate(glm::mat4(1.0f), pos) * glm::mat4_cast(rot) * glm::scale(glm::mat4(1.0f), scale);
		locals[track.boneIndex] = localTransform;
	}

	return locals;
}
