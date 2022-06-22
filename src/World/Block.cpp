#include "Block.h"

namespace MinecraftClone
{
	Block::Block()
	{
		solid = false;
	}

	Block::Block(const glm::vec3& position, const glm::vec2 atlasCoord)
		: position(position), atlas_coords(atlasCoord)
	{
		solid = true;
	}
}
