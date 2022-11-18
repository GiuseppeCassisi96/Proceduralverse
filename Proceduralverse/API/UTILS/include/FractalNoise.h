#pragma once

#include <GLM/include/glm.hpp>
#include <GLM/include/gtc/matrix_transform.hpp>
#include <GLM/include/gtc/type_ptr.hpp>
class FractalNoise
{
public:
	FractalNoise(int octaves, float frequency, float amplitude);
	glm::vec2 Mod289(glm::vec2 x);
	glm::vec3 Mod289(glm::vec3 x);
	glm::vec3 Permute(glm::vec3 x);
	float SimplexNoise2D(glm::vec2 inputVector);
	float ComputeFractalNoise(glm::vec2 inputVector);
	
	int GetOctaves();
	float GetFrequency();
	float GetAmplitude();
	int SetOctaves();
	float SetFrequency();
	float SetAmplitude();
private:
	int octaves;
	float frequency, amplitude;
};
