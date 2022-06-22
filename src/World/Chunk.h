#pragma once

#include "Block.h"
#include "../core.h"

namespace MinecraftClone
{
	struct Chunk
	{
		static const int CHUNK_SIZE = 5;
		static const int BLOCK_COUNT = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
		static glm::vec3 vx, vy, vz;

		glm::vec3 position;
		uint32_t vao, vbo;
		Block* blocks;

		Chunk(const glm::vec3& position);
		~Chunk();

		int CreateMesh();

		static glm::vec3 InternalPosition(int x, int y, int z);
		const Block& GetBlock(int x, int y, int z);
		void FreeBuffers();

	private:
		static std::array<glm::vec3, 8> vertices;
		static std::array<uint32_t, 36> cubeElements;
		static std::array<glm::vec2, 6> texCoords;

		static int Index(int x, int y, int z);
	};
}