#version 460 core

uniform sampler2D heightMap;
uniform sampler2D biomeMap;
uniform sampler2D grass;
uniform sampler2D snow;
uniform sampler2D rock;
uniform sampler2D sand;
uniform int numberOfTile;

in vec2 vertUVcoord;
in vec3 normal;

subroutine vec4 ProceduralVerseSub();

subroutine uniform ProceduralVerseSub PVS; 

out vec4 fragColor;

subroutine(ProceduralVerseSub)
vec4 TerrainFrag()
{
	vec4 color;
	
	float biomeValue =  texture(biomeMap, vertUVcoord.yx/numberOfTile).x;
	float heightValue = texture(heightMap, vertUVcoord/numberOfTile).x;
	color = texture(grass, vertUVcoord);
	if(biomeValue <= -0.8 && heightValue < 0.0)
	{
		color = texture(sand, vertUVcoord); //+ vec4(vec3(0.2), 1.0);
	}
	if(biomeValue > -0.2)
	{
		color = texture(grass, vertUVcoord);
	}
	if(heightValue >= 0.2)
	{
		if(biomeValue> -0.8)
		{
			color = texture(snow, vertUVcoord) + vec4(vec3(0.2), 1.0);
		}
		if(biomeValue >=-0.2)
		{
			color = texture(rock, vertUVcoord);
		}
	}
	return color;
}
subroutine(ProceduralVerseSub)
vec4 TreeFrag()
{
	return vec4(normal, 1.0f);
}

void main()
{
	fragColor = PVS();
}