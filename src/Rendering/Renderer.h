#pragma once

#include "Shader.h"
#include "Window.h"
#include "../World/Chunk.h"
#include "../World/Player.h"

namespace MinecraftClone
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void RenderChunk(Window* window, const Chunk& chunk, const Player& player);

	private:
		Shader m_shader;

		int m_atlas_w, m_atlas_h, m_sprite_size;
		uint32_t m_atlas_id;
		uint32_t vao, vbo;

		static std::array<glm::vec3, 8> vertices;
		static std::array<uint32_t, 36> cubeElements;
		static std::array<glm::vec2, 6> texCoords;

	private:
		void LoadAtlas(const std::string& path, int& width, int& height);
	};
}