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
			cubeVertices[vertexIndex].position = vertices[cubeElements[vertexIndex]];
			cubeVertices[vertexIndex].texCoord = texCoords[vertexIndex % 6];
		}

		float windowAspect = ((float)window->window_width / (float)window->window_height);
		float fov = 90.0f;
		float zNear = 0.1f;
		float zFar = 10000.0f;
		projection = glm::perspective(fov, windowAspect, zNear, zFar);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * cubeVertices.size(), cubeVertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texCoord));
		glEnableVertexAttribArray(1);

		loadAtlas("res/images/blocks.png", atlasW, atlasH);
		spriteSize = 16;
	}

	Renderer::~Renderer()
	{
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
		glDeleteTextures(1, &atlasID);
	}

	void Renderer::drawCube(const Cube& cube)
	{
		shader.use();
		shader.setUniformMat4f("uView", camera->GetView());
		shader.setUniformMat4f("uProjection", projection);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), cube.position);
		shader.setUniformMat4f("uModel", model);

		int textureSlot = 0;

		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, atlasID);
		shader.setUniform1i("uTexture", textureSlot);

		shader.setUniform1i("uAtlasW", atlasW);
		shader.setUniform1i("uAtlasH", atlasH);
		shader.setUniform1i("uAtlasSpriteSize", spriteSize);

		shader.setUniformVec2f("uAtlasCoord", cube.atlasCoord);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)cubeVertices.size());
	}

	void Renderer::loadAtlas(const std::string& path, int& width, int& height)
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
		
		glGenTextures(1, &atlasID);
		glBindTexture(GL_TEXTURE_2D, atlasID);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, textureFormat, GL_UNSIGNED_BYTE, pixels);
		
		stbi_image_free(pixels);
	}
}