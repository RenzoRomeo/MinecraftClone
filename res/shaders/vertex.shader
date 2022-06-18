#version 460 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;

out vec4 fColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main() {
	gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0f);
	fColor = aColor;
}