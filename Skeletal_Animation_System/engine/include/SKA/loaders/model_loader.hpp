#pragma once
#include "../common.hpp"
#include "../renderer/mesh.hpp"
#include "SKA/animation/skeleton.hpp"


namespace ska
{
	class Model {
		public:
			Model() = default;
			~Model() = default;
			Model(const Model&) = delete;
			Model& operator=(const Model&) = delete;
			const std::vector< std::unique_ptr<Mesh>>& getMeshes() const { return meshes_; }

			void loadModel(const std::string& path);
			void draw() const {
				for (const auto& mesh : meshes_) {
					mesh->draw();
				}
			}

			Skeleton& getSkeleton() { return skeleton_; }
		private:
			Skeleton skeleton_;
			std::vector<std::unique_ptr<Mesh>> meshes_;
	};
}