#include "World.h"

namespace MinecraftClone
{
	World::World(Window* window)
		: camera(Camera({ 0,0,0 }, { 0,1,0 })), renderer(Renderer(window, &camera))
	{
		chunks.push_back(new Chunk({ 0,1,0 }));
		chunks.push_back(new Chunk({ 0,0,0 }));
	}

	World::~World()
	{
		for (auto& chunk : chunks)
		{
			delete chunk;
		}
	}

	void World::Frame(float dt)
	{
		shader.Use();

		camera.SetDt(dt);
		UserInput();

		for (const auto& chunk : chunks)
		{
			renderer.RenderChunk(*chunk);
		}
	}

	void World::UserInput()
	{
		camera.ProcessMouse(Input::x_offset, Input::y_offset);
		Input::ResetMouseOffsets();

		if (Input::IsKeyDown(GLFW_KEY_W))
			camera.ProcessKeyboard(CameraMovement::Forward);
		if (Input::IsKeyDown(GLFW_KEY_S))
			camera.ProcessKeyboard(CameraMovement::Backward);
		if (Input::IsKeyDown(GLFW_KEY_A))
			camera.ProcessKeyboard(CameraMovement::Left);
		if (Input::IsKeyDown(GLFW_KEY_D))
			camera.ProcessKeyboard(CameraMovement::Right);
	}
}
