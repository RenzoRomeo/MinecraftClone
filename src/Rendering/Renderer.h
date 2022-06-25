#pragma once

#include "Shader.h"
#include "Window.h"
#include "../World/Block.h"
#include "../World/Chunk.h"
#include "../World/Player.h"

namespace MinecraftClone
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void RenderChunk(Window* window, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, uint32_t vao, uint32_t vertex_count);

	private:
		Shader m_shader;

		int m_atlas_w, m_atlas_h, m_sprite_size;
		uint32_t m_atlas_id;

	private:
		void LoadAtlas(const std::string& path, int& width, int& height);
	};
}