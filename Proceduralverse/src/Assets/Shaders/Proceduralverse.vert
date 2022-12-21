#version 460 core


//Input vars
layout (location = 0) in vec3 cpuPos;
layout (location = 1) in vec2 cpuUVCoord;
layout(location = 2) in vec3 cpuNormal;
layout(location = 3) in vec3 cpuTangent;
layout(location = 4) in vec3 cpuBiTangent;
layout(location = 5) in mat4 cpuTranslation;

//Subroutine type
subroutine vec4 ProceduralVerseSub();



//Uniform vars 
subroutine uniform ProceduralVerseSub PVS;
uniform mat4 model;           
uniform mat4 view;            
uniform mat4 proj;    
uniform float heightScale;
uniform int numberOfTile;

//Output vars
out vec2 vertUVcoord;
out vec3 normal;

subroutine(ProceduralVerseSub) //index 0
vec4 TerrainGeneration()
{
    vec3 randomPos = cpuPos;
	vertUVcoord = cpuUVCoord;
	randomPos.y = cpuPos.y * heightScale;
	return proj * view * model * vec4(randomPos, 1.0f);  
}

subroutine(ProceduralVerseSub) //index 1
vec4 TreeVertShader()
{
	//We apply normal matrix transformation 
	normal = normalize(mat3(inverse(transpose(view * cpuTranslation))) * cpuNormal);
	return proj * view * cpuTranslation * vec4(cpuPos,1.0);
}

void main()
{
	gl_Position = PVS();
}