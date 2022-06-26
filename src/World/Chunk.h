#pragma once

#include "Block.h"
#include "../core.h"

namespace MinecraftClone
{
	enum class Sides
	{
		Left,
		Right,
		Front,
		Back,
		Top,
		Bottom
	};

	class Chunk
	{
	public:
		Chunk(const glm::vec3& position);

		glm::vec3 GetPosition() const { return position; }
		static int GetSize() { return CHUNK_SIZE; }
		static int GetBlockCount() { return BLOCK_COUNT; }

		bool HasSolidNeighbor(int x, int y, int z, Sides side) const;
		const Block& GetBlock(int x, int y, int z) const;
		void SetEmpty(); // Debugging

	private:
		static const int CHUNK_SIZE = 5;
		static const int BLOCK_COUNT = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

		glm::vec3 position;
		std::unique_ptr<std::array<Block, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE>> blocks;

	private:
		static int Index(int x, int y, int z);
		static glm::vec3 InternalPosition(int x, int y, int z);
		bool IsBlockInside(int x, int y, int z) const;
		void Update(float dt);
	};
}