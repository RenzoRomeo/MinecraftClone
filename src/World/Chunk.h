#pragma once

#include "Block.h"
#include "../core.h"

namespace MinecraftClone
{
	struct Chunk
	{
		static const int CHUNK_SIZE = 5;
		static const int CHUNK_HEIGHT = 5;
		static const int BLOCK_COUNT = CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT;

		uint32_t vao, vbo;

		Block* blocks;

		Chunk();
		~Chunk();

		void CreateMesh();

		static int index(int x, int y, int z);
	};
}