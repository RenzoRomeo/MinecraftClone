#pragma once

#include "core.h"
#include "Shader.h"

namespace MinecraftClone
{
	struct Vertex {
		glm::vec3 position;
		glm::vec2 tex_coords;
	};

	struct Texture
	{
		std::string filepath;
		uint32_t texture_id;
		int32_t width;
		int32_t height;
		int32_t num_channels;
	};

	struct Cube
	{
		glm::ivec2 atlas_coords = { 2,3 };
		glm::vec3 position;

		Cube(const glm::vec3& position, const glm::vec2 atlasCoord);
	};
}