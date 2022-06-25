#include "Chunk.h"

#include "World.h"

namespace MinecraftClone
{
	std::array<glm::vec3, 8> Chunk::vertices = {
			glm::vec3{-0.5f, 0.5f, 0.5f},
			glm::vec3{0.5f, 0.5f, 0.5f},
			glm::vec3{-0.5f, -0.5f, 0.5f},
			glm::vec3{0.5f, -0.5f, 0.5f},

			glm::vec3{-0.5f, 0.5f, -0.5f},
			glm::vec3{0.5f, 0.5f, -0.5f},
			glm::vec3{-0.5f, -0.5f, -0.5f},
			glm::vec3{0.5f, -0.5f, -0.5f}
	};

	std::array<uint32_t, 36> Chunk::cubeElements = {
			1, 0, 2,    3, 1, 2,    // Front face
			5, 1, 3,    7, 5, 3,    // Right face
			7, 6, 4,    5, 7, 4,    // Back face
			0, 4, 6,    2, 0, 6,    // Left face
			5, 4, 0,    1, 5, 0,    // Top face
			3, 2, 6,    7, 3, 6     // Bottom face
	};

	std::array<glm::vec2, 6> Chunk::texCoords = {
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),

			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),
	};


	Chunk::Chunk(const glm::vec3& position)
		: position(position)
	{
		blocks = new Block[BLOCK_COUNT];

		glCreateVertexArrays(1, &vao);
		glCreateBuffers(1, &vbo);

		// Just a test
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				for (int k = 0; k < CHUNK_SIZE; k++)
				{
					int index = Chunk::Index(i, j, k);
					blocks[index].atlas_coords = { 0, 0 };
				}
			}
		}
	}

	Chunk::~Chunk()
	{
		delete[] blocks;
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}

	int Chunk::CreateMesh()
	{
		std::vector<Vertex> cube_vertices;

		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			for (int y = 0; y < CHUNK_SIZE; y++)
			{
				for (int x = 0; x < CHUNK_SIZE; x++)
				{
					glm::vec3 internal_position = (float)x * World::GetVx() + (float)y * World::GetVy() + (float)z * World::GetVz();

					bool front = z == CHUNK_SIZE - 1;
					bool back = z == 0;
					bool bottom = y == CHUNK_SIZE - 1;
					bool top = y == 0;
					bool left = x == 0;
					bool right = x == CHUNK_SIZE - 1;

					World* world = World::GetInstance();

					if (front && !world->ChunkHasNeighbor(position, Sides::Front))
						for (int i = 0; i < 6; i++)
						{
							cube_vertices.push_back({ internal_position + vertices[cubeElements[i]], texCoords[i % 6], {0,0} });
						}
					
					if (back && !world->ChunkHasNeighbor(position, Sides::Back))
						for (int i = 2 * 6; i < (2 + 1) * 6; i++)
						{
							cube_vertices.push_back({ internal_position + vertices[cubeElements[i]], texCoords[i % 6], {0,0} });
						}
					
					if (top && !world->ChunkHasNeighbor(position, Sides::Top))
						for (int i = 5 * 6; i < (5 + 1) * 6; i++)
						{
							cube_vertices.push_back({ internal_position + vertices[cubeElements[i]], texCoords[i % 6], {0,0} });
						}
					
					if (bottom && !world->ChunkHasNeighbor(position, Sides::Bottom))
						for (int i = 4 * 6; i < (4 + 1) * 6; i++)
						{
							cube_vertices.push_back({ internal_position + vertices[cubeElements[i]], texCoords[i % 6], {1,0} });
						}
					
					if (left && !world->ChunkHasNeighbor(position, Sides::Left))
						for (int i = 3 * 6; i < (3 + 1) * 6; i++)
						{
							cube_vertices.push_back({ internal_position + vertices[cubeElements[i]], texCoords[i % 6], {0,0} });
						}
					
					if (right && !world->ChunkHasNeighbor(position, Sides::Right))
						for (int i = 1 * 6; i < (1 + 1) * 6; i++)
						{
							cube_vertices.push_back({ internal_position + vertices[cubeElements[i]], texCoords[i % 6], {0,0} });
						}
				}
			}
		}

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * cube_vertices.size(), cube_vertices.data(), GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, tex_coords));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, atlas_coords));
		glEnableVertexAttribArray(2);

		return cube_vertices.size();
	}

	int Chunk::Index(int x, int y, int z)
	{
		return z * Chunk::GetSize() * Chunk::GetSize() + x * Chunk::GetSize() + y;
	}

	glm::vec3 Chunk::InternalPosition(int x, int y, int z)
	{
		return (float)x * World::GetVx() + (float)y * World::GetVy() + (float)z * World::GetVz();
	}

	const Block& Chunk::GetBlock(int x, int y, int z)
	{
		int i = Index(x, y, z);
		return blocks[i];
	}
}
