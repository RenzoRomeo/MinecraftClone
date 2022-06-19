#include "Renderer.h"

namespace MinecraftClone
{
	Renderer::Renderer(Window* window, Camera* camera)
		: window(window), camera(camera)
	{
		shader = Shader("res/shaders/cubeVertex.shader", "res/shaders/cubeFragment.shader");

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

			glm::vec2(1.0f, 1.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f, 0.0f),
		};

		for (int vertexIndex = 0; vertexIndex < cubeElements.size(); vertexIndex++)
		{
			cube_vertices[vertexIndex].position = vertices[cubeElements[vertexIndex]];
			cube_vertices[vertexIndex].tex_coords = texCoords[vertexIndex % 6];
		}

		float windowAspect = ((float)window->window_width / (float)window->window_height);
		float fov = 90.0f;
		float zNear = 0.1f;
		float zFar = 10000.0f;
		projection = glm::perspective(fov, windowAspect, zNear, zFar);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * cube_vertices.size(), cube_vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, tex_coords));
		glEnableVertexAttribArray(1);

		LoadAtlas("res/images/blocks.png", atlas_w, atlas_h);
		sprite_size = 16;
	}

	Renderer::~Renderer()
	{
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
		glDeleteTextures(1, &atlas_id);
	}

	void Renderer::DrawCube(const Cube& cube)
	{
		shader.use();
		shader.SetUniformMat4f("uView", camera->GetView());
		shader.SetUniformMat4f("uProjection", projection);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), cube.position);
		shader.SetUniformMat4f("uModel", model);

		int textureSlot = 0;

		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, atlas_id);
		shader.SetUniform1i("uTexture", textureSlot);

		shader.SetUniform1i("uAtlasW", atlas_w);
		shader.SetUniform1i("uAtlasH", atlas_h);
		shader.SetUniform1i("uAtlasSpriteSize", sprite_size);

		shader.SetUniformVec2f("uAtlasCoord", cube.atlas_coords);

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