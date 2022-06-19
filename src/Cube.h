#pragma once

#include "core.h"
#include "Shader.h"

namespace MinecraftClone
{
	struct Vertex {
		glm::vec3 position;
		glm::vec2 texCoord;
	};

	struct Texture
	{
		std::string filepath;
		uint32_t textureId;
		int32_t width;
		int32_t height;
		int32_t numChannels;
	};

	struct Cube
	{
		uint32_t textureID;
		glm::vec3 position;

		Cube(const glm::vec3& position, uint32_t textureID);
	};
}