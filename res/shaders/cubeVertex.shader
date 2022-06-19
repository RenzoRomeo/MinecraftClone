#version 460 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoords;

out vec2 fTexCoords;

uniform int uAtlasW;
uniform int uAtlasH;
uniform int uAtlasSpriteSize;
uniform vec2 uAtlasCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
	float x = (uAtlasCoord.x + aTexCoords.x) * uAtlasSpriteSize / uAtlasW;
	float y = (uAtlasCoord.y + aTexCoords.y) * uAtlasSpriteSize / uAtlasH;
	
	fTexCoords = vec2(x, y);
	gl_Position = uProjection * uView * (uModel * vec4(aPosition, 1.0));
}