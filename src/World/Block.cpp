#include "Block.h"

namespace MinecraftClone
{
	Block::Block()
	{
		solid = false;
	}

	Block::Block(const glm::vec2 atlasCoord)
		: atlas_coords(atlasCoord)
	{
		solid = true;
	}
}
