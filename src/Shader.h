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
	unsigned int ID;

public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void use();

	void setUniform1b(const std::string& name, bool value) const;
	void setUniform1i(const std::string& name, int value) const;
	void setUniform1f(const std::string& name, float value) const;
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix) const;

private:
	void checkCompileErrors(unsigned int shader, const std::string& type);
};