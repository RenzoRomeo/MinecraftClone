#include "World.h"

namespace MinecraftClone
{
	World::World(Window* window)
		: camera(Camera()), window(window)
	{
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
			// Each set of 6 indices represents one quad
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

		shader = Shader("res/shaders/cubeVertex.shader", "res/shaders/cubeFragment.shader");

		float windowAspect = ((float)window->windowWidth / (float)window->windowHeight);
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

		for (auto& filepath : std::filesystem::directory_iterator("res/images"))
		{
			textures.push_back(createTexture(filepath.path().string(), true));
		}

		defaultScene();
	}

	World::~World()
	{
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);

		for (auto& texture : textures)
		{
			glDeleteTextures(1, &texture.textureId);
		}
	}

	void World::frame(float dt)
	{
		shader.use();

		camera.setdt(dt);
		userInput();

		shader.setUniformMat4f("uView", camera.getView());
		shader.setUniformMat4f("uProjection", projection);

		for (const auto& cube : cubes)
		{
			drawCube(cube);
		}
	}

	void World::addCube(const Cube& cube)
	{
		cubes.push_back(cube);
	}

	void World::drawCube(const Cube& cube)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), cube.position);
		shader.setUniformMat4f("uModel", model);

		int textureSlot = 0;

		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, cube.textureID);
		shader.setUniform1i("uTexture", textureSlot);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)cubeVertices.size());
	}

	Texture World::createTexture(const std::string& filepath, bool pixelated)
	{
			Texture res;
			res.filepath = filepath;
			uint8_t* pixels = stbi_load(res.filepath.c_str(), &res.width, &res.height, &res.numChannels, 0);

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

	void World::defaultScene()
	{
		for (int x = 0; x < 10; x++)
		{
			for (int z = 0; z < 10; z++)
			{
				int tex = rand() % textures.size();
				Cube cube(glm::vec3(x - 5, 0, z - 5), textures.at(tex).textureId);

				if (rand() % 10 > 8)
				{
					int tex = rand() % textures.size();
					Cube cube(glm::vec3(x - 5, rand() % 3, z - 5), textures.at(tex).textureId);
					addCube(cube);
				}

				addCube(cube);
			}
		}
	}
	void World::userInput()
	{
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
	}
}
