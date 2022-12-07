#pragma once
#include <vector>
#include <GLM/include/vec2.hpp>
#include <GLM/include/common.hpp>
#include <GLM/include/vec3.hpp>
#include <GLM/include/vec4.hpp>
#include <GLM/include/ext/quaternion_geometric.hpp>
#include "UTILS/include/FractalNoise.h"
#include <algorithm>
#include <cstdint>

class FractalNoise
{
private:
	
	int res;
	float SimplexNoise(const glm::vec3& inputVector);
	int32_t fastfloor(float fp);
	uint8_t  hash(int32_t  i);
	float grad(int32_t  hash, float x, float y, float z);
	
public:
	std::vector<float> HeightMap;
	float seed;
	int octaves;
	float frequency;
	float amplitude;
	float ComputeFractal(const glm::vec3& inputVector);
	FractalNoise(int res, int octaves = 2, float frequency = 2.0f, float amplitude = 2.0f, 
		float seed = 0.0f);
	void CreateHeightMap();
};
