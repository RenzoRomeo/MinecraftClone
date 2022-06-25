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
		~Chunk();

		int CreateMesh();

		glm::vec3 GetPosition() const { return position; }
		uint32_t GetVao() const { return vao; }
		static int GetSize() { return CHUNK_SIZE; }
		static int GetBlockCount() { return BLOCK_COUNT; }

	private:
		static std::array<glm::vec3, 8> vertices;
		static std::array<uint32_t, 36> cubeElements;
		static std::array<glm::vec2, 6> texCoords;

		static const int CHUNK_SIZE = 5;
		static const int BLOCK_COUNT = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

		glm::vec3 position;
		uint32_t vao, vbo;
		Block* blocks;

	private:
		static int Index(int x, int y, int z);
		static glm::vec3 InternalPosition(int x, int y, int z);
		const Block& GetBlock(int x, int y, int z);
		void Update(float dt);
	};
}