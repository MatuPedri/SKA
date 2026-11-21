#include <SKA/renderer/shader_program.hpp>
#include <glad/glad.h>

ska::ShaderProgram::ShaderProgram()
{
	id_ = glCreateProgram();
}

ska::ShaderProgram::~ShaderProgram()
{
	if (glIsProgram(id_))
	{
		glDeleteProgram(id_);
	}
}

void ska::ShaderProgram::attachShader(Shader* shader)
{
	if(shader)
	{
		glAttachShader(id_, shader->getId());
	}
}

bool ska::ShaderProgram::link()
{
	glLinkProgram(id_);
	GLint program_linked = 0;
	GLsizei log_length = 0;

	glGetProgramiv(id_, GL_LINK_STATUS, &program_linked);
	glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &log_length);

	if(program_linked != GL_TRUE) {
		std::string errorLog(static_cast<size_t>(log_length) + 1, '\0');
		GLsizei ll = 0;
		glGetProgramInfoLog(id_, log_length, &ll, errorLog.data());
		errorLog.resize(static_cast<size_t>(ll));
		return false;
	}

	return true;
}

void ska::ShaderProgram::use() const
{
	glUseProgram(id_);
}

void ska::ShaderProgram::setMat4(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
