#include "World.h"

namespace MinecraftClone
{
	World::World(Window* window)
		: camera(Camera({ 0,0,0 }, { 0,1,0 })), renderer(Renderer(window, &camera))
	{
		chunks.push_back(new Chunk({ 0,0,0 }));
	}

	World::~World()
	{
		for (Chunk* chunk : chunks)
		{
			delete chunk;
		}
	}

	void World::Frame(float dt)
	{
		shader.Use();

		camera.SetDt(dt);
		UserInput();

		//GenerateChunksAroundPlayer();

		for (int i = 0; i < chunks.size(); i++)
		{
			Chunk* chunk = chunks.at(i);
			renderer.RenderChunk(*chunk);
			if (chunk->DistanceToPlayer(camera.position) >= 15.0f)
			{
				std::cout << "Deleted chunk - Distance: " << chunks.at(0)->DistanceToPlayer(camera.position) << '\n';
				chunks.erase(chunks.begin() + i);
			}
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

	//void World::GenerateChunksAroundPlayer()
	//{
	//	float render_distance = 15.0f;
	//
	//	for (int x = -render_distance; x < render_distance; x++)
	//	{
	//		for (int z = -render_distance; z < render_distance; z++)
	//		{
	//			chunks.push_back(new Chunk({ x,0,z }));
	//		}
	//	}
	//}
}
