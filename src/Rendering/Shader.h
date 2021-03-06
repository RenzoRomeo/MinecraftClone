#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader();
	Shader(const std::string& vertexPath, const std::string& fragmentPath);

	void Use();

	void SetUniform1b(const std::string& name, bool value) const;
	void SetUniform1i(const std::string& name, int value) const;
	void SetUniform1f(const std::string& name, float value) const;
	void SetUniformVec2f(const std::string& name, const glm::vec2 vec) const;
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix) const;

	void Free();

	uint32_t GetId() const { return id; }

private:
	uint32_t id;

private:
	void CheckCompileErrors(unsigned int shader, const std::string& type);
};