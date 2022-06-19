#pragma once

#include "Shader.h"
#include "Window.h"
#include "Cube.h"
#include "Camera.h"

namespace MinecraftClone
{
	class Renderer
	{
	private:
		Camera* camera;
		Shader shader;
		Window* window;
		uint32_t vao, vbo;

		int atlas_w, atlas_h, sprite_size;
		uint32_t atlas_id;
		std::array<Vertex, 36> cube_vertices;

		glm::mat4 projection;

	public:
		Renderer(Window* window, Camera* camera);
		~Renderer();

		void DrawCube(const Cube& cube);

	private:
		void LoadAtlas(const std::string& path, int& width, int& height);
	};
}