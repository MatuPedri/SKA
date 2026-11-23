#include "SKA/loaders/model_loader.hpp"
#include "SKA/renderer/vertex.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

static void validateWeights(const std::vector<ska::Vertex>& vertices)
{
	int noBones = 0, badSum = 0, maxInfl = 0;
	for (const ska::Vertex& v : vertices)
	{
		float sum = v.boneWeights.x + v.boneWeights.y + v.boneWeights.z + v.boneWeights.w;
		int n = 0;
		for (int k = 0; k < 4; ++k)
			if (v.boneWeights[k] > 0.0f) ++n;

		if (n == 0) ++noBones;
		else if (std::abs(sum - 1.0f) > 0.01f) ++badSum;
		maxInfl = std::max(maxInfl, n);
	}
	printf("Vertices: %zu | sin huesos: %d | suma != 1: %d | max influencias: %d\n",
		vertices.size(), noBones, badSum, maxInfl);
}

static ska::AnimationClip loadAnimation(const aiAnimation* anim, const ska::Skeleton& skeleton)
{
	ska::AnimationClip clip(anim->mName.C_Str(), static_cast<float>(anim->mDuration), anim->mTicksPerSecond > 0.0 ? static_cast<float>(anim->mTicksPerSecond) : 25.0f);

	for (unsigned int c = 0; c < anim->mNumChannels; ++c)
	{
		const aiNodeAnim* channel = anim->mChannels[c];
		int boneIndex = skeleton.findBone(channel->mNodeName.C_Str());
		if (boneIndex < 0) continue;

		ska::BoneTrack track;
		track.boneIndex = boneIndex;

		for (unsigned int p = 0; p < channel->mNumPositionKeys; ++p)
		{
			const aiVectorKey& pk = channel->mPositionKeys[p];
			ska::KeyVec3 key;
			key.time = static_cast<float>(pk.mTime);
			key.value = glm::vec3(pk.mValue.x, pk.mValue.y, pk.mValue.z);
			track.positionKeys.push_back(key);
		}

		for (unsigned int r = 0; r < channel->mNumRotationKeys; ++r)
		{
			const aiQuatKey& rk = channel->mRotationKeys[r];
			ska::KeyQuat key;
			key.time = static_cast<float>(rk.mTime);
			key.value = glm::quat(rk.mValue.w, rk.mValue.x, rk.mValue.y, rk.mValue.z);
			track.rotationKeys.push_back(key);
		}

		for (unsigned int s = 0; s < channel->mNumScalingKeys; ++s)
		{
			const aiVectorKey& sk = channel->mScalingKeys[s];
			ska::KeyVec3 key;
			key.time = static_cast<float>(sk.mTime);
			key.value = glm::vec3(sk.mValue.x, sk.mValue.y, sk.mValue.z);
			track.scaleKeys.push_back(key);
		}

		clip.addTrack(std::move(track));
	}
	return clip;
}

static void addInfluence(ska::Vertex& v, int boneId, float weight) {
	for (int k = 0; k < 4; k++) {
		if (v.boneWeights[k] == 0.0f) {
			v.boneIds[k] = boneId;
			v.boneWeights[k] = weight;
			return;
		}
	}
}

static std::unique_ptr<ska::Mesh> processMesh(const aiMesh* mesh, const ska::Skeleton& skeleton)
{
	std::vector<ska::Vertex> vertices;
	std::vector<u32> indices;
	vertices.reserve(mesh->mNumVertices);
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		ska::Vertex vertex;
		vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		if (mesh->HasNormals()) {
			vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		}
		vertices.push_back(vertex);
	}

	for (unsigned int b = 0; b < mesh->mNumBones; ++b)
	{
		const aiBone* bone = mesh->mBones[b];
		int boneId = skeleton.findBone(bone->mName.C_Str());
		if(boneId < 0) continue;   // hueso desconocido ignoramos 
		for (unsigned int w = 0; w < bone->mNumWeights; ++w)
		{
			const aiVertexWeight& vw = bone->mWeights[w];
			addInfluence(vertices[vw.mVertexId], boneId, vw.mWeight);
		}
	}

	indices.reserve(mesh->mNumFaces * 3);
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		const aiFace& face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}
	//validateWeights(vertices);
	return std::make_unique<ska::Mesh>(vertices, indices);
}

static void printNode(const aiNode* node, unsigned int level)
{
	printf("%*s%s\n", static_cast<int>(level * 2), "", node->mName.C_Str());
	for (unsigned int i = 0; i < node->mNumChildren; ++i)
		printNode(node->mChildren[i], level + 1);
}

static void modelInfo(const aiScene* scene)
{
	printf("Meshes: %u | Animations: %u\n", scene->mNumMeshes, scene->mNumAnimations);

	for (unsigned int m = 0; m < scene->mNumMeshes; ++m)
	{
		const aiMesh* mesh = scene->mMeshes[m];

		printf("Mesh %u: %u vertices, %u bones\n", m, mesh->mNumVertices, mesh->mNumBones);

		for (unsigned int b = 0; b < mesh->mNumBones; ++b)
		{
			const aiBone* bone = mesh->mBones[b];
			printf("  Bone %u: %s (%u weights)\n", b, bone->mName.C_Str(), bone->mNumWeights);

			for (unsigned int w = 0; w < bone->mNumWeights && w < 3; ++w)
				printf("    vertex %u -> %f\n", bone->mWeights[w].mVertexId, bone->mWeights[w].mWeight);
		}
	}

	printNode(scene->mRootNode, 0);

	for (unsigned int a = 0; a < scene->mNumAnimations; ++a)
	{
		const aiAnimation* anim = scene->mAnimations[a];
		printf("Animation %u: %.2f ticks, %.2f ticks/s, %u channels\n",
			a, anim->mDuration, anim->mTicksPerSecond, anim->mNumChannels);
	}
}

static glm::mat4 toGlm(const aiMatrix4x4& mat)
{
	return glm::transpose(glm::make_mat4(&mat.a1));
}

static void buildSkeleton(const aiNode* node, const aiScene* scene, ska::Skeleton& skeleton, int parentIndex = -1)
{
	const std::string name = node->mName.C_Str();
	const glm::mat4 localBind = toGlm(node->mTransformation);
	glm::mat4 inversedBind(1.0f);
	bool isBone = false;

	for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		const aiMesh* mesh = scene->mMeshes[i];
		for (unsigned int b = 0; b < mesh->mNumBones; ++b)
		{
			const aiBone* bone = mesh->mBones[b];
			if (bone->mName == node->mName)
			{
				isBone = true;
				inversedBind = toGlm(bone->mOffsetMatrix);
				break;
			}
		}
	}

	int currentIndex = skeleton.addBone(name, parentIndex, localBind, inversedBind, isBone);
	//printf("Index: %d | Bone: %s | Parent: %d | IsBone: %d\n", currentIndex, boneInfo.name.c_str(), boneInfo.parent, boneInfo.isBone);
	if(node->mNumMeshes > 0) {
		skeleton.setMeshNode(currentIndex);
	}
	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		buildSkeleton(node->mChildren[i], scene, skeleton, currentIndex);
	}
}

static void validateSkeleton(const ska::Skeleton& skeleton) {
	// matriz de skinning en reposo inverse(globalMesh) * global[i] * inversedBind[i] = I
	const auto global =	skeleton.computeGlobals(skeleton.bindLocals());
	const auto skin = skeleton.computeSkinMatrices(global); 
	
	for(size_t i = 0; i < skeleton.getBoneCount(); ++i) {
		const auto& b = skeleton.getBone(i);
		if (!b.isBone) continue;

		float err = 0.0f;
		for(int c = 0; c < 4; ++c) {
			for(int row = 0; row < 4; ++row) {
				float expected = (c == row) ? 1.0f : 0.0f;
				err = std::max(err, std::abs(skin[i][c][row] - expected));
			}
		}
		printf("Bone %zu: %s | Max error: %.6f\n", i, b.name.c_str(), err);
	}
}

void ska::Model::loadModel(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_LimitBoneWeights);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}

	//modelInfo(scene);
	
	buildSkeleton(scene->mRootNode, scene, skeleton_);
	for (unsigned int a = 0; a < scene->mNumAnimations; ++a){
		animations_.push_back(loadAnimation(scene->mAnimations[a], skeleton_));
	}
	//validateSkeleton(skeleton_);

	meshes_.reserve(scene->mNumMeshes);
	for(int i = 0; i < scene->mNumMeshes; ++i)
	{
		const aiMesh* ai_mesh = scene->mMeshes[i];
		meshes_.push_back(processMesh(ai_mesh, skeleton_));
	}
}