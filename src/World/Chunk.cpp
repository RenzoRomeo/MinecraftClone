#include "Chunk.h"

#include "World.h"

namespace MinecraftClone
{
	Chunk::Chunk(const glm::vec3& position)
		: position(position)
	{
		blocks = std::make_unique<std::array<Block, CHUNK_SIZE* CHUNK_SIZE* CHUNK_SIZE>>();

		// Just a test
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				for (int k = 0; k < CHUNK_SIZE; k++)
				{
					int index = Chunk::Index(i, j, k);
					blocks->at(index).atlas_coords = { 0,0 };
					blocks->at(index).solid = true;
				}
			}
		}
	}

	int Chunk::Index(int x, int y, int z)
	{
		return y * (Chunk::GetSize() - 1) * (Chunk::GetSize() - 1) + z * (Chunk::GetSize() - 1) + x;
	}

	glm::vec3 Chunk::InternalPosition(int x, int y, int z)
	{
		return (float)x * World::GetVx() + (float)y * World::GetVy() + (float)z * World::GetVz();
	}

	bool Chunk::IsBlockInside(int x, int y, int z) const
	{
		return !(x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_SIZE || z < 0 || z >= CHUNK_SIZE);
	}

	bool Chunk::HasSolidNeighbor(int x, int y, int z, Sides side) const
	{
		if (side == Sides::Top)
			if (!IsBlockInside(x, y + 1, z))
				return false;
			else
				return GetBlock(x, y + 1, z).solid;

		if (side == Sides::Bottom)
			if (!IsBlockInside(x, y - 1, z))
				return false;
			else
				return GetBlock(x, y - 1, z).solid;

		if (side == Sides::Left)
			if (!IsBlockInside(x - 1, y, z))
				return false;
			else
				return GetBlock(x - 1, y, z).solid;

		if (side == Sides::Right)
			if (!IsBlockInside(x + 1, y, z))
				return false;
			else
				return GetBlock(x + 1, y, z).solid;

		if (side == Sides::Back)
			if (!IsBlockInside(x, y, z - 1))
				return false;
			else
				return GetBlock(x, y, z - 1).solid;

		if (side == Sides::Front)
			if (!IsBlockInside(x, y, z + 1))
				return false;
			else
				return GetBlock(x, y, z + 1).solid;

		return false;
	}

	const Block& Chunk::GetBlock(int x, int y, int z) const
	{
		int i = Index(x, y, z);
		return blocks->at(i);
	}

	void Chunk::SetEmpty()
	{
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				for (int k = 0; k < CHUNK_SIZE; k++)
				{
					int index = Chunk::Index(i, j, k);
					blocks->at(index).atlas_coords = { 0,0 };
					blocks->at(index).solid = false;
				}
			}
		}
	}
}
