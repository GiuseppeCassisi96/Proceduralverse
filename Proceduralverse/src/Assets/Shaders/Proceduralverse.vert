#version 460 core


//Input vars
layout (location = 0) in vec3 cpuPos;
layout (location = 1) in vec2 cpuUVCoord;
layout(location = 2) in vec3 cpuNormal;

//Subroutine type
subroutine vec4 ProceduralVerseSub();



//Uniform vars 
subroutine uniform ProceduralVerseSub PVS;
uniform mat4 model;           
uniform mat4 view;            
uniform mat4 proj;    
uniform mat3 normalMatrix;
uniform float heightScale;
uniform sampler2D heightMap;

//Output vars
out vec3 color;
out vec2 vertUVcoord;
out vec3 normal;

subroutine(ProceduralVerseSub) //index 0
vec4 TerrainGeneration()
{
    vec3 randomPos = cpuPos;
//    randomPos.y = texture(heightMap, cpuUVCoord).x * heightScale;
//    color = vec3(texture(heightMap, cpuUVCoord).x);
	
	randomPos.y = cpuPos.y * heightScale;
	color = vec3(cpuPos.y);


    return proj * view * model * vec4(randomPos, 1.0f);
}

subroutine(ProceduralVerseSub) //index 1
vec4 TreeVertShader()
{
    //We apply normal matrix transformation 
	normal = normalize(normalMatrix * cpuNormal);
	return proj * view * model * vec4(cpuPos,1.0);
}

void main()
{
	gl_Position = PVS();
}