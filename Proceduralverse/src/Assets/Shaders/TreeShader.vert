#version 410 core

layout(location = 0) in vec3 cpuPos;
layout(location = 2) in vec3 cpuNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat3 normalMatrix;
out vec3 normal;

void main()
{
	//We apply normal matrix transformation 
	normal = normalize(normalMatrix * cpuNormal) ;
	gl_Position = proj * view * model * vec4(cpuPos,1.0);
}