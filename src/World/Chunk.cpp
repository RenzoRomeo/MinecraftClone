#include "Chunk.h"

namespace MinecraftClone
{
	Chunk::Chunk()
	{
		blocks = new Block[CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT];

		// Just a test
		for (int i = 0; i < CHUNK_HEIGHT; i++)
		{
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				for (int k = 0; k < CHUNK_HEIGHT; k++)
				{
					int index = Chunk::index(i,j,k);
					blocks[index].position = glm::vec3(i, j, k);
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

	void Chunk::CreateMesh()
	{
		std::vector<Vertex> cube_vertices;

		std::array<glm::vec3, 8> vertices = {
		glm::vec3{-0.5f, 0.5f, 0.5f},
		glm::vec3{0.5f, 0.5f, 0.5f},
		glm::vec3{-0.5f, -0.5f, 0.5f},
		glm::vec3{0.5f, -0.5f, 0.5f},

		glm::vec3{-0.5f, 0.5f, -0.5f},
		glm::vec3{0.5f, 0.5f, -0.5f},
		glm::vec3{-0.5f, -0.5f, -0.5f},
		glm::vec3{0.5f, -0.5f, -0.5f}
		};

		std::array<uint32_t, 36> cubeElements = {
			1, 0, 2,    3, 1, 2,    // Front face
			5, 1, 3,    7, 5, 3,    // Right face
			7, 6, 4,    5, 7, 4,    // Back face
			0, 4, 6,    2, 0, 6,    // Left face
			5, 4, 0,    1, 5, 0,    // Top face
			3, 2, 6,    7, 3, 6     // Bottom face
		};

		std::array<glm::vec2, 6> texCoords = {
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),

			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),
		};

		for (int z = 0; z < CHUNK_HEIGHT; z++)
		{
			for (int x = 0; x < CHUNK_SIZE; x++)
			{
				for (int y = 0; y < CHUNK_SIZE; y++)
				{
					// For now, it only draws the hollow chunk
					int front = 0;
					int right = 1;
					int back = 2;
					int left = 3;
					int top = 4;
					int bottom = 5;

					// Left
					if (x == 0)
					{
						for (int i = left; i < left + 6; i++)
						{
							Vertex v;
							v.position = vertices[cubeElements[i]];
							v.tex_coords = texCoords[i % 6];
							cube_vertices.push_back(v);
						}
					}
					
					// Right
					if (x == CHUNK_SIZE - 1)
					{
						for (int i = right; i < right + 6; i++)
						{
							Vertex v;
							v.position = vertices[cubeElements[i]];
							v.tex_coords = texCoords[i % 6];
							cube_vertices.push_back(v);
						}
					}

					// Front
					if (y == 0)
					{
						for (int i = front; i < front + 6; i++)
						{
							Vertex v;
							v.position = vertices[cubeElements[i]];
							v.tex_coords = texCoords[i % 6];
							cube_vertices.push_back(v);
						}
					}
					
					// Back
					if (y == CHUNK_SIZE - 1)
					{
						for (int i = back; i < back + 6; i++)
						{
							Vertex v;
							v.position = vertices[cubeElements[i]];
							v.tex_coords = texCoords[i % 6];
							cube_vertices.push_back(v);
						}
					}
					
					// Top
					if (z == CHUNK_HEIGHT - 1)
					{
						for (int i = bottom; i < bottom + 6; i++)
						{
							Vertex v;
							v.position = vertices[cubeElements[i]];
							v.tex_coords = texCoords[i % 6];
							cube_vertices.push_back(v);
						}
					}
					
					// Bottom
					if (z == 0)
					{
						for (int i = top; i < top + 6; i++)
						{
							Vertex v;
							v.position = vertices[cubeElements[i]];
							v.tex_coords = texCoords[i % 6];
							cube_vertices.push_back(v);
						}
					}
				}
			}
		}

		glCreateVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glCreateBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* cube_vertices.size(), cube_vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, tex_coords));
		glEnableVertexAttribArray(1);

	}

	int Chunk::index(int x, int y, int z)
	{
		return z * CHUNK_SIZE * CHUNK_SIZE + x * CHUNK_SIZE + y;
	}
}
