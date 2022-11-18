#include <UTILS/include/FractalNoise.h>

FractalNoise::FractalNoise(int octaves, float frequency, float amplitude)
	: octaves{ octaves }, frequency{ frequency }, amplitude{ amplitude } {}

glm::vec2 FractalNoise::Mod289(glm::vec2 x)
{
	return x - floor(x * (1.0f / 289.0f)) * 289.0f;
}

glm::vec3 FractalNoise::Mod289(glm::vec3 x)
{
	return x - floor(x * (1.0f / 289.0f)) * 289.0f;
}

glm::vec3 FractalNoise::Permute(glm::vec3 x)
{
	return Mod289(((x * 34.0f) + 10.0f) * x);
}

float FractalNoise::SimplexNoise2D(glm::vec2 inputVector)
{
	const glm::vec4 c{ 0.211324865405187f, 0.366025403784439f,
		              -0.577350269189626f, 0.024390243902439f };
	glm::vec2 i = floor(inputVector + glm::dot(inputVector, glm::vec2(c.y)));
	glm::vec2 x0 = inputVector - i + glm::dot(i, glm::vec2(c.x));
	glm::vec2 i1 = (x0.x > x0.y) ? glm::vec2(1.0f, 0.0f) : glm::vec2(0.0f, 1.0f);
	glm::vec4 x12 = glm::vec4(x0.x, x0.y, x0.x, x0.y) + glm::vec4(c.x, c.x, c.z, c.z);
	x12 = glm::vec4{ x12.x - i1.x, x12.y - i1.y, x12.z, x12.w };
	i = Mod289(i);
	glm::vec3 p = Permute(Permute(i.y + glm::vec3(0.0, i1.y, 1.0))
		+ i.x + glm::vec3(0.0, i1.x, 1.0));

	glm::vec3 m = glm::max(0.5f - glm::vec3(dot(x0, x0), glm::dot(glm::vec2(x12.x, x12.y), glm::vec2(x12.x, x12.y)),
		glm::dot(glm::vec2(x12.z, x12.w), glm::vec2(x12.z, x12.w))), 0.0f);
	m = m * m;
	m = m * m;

	glm::vec3 x = 2.0f * glm::fract(p * glm::vec3(c.w)) - 1.0f;
	glm::vec3 h = abs(x) - 0.5f;
	glm::vec3 ox = floor(x + 0.5f);
	glm::vec3 a0 = x - ox;

	m *= 1.79284291400159f - 0.85373472095314f * (a0 * a0 + h * h);

	// Compute final noise value at P
	glm::vec3 g;
	g.x = a0.x * x0.x + h.x * x0.y;
	g = glm::vec3(g.x, glm::vec2(a0.y, a0.z) * glm::vec2(x12.x, x12.z) + 
	glm::vec2(h.y, h.z) * glm::vec2(x12.y, x12.w));
	return 130.0f * glm::dot(m, g);
}

float FractalNoise::ComputeFractalNoise(glm::vec2 inputVector)
{
	return 0.0f;
}

int FractalNoise::GetOctaves()
{
	return 0;
}

float FractalNoise::GetFrequency()
{
	return 0.0f;
}

float FractalNoise::GetAmplitude()
{
	return 0.0f;
}

int FractalNoise::SetOctaves()
{
	return 0;
}

float FractalNoise::SetFrequency()
{
	return 0.0f;
}

float FractalNoise::SetAmplitude()
{
	return 0.0f;
}

