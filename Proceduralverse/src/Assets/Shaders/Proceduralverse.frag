#version 410 core

in vec3 color;
in vec2 vertUVcoord;
in vec3 normal;

subroutine vec4 ProceduralVerseSub();

subroutine uniform ProceduralVerseSub PVS; 

out vec4 fragColor;

subroutine(ProceduralVerseSub)
vec4 TerrainFrag()
{
	return vec4(color, 1.0f);
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