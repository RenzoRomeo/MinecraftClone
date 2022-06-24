#include "Renderer.h"

namespace MinecraftClone
{
	Renderer::Renderer()
	{
		m_shader = Shader("res/shaders/cubeVertex.shader", "res/shaders/cubeFragment.shader");
		m_sprite_size = 16;
		LoadAtlas("res/images/blocks.png", m_atlas_w, m_atlas_h);
	}

	Renderer::~Renderer()
	{
		glDeleteTextures(1, &m_atlas_id);
	}

	void Renderer::RenderChunk(Window* window, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, uint32_t vao, uint32_t vertex_count)
	{

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