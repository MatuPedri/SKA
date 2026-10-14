#pragma once
#include "../common.hpp"
#include "shader.hpp"

namespace ska {
	class ShaderProgram {
		public:
			ShaderProgram();
			~ShaderProgram();
			ShaderProgram(const ShaderProgram&) = delete;
			ShaderProgram& operator=(const ShaderProgram&) = delete;
			void attachShader(Shader* shader);
			bool link();
			void use() const;
			u32 getId() const { return id_; }
		protected:
			u32 id_ = 0;
	};
}