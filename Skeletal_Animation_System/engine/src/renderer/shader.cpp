#include <SKA/renderer/shader.hpp>
#include <glad/glad.h>
#include <stdexcept>   
#include <sstream>    

ska::Shader::Shader()
{
	is_compiled_ = false;
	type_ = Type::Invalid;
	id_ = 0;
}

ska::Shader::~Shader()
{
	glDeleteShader(id_);
}

void ska::Shader::loadSource(const Type shader_type, const char* source, const unsigned int source_size)
{
	type_ = shader_type;
	switch (shader_type)
	{
	case Type::Vertex:
		id_ = glCreateShader(GL_VERTEX_SHADER);
		break;
	case Type::Fragment:
		id_ = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case Type::Geometry:
		id_ = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	default:
		throw std::runtime_error("Invalid shader type");
	}
	GLint size = source_size;
	glShaderSource(id_, 1, &source, &size);
}

void ska::Shader::loadSourceFromFile(const Type shader_type, const char* path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		std::fprintf(stderr, "[Shader] could not open file: %s\n", path);
		throw std::runtime_error("Shader file not found");
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string source = buffer.str();

	loadSource(shader_type, source.c_str(), (u32)(source.size()));
}

bool ska::Shader::compile()
{
	glCompileShader(id_);
	GLint success = GL_FALSE;
	glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &maxLength);

		std::unique_ptr<char[]> errorLog = std::make_unique<char[]>(maxLength + 1);
		glGetShaderInfoLog(id_, maxLength, &maxLength, errorLog.get());
		errorLog[maxLength] = '\0';
		std::fprintf(stderr, "[GLShader] compile error:\n%s\n", errorLog.get());

		is_compiled_ = false;
		return false;
	}
	is_compiled_ = true;
	return true;
}