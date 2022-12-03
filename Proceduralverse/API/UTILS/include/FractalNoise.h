#pragma once
#include <vector>
#include <GLM/include/vec2.hpp>
#include <GLM/include/common.hpp>
#include <GLM/include/vec3.hpp>
#include <GLM/include/vec4.hpp>
#include <GLM/include/ext/quaternion_geometric.hpp>
#include <algorithm>

class FractalNoise
{
private:
	
	int width, height;
	float SimplexNoise(glm::vec3 inputVector);
	glm::vec3 mod289(glm::vec3 x);
	glm::vec4 mod289(glm::vec4 x);
	glm::vec4 permute(glm::vec4 x);
	glm::vec4 taylorInvSqrt(glm::vec4 r);
	float ComputeFractal(glm::vec3 inputVector);
public:
	std::vector<std::vector<float>> HeightMap;
	float seed;
	int octaves;
	float frequency;
	float amplitude;
	FractalNoise(int width, int height, int octaves = 2, float frequency = 2.0f, float amplitude = 2.0f, 
		float seed = 0.0f);
	void CreateHeightMap();
};
