#pragma once
#include "../common.hpp"

namespace ska
{
	class Shader {
		public:
			enum class Type {
				Invalid = 0,
				Fragment,
				Vertex,
				Geometry
			};

			Shader();
			~Shader();
			Shader(const Shader&) = delete;
			Shader& operator=(const Shader&) = delete;

			void loadSource(const Type shader_type, const char* source, const unsigned int source_size);
			void loadSourceFromFile(const Type shader_type, const char* path);
			bool compile();
			bool is_compiled() const { return is_compiled_; }
			unsigned int getId() const { return id_; }
			Type getType() const { return type_; } 

		protected:
			unsigned int id_;
			Type type_;
			bool is_compiled_;
	};
}