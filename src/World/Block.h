#pragma once

#include "../core.h"

namespace MinecraftClone
{
	struct Vertex {
		glm::vec3 position;
		glm::vec2 tex_coords;
		glm::vec2 atlas_coords;
	};

	struct Texture
	{
		std::string filepath;
		uint32_t texture_id;
		int32_t width;
		int32_t height;
		int32_t num_channels;
	};

	struct Block
	{
		glm::vec2 atlas_coords = { 2,3 };
		bool solid;

		Block();
		Block(const glm::vec2 atlasCoord);
	};
}