#version 410 core 
layout (vertices = 4) out;

in vec2 vertUVCoord[];
out vec2 tescUVCoord[];

uniform int segmentsPerEdge;

void main()
{
	//I'm simply passing primitives data to the TES 
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	tescUVCoord[gl_InvocationID] = vertUVCoord[gl_InvocationID];

	//I'm defining how much tessellation to do
	if(gl_InvocationID == 0)
	{
		//I'm defining the number of segments per outers edge
		gl_TessLevelOuter[0] = 10;
		gl_TessLevelOuter[1] = 10;
		gl_TessLevelOuter[2] = 10;
		gl_TessLevelOuter[3] = 10;

		//I'm defining the number of segments per inners edge
		gl_TessLevelInner[0] = 10;
		gl_TessLevelInner[1] = 10;
	}
}