#include "Cubes.h"
#include "core.h"
#include "Input.h"
#include "Window.h"
#include "Shader.h"

#include "Camera.h"


namespace MinecraftClone
{
	namespace Cubes
	{
		struct Vertex
		{
			glm::vec3 position;
			glm::vec2 texCoords;
		};

		struct Texture
		{
			std::string filepath;
			uint32_t textureId;
			int32_t width;
			int32_t height;
			int32_t numChannels;
		};

		struct Cube
		{
			std::array<Vertex, 36> vertices;
			uint32_t VAO;
			uint32_t VBO;
		};

		static std::array<uint32_t, 36> cubeElements = {
			// Each set of 6 indices represents one quad
			1, 0, 2,    3, 1, 2,    // Front face
			5, 1, 3,    7, 5, 3,    // Right face
			7, 6, 4,    5, 7, 4,    // Back face
			0, 4, 6,    2, 0, 6,    // Left face
			5, 4, 0,    1, 5, 0,    // Top face
			3, 2, 6,    7, 3, 6     // Bottom face
		};

		static std::vector<std::string> textureFilepaths;
		static Cube defaultCube;
		static std::vector<Texture> textures;
		static Shader texturedCubeShader;
		static std::vector<glm::vec3> cubePositions;
		static std::vector<int> cubeTextures;

		static glm::mat4 projection;

		void createDefaultCube()
		{
			std::array<glm::vec3, 8> cubeVertices = {
				glm::vec3{-0.5f, 0.5f, 0.5f},
				glm::vec3{0.5f, 0.5f, 0.5f},
				glm::vec3{-0.5f, -0.5f, 0.5f},
				glm::vec3{0.5f, -0.5f, 0.5f},
			
				glm::vec3{-0.5f, 0.5f, -0.5f},
				glm::vec3{0.5f, 0.5f, -0.5f},
				glm::vec3{-0.5f, -0.5f, -0.5f},
				glm::vec3{0.5f, -0.5f, -0.5f}
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
				defaultCube.vertices[vertexIndex].position = cubeVertices[cubeElements[vertexIndex]];
				defaultCube.vertices[vertexIndex].texCoords = texCoords[vertexIndex % 6];
			}

			glGenVertexArrays(1, &defaultCube.VAO);
			glBindVertexArray(defaultCube.VAO);

			glGenBuffers(1, &defaultCube.VBO);
			glBindBuffer(GL_ARRAY_BUFFER, defaultCube.VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * defaultCube.vertices.size(), defaultCube.vertices.data(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texCoords));
			glEnableVertexAttribArray(1);
		}

		void drawCube(const glm::vec3& position, const Texture& texture)
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
			texturedCubeShader.setUniformMat4f("uModel", model);

			int textureSlot = 0;

			glActiveTexture(GL_TEXTURE0 + textureSlot);
			glBindTexture(GL_TEXTURE_2D, texture.textureId);
			texturedCubeShader.setUniform1i("uTexture", textureSlot);

			glBindVertexArray(defaultCube.VAO);
			glDrawArrays(GL_TRIANGLES, 0, (GLsizei)defaultCube.vertices.size());
		}

		void destroyDefaultCube()
		{
			
			glDeleteBuffers(1, &defaultCube.VBO);
			glDeleteVertexArrays(1, &defaultCube.VAO);
		}

		Texture createTexture(const std::string& filepath, bool pixelated = false)
		{
			Texture res;
			res.filepath = filepath;
			uint8_t *pixels = stbi_load(res.filepath.c_str(), &res.width, &res.height, &res.numChannels, 0);
			
			int bpp = res.numChannels;
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
				return Texture{};
			}

			glGenTextures(1, &res.textureId);
			glBindTexture(GL_TEXTURE_2D, res.textureId);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pixelated ? GL_NEAREST : GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, pixelated ? GL_NEAREST : GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, res.width, res.height, 0, textureFormat, GL_UNSIGNED_BYTE, pixels);

			stbi_image_free(pixels);

			return res;
		}

		void destroyTexture(Texture& texture)
		{
			glDeleteTextures(1, &texture.textureId);
		}

		void init(const Window& window)
		{
			texturedCubeShader = Shader("res/shaders/cubeVertex.shader", "res/shaders/cubeFragment.shader");

			createDefaultCube();

			float windowAspect = ((float)window.windowWidth / (float)window.windowHeight);
			float fov = 90.0f;
			float zNear = 0.1f;
			float zFar = 10000.0f;

			projection = glm::perspective(fov, windowAspect, zNear, zFar);

			for (auto& filepath : std::filesystem::directory_iterator("res/images"))
			{
				if (filepath.path().stem().string() != "normal")
					textures.push_back(createTexture(filepath.path().string(), true));
			}

			for (int x = 0; x < 10; x++)
			{
				for (int z = 0; z < 10; z++)
				{
					int tex = rand() % textures.size();
					cubePositions.push_back(glm::vec3(x - 5, 0, z - 5));
					cubeTextures.push_back(tex);
				
					if (rand() % 10 > 8)
					{
						int tex = rand() % textures.size();
						cubePositions.push_back(glm::vec3(x - 5, rand() % 3, z - 5));
						cubeTextures.push_back(tex);
					}
				}
			}
		}

		void destroy()
		{
			destroyDefaultCube();

			for (auto& texture : textures)
			{
				destroyTexture(texture);
			}

			texturedCubeShader.free();
		}

		Camera camera;

		void update(float dt)
		{
			texturedCubeShader.use();

			camera.setdt(dt);

			if (Input::movingUp)
				camera.rotateUp();
			if (Input::movingDown)
				camera.rotateDown();
			if (Input::movingLeft)
				camera.rotateLeft();
			if (Input::movingRight)
				camera.rotateRight();

			Input::resetMouse();

			if (Input::isKeyDown(GLFW_KEY_W))
				camera.moveForward();
			if (Input::isKeyDown(GLFW_KEY_S))
				camera.moveBackwards();
			if (Input::isKeyDown(GLFW_KEY_A))
				camera.moveLeft();
			if (Input::isKeyDown(GLFW_KEY_D))
				camera.moveRight();

			texturedCubeShader.setUniformMat4f("uView", camera.getView());
			texturedCubeShader.setUniformMat4f("uProjection", projection);
			for (int i = 0; i < cubePositions.size(); i++)
			{
				drawCube(cubePositions[i], textures.at(cubeTextures.at(i)));
			}
		}
	}
}
