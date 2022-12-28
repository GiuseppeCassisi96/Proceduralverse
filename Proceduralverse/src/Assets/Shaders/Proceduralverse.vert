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
uniform mat3 NormalMatrix;
uniform vec3 sunPos;

//Output vars
out vec2 vUVcoord;
out vec3 vNormal;   //N
out vec3 vLightDir; //L
out vec3 vViewDir;  //V

subroutine(ProceduralVerseSub) //index 0
vec4 TerrainGeneration()
{
    vec3 randomPos = cpuPos;
	vUVcoord = cpuUVCoord;
	randomPos.y = cpuPos.y * heightScale;
	//TRANSFORMATION

	//Position of vertex in view coords
	vec4 mvPos = view * model * vec4(randomPos, 1.0f);
	//Is CameraPos(0.0,0.0,0.0) - mvPos.xyz -->  -mvPos.xyz
	vViewDir = -mvPos.xyz;
	//Position of ligth in view coords
	vec4 lighSunPos = view * vec4(sunPos, 1.0);
	vLightDir = lighSunPos.xyz - mvPos.xyz;
	vNormal = normalize(NormalMatrix * cpuPos);
	
	return proj * mvPos;  
}

subroutine(ProceduralVerseSub) //index 1
vec4 TreeVertShader()
{
	//TRANSFORMATION
	//We apply normal matrix transformation 
	vNormal = normalize(mat3(inverse(transpose(view * cpuTranslation))) * cpuNormal);
	//Position of vertex in view coords
	vec4 mvPos = view * cpuTranslation * vec4(cpuPos, 1.0f);
	//Position of ligth in view coords
	vec4 lighSunPos = view * vec4(sunPos, 1.0);
	vLightDir = lighSunPos.xyz - mvPos.xyz;
	vViewDir = -mvPos.xyz;
	return proj * mvPos;
}

void main()
{
	gl_Position = PVS();
}