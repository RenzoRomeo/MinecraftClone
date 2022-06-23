#pragma once

#include "Shader.h"
#include "Window.h"
#include "../World/Block.h"
#include "../World/Chunk.h"
#include "Camera.h"

namespace MinecraftClone
{
	class Renderer
	{
	private:
		Shader shader;

		int atlas_w, atlas_h, sprite_size;
		uint32_t atlas_id;

		glm::mat4 projection;

	public:
		Renderer();
		~Renderer();
		void RenderChunk(Window* window, Camera* camera, Chunk& chunk);

	private:
		void LoadAtlas(const std::string& path, int& width, int& height);
	};
}