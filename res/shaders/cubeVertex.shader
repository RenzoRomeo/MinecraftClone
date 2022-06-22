#version 460 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in vec2 aAtlasCoords;

out vec2 fTexCoords;

uniform int uAtlasW;
uniform int uAtlasH;
uniform int uAtlasSpriteSize;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
	float x = (aAtlasCoords.x + aTexCoords.x) * uAtlasSpriteSize / uAtlasW;
	float y = (aAtlasCoords.y + aTexCoords.y) * uAtlasSpriteSize / uAtlasH;
	
	fTexCoords = vec2(x, y);
	gl_Position = uProjection * uView * (uModel * vec4(aPosition, 1.0));
}