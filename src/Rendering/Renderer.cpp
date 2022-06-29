#include "Renderer.h"

#include "../World/World.h"

namespace MinecraftClone
{
	std::array<glm::vec3, 8> Renderer::vertices = {
			glm::vec3{-0.5f, 0.5f, 0.5f},
			glm::vec3{0.5f, 0.5f, 0.5f},
			glm::vec3{-0.5f, -0.5f, 0.5f},
			glm::vec3{0.5f, -0.5f, 0.5f},

			glm::vec3{-0.5f, 0.5f, -0.5f},
			glm::vec3{0.5f, 0.5f, -0.5f},
			glm::vec3{-0.5f, -0.5f, -0.5f},
			glm::vec3{0.5f, -0.5f, -0.5f}
	};

	std::array<uint32_t, 36> Renderer::cubeElements = {
			1, 0, 2,    3, 1, 2,    // Front face
			5, 1, 3,    7, 5, 3,    // Right face
			7, 6, 4,    5, 7, 4,    // Back face
			0, 4, 6,    2, 0, 6,    // Left face
			5, 4, 0,    1, 5, 0,    // Top face
			3, 2, 6,    7, 3, 6     // Bottom face
	};

	std::array<glm::vec2, 6> Renderer::texCoords = {
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),

			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),
	};

	Renderer::Renderer()
	{
		m_shader = Shader("res/shaders/cubeVertex.shader", "res/shaders/cubeFragment.shader");
		m_sprite_size = 16;
		LoadAtlas("res/images/blocks.png", m_atlas_w, m_atlas_h);

		glCreateVertexArrays(1, &vao);
		glCreateBuffers(1, &vbo);
	}

	Renderer::~Renderer()
	{
		glDeleteTextures(1, &m_atlas_id);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

	void Renderer::RenderChunk(Window* window, const Chunk& chunk, const Player& player)
	{
		std::vector<Vertex> cube_vertices;

		for (int z = 0; z < Chunk::GetSize(); z++)
		{
			for (int y = 0; y < Chunk::GetSize(); y++)
			{
				for (int x = 0; x < Chunk::GetSize(); x++)
				{
					glm::vec3 internal_position = (float)x * World::GetVx() + (float)y * World::GetVy() + (float)z * World::GetVz();

					World* world = World::GetInstance();

					const Block& block = chunk.GetBlock(x, y, z);

					if (!block.Solid)
						continue;

					if (!chunk.HasSolidNeighbor(x, y, z, Sides::Front) && !world->IsNeighborSolidBlock(chunk.GetPosition(), { x,y,z }, Sides::Front))
						for (int i = 0; i < 6; i++)
						{
							cube_vertices.push_back({ internal_position + vertices[cubeElements[i]], texCoords[i % 6], block.FrontAtlasCoord });
						}

					if (!chunk.HasSolidNeighbor(x, y, z, Sides::Back) && !world->IsNeighborSolidBlock(chunk.GetPosition(), { x,y,z }, Sides::Back))
						for (int i = 2 * 6; i < (2 + 1) * 6; i++)
						{
							cube_vertices.push_back({ internal_position + vertices[cubeElements[i]], texCoords[i % 6], block.BackAtlasCoord });
						}

					if (!chunk.HasSolidNeighbor(x, y, z, Sides::Bottom) && !world->IsNeighborSolidBlock(chunk.GetPosition(), { x,y,z }, Sides::Bottom))
						for (int i = 5 * 6; i < (5 + 1) * 6; i++)
						{
							cube_vertices.push_back({ internal_position + vertices[cubeElements[i]], texCoords[i % 6], block.BottomAtlasCoord });
						}

					if (!chunk.HasSolidNeighbor(x, y, z, Sides::Top) && !world->IsNeighborSolidBlock(chunk.GetPosition(), { x,y,z }, Sides::Top))
						for (int i = 4 * 6; i < (4 + 1) * 6; i++)
						{
							cube_vertices.push_back({ internal_position + vertices[cubeElements[i]], texCoords[i % 6], block.TopAtlasCoord });
						}

					if (!chunk.HasSolidNeighbor(x, y, z, Sides::Left) && !world->IsNeighborSolidBlock(chunk.GetPosition(), { x,y,z }, Sides::Left))
						for (int i = 3 * 6; i < (3 + 1) * 6; i++)
						{
							cube_vertices.push_back({ internal_position + vertices[cubeElements[i]], texCoords[i % 6], block.LeftAtlasCoord });
						}

					if (!chunk.HasSolidNeighbor(x, y, z, Sides::Right) && !world->IsNeighborSolidBlock(chunk.GetPosition(), { x,y,z }, Sides::Right))
						for (int i = 1 * 6; i < (1 + 1) * 6; i++)
						{
							cube_vertices.push_back({ internal_position + vertices[cubeElements[i]], texCoords[i % 6], block.RightAtlasCoord });
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

		float fov = 90.0f;
		float zNear = 0.1f;
		float zFar = 10000.0f;
		glm::mat4 projection = glm::perspective(fov, window->GetAspectRatio(), zNear, zFar);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), chunk.GetPosition() * glm::vec3(Chunk::GetSize()));
		glm::mat4 view = player.GetView();

		m_shader.Use();
		m_shader.SetUniformMat4f("uModel", model);
		m_shader.SetUniformMat4f("uView", view);
		m_shader.SetUniformMat4f("uProjection", projection);

		int textureSlot = 0;
		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, m_atlas_id);
		m_shader.SetUniform1i("uTexture", textureSlot);

		m_shader.SetUniform1i("uAtlasW", m_atlas_w);
		m_shader.SetUniform1i("uAtlasH", m_atlas_h);
		m_shader.SetUniform1i("uAtlasSpriteSize", m_sprite_size);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)cube_vertices.size());
	}

	void Renderer::LoadAtlas(const std::string& path, int& width, int& height)
	{
		int numChannels;

		uint8_t* pixels = stbi_load(path.c_str(), &width, &height, &numChannels, 0);

		int bpp = numChannels;
		uint32_t textureFormat = GL_RGBA;
		uint32_t internalFormat = GL_RGBA32F;
		if (bpp == 3)
		{
			textureFormat = GL_RGB;
			internalFormat = GL_RGB32F;
		}
		else if (bpp != 4)
		{
			stbi_image_free(pixels);
			return;
		}

		glGenTextures(1, &m_atlas_id);
		glBindTexture(GL_TEXTURE_2D, m_atlas_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, textureFormat, GL_UNSIGNED_BYTE, pixels);

		stbi_image_free(pixels);
	}
}