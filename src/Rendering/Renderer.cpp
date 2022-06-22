#include "Renderer.h"

namespace MinecraftClone
{
	Renderer::Renderer(Window* window, Camera* camera)
		: window(window), camera(camera)
	{
		shader = Shader("res/shaders/cubeVertex.shader", "res/shaders/cubeFragment.shader");

		float windowAspect = ((float)window->window_width / (float)window->window_height);
		float fov = 90.0f;
		float zNear = 0.1f;
		float zFar = 10000.0f;
		projection = glm::perspective(fov, windowAspect, zNear, zFar);

		LoadAtlas("res/images/blocks.png", atlas_w, atlas_h);
		sprite_size = 16;
	}

	Renderer::~Renderer()
	{
		glDeleteTextures(1, &atlas_id);
	}

	void Renderer::RenderChunk(Chunk& chunk)
	{
		shader.use();
		shader.SetUniformMat4f("uView", camera->GetView());
		shader.SetUniformMat4f("uProjection", projection);

		int vertex_count = chunk.CreateMesh();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), chunk.position * glm::vec3(Chunk::CHUNK_SIZE));
		shader.SetUniformMat4f("uModel", model);

		int textureSlot = 0;

		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, atlas_id);
		shader.SetUniform1i("uTexture", textureSlot);

		shader.SetUniform1i("uAtlasW", atlas_w);
		shader.SetUniform1i("uAtlasH", atlas_h);
		shader.SetUniform1i("uAtlasSpriteSize", sprite_size);

		glBindVertexArray(chunk.vao);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertex_count);
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

		glGenTextures(1, &atlas_id);
		glBindTexture(GL_TEXTURE_2D, atlas_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, textureFormat, GL_UNSIGNED_BYTE, pixels);

		stbi_image_free(pixels);
	}
}