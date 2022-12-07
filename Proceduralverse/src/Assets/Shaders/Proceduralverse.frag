#version 410 core

in vec3 color;
in vec2 vertUVcoord;


out vec4 fragColor;

void main()
{
	fragColor = vec4(color, 1.0f);
}