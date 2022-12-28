#version 460 core


subroutine vec4 ProceduralVerseSub();

subroutine uniform ProceduralVerseSub PVS; 
uniform sampler2D heightMap;
uniform sampler2D biomeMap;
uniform sampler2D grass;
uniform sampler2D snow;
uniform sampler2D rock;
uniform sampler2D sand;
uniform int numberOfTile;
uniform vec3 diffusiveColor;
uniform vec3 specularColor;
uniform vec3 ambientColor;
uniform float kd;
uniform float ks;
uniform float ka;
uniform float alphaPhong;

in vec2 vUVcoord;
in vec3 vNormal;
in vec3 vLightDir;
in vec3 vViewDir;

out vec4 fragColor;


const float PI = 3.14159265359;
subroutine(ProceduralVerseSub)
vec4 TerrainFrag()
{
	vec4 color;
	
	float biomeValue =  texture(biomeMap, vUVcoord.yx/numberOfTile).x;
	float heightValue = texture(heightMap, vUVcoord/numberOfTile).x;
	color = texture(grass, vUVcoord);
	if(biomeValue <= -0.8 && heightValue < 0.0)
	{
		color = texture(sand, vUVcoord); //+ vec4(vec3(0.2), 1.0);
	}
	if(biomeValue > -0.2)
	{
		color = texture(grass, vUVcoord);
	}
	if(heightValue >= 0.2)
	{
		if(biomeValue> -0.8)
		{
			color = texture(snow, vUVcoord) + vec4(vec3(0.2), 1.0);
		}
		if(biomeValue >=-0.2)
		{
			color = texture(rock, vUVcoord);
		}
	}

	//I normalize for sure 
	vec3 N = normalize(vNormal);
	vec3 L = normalize(vLightDir.xyz);
	float lambertian = max(dot(L,N),0.0);
	color = vec4(kd * lambertian * color.xyz, 1.0);
	return color;
}
subroutine(ProceduralVerseSub)
vec4 TreeFrag()
{
	vec4 color;
	//I normalize for sure 
	vec3 N = normalize(vNormal);
	vec3 L = normalize(vLightDir.xyz);
	float lambertian = max(dot(L,N),0.0);
	color = vec4(kd * lambertian * diffusiveColor, 1.0);
	return color;
}

void main()
{
	fragColor = PVS();
}