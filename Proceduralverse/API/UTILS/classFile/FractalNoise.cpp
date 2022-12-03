#include "UTILS/include/FractalNoise.h"

#include <iostream>


FractalNoise::FractalNoise(int width, int height, int octaves, float frequency, float amplitude, float seed)
    : width{ width }, height{ height }, octaves{ octaves }, frequency{ frequency }, amplitude{ amplitude }, seed{ seed }
{
    HeightMap.resize(width, std::vector<float>(height));
}

void FractalNoise::CreateHeightMap()
{
    for(int i = 0; i < height; i++)
    {
	    for(int j = 0; j < width; j++)
	    {
           HeightMap[i][j] = ComputeFractal(glm::vec3(
               i, j, seed));
	    }
    }

 
}

float FractalNoise::SimplexNoise(glm::vec3 inputVector)
{
    const glm::vec2  C = glm::vec2(1.0 / 6.0, 1.0 / 3.0);
    const glm::vec4  D = glm::vec4(0.0, 0.5, 1.0, 2.0);

    // First corner
    glm::vec3 i = floor(inputVector + glm::dot(inputVector,  glm::vec3(C.y)));
    glm::vec3 x0 = inputVector - i + dot(i, glm::vec3(C.x));

    // Other corners
    glm::vec3 g = glm::step( glm::vec3(x0.y, x0.z, x0.x), glm::vec3(x0.x, x0.y, x0.z));
    glm::vec3 l = 1.0f - g;
    glm::vec3 i1 = glm::min( glm::vec3(g.x, g.y, g.z), glm::vec3(l.z, l.x, l.y));
    glm::vec3 i2 = glm::max(glm::vec3(g.x, g.y, g.z), glm::vec3(l.z, l.x, l.y));

    glm::vec3 x1 = x0 - i1 + glm::vec3(C.x);
    glm::vec3 x2 = x0 - i2 + glm::vec3(C.y);
    glm::vec3 x3 = x0 - glm::vec3(D.y); 

    // Permutations
    i = mod289(i);
    glm::vec4 p = permute(permute(permute(
        i.z + glm::vec4(0.0, i1.z, i2.z, 1.0))
        + i.y + glm::vec4(0.0, i1.y, i2.y, 1.0))
        + i.x + glm::vec4(0.0, i1.x, i2.x, 1.0));

    // Gradients: 7x7 points over a square, mapped onto an octahedron.
    // The ring size 17*17 = 289 is close to a multiple of 49 (49*6 = 294)
    float n_ = 0.142857142857f; // 1.0/7.0
    glm::vec3  ns = n_ * glm::vec3(D.w, D.y, D.z) - glm::vec3(D.x, D.z, D.x);

    glm::vec4 j = p - 49.0f * floor(p * ns.z * ns.z);  //  mod(p,7*7)

    glm::vec4 x_ = floor(j * ns.z);
    glm::vec4 y_ = floor(j - 7.0f * x_);    // mod(j,N)

    glm::vec4 x = x_ * ns.x + glm::vec4(ns.y);
    glm::vec4 y = y_ * ns.x + glm::vec4(ns.y);
    glm::vec4 h = 1.0f - abs(x) - abs(y);

    glm::vec4 b0 = glm::vec4(glm::vec2(x.x, x.y), glm::vec2(y.x, y.y));
    glm::vec4 b1 = glm::vec4(glm::vec2(x.z, x.w), glm::vec2(y.z, y.w));

    glm::vec4 s0 = floor(b0) * 2.0f + 1.0f;
    glm::vec4 s1 = floor(b1) * 2.0f + 1.0f;
    glm::vec4 sh = -step(h, glm::vec4(0.0));

    glm::vec4 a0 = glm::vec4(b0.x, b0.z, b0.y, b0.w) + glm::vec4(s0.x, s0.z, s0.y, s0.w)
	* glm::vec4(sh.x, sh.x, sh.y, sh.y);
    glm::vec4 a1 = glm::vec4(b1.x, b1.z, b1.y, b1.w) + glm::vec4(s1.x, s1.z, s1.y, s1.w) * 
        glm::vec4(sh.z, sh.z, sh.w, sh.w);

    glm::vec3 p0 = glm::vec3(glm::vec2(a0.x, a0.y), h.x);
    glm::vec3 p1 = glm::vec3(glm::vec2(a0.z, a0.w),h.y);
    glm::vec3 p2 = glm::vec3(glm::vec2(a1.x, a1.y), h.z);
    glm::vec3 p3 = glm::vec3(glm::vec2(a1.z, a1.w), h.w);

    //Normalise gradients
    glm::vec4 norm = taylorInvSqrt(glm::vec4(glm::dot(p0, p0), glm::dot(p1, p1), glm::dot(p2, p2), glm::dot(p3, p3)));
    p0 *= norm.x;
    p1 *= norm.y;
    p2 *= norm.z;
    p3 *= norm.w;

    // Mix final noise value
    glm::vec4 m = glm::max(0.5f - glm::vec4(glm::dot(x0, x0), glm::dot(x1, x1), 
        glm::dot(x2, x2), glm::dot(x3, x3)), 0.0f);
    m = m * m;
    return 105.0 * glm::dot(m * m, glm::vec4(dot(p0, x0), dot(p1, x1),
                                             dot(p2, x2), dot(p3, x3)));
}

glm::vec3 FractalNoise::mod289(glm::vec3 x)
{
	return x - floor(x * (1.0f / 289.0f)) * 289.0f;
}

glm::vec4 FractalNoise::mod289(glm::vec4 x)
{
    return x - floor(x * (1.0f / 289.0f)) * 289.0f;
}

glm::vec4 FractalNoise::permute(glm::vec4 x)
{
    return mod289(((x * 34.0f) + 10.0f) * x);
}

glm::vec4 FractalNoise::taylorInvSqrt(glm::vec4 r)
{
    return 1.79284291400159f - 0.85373472095314f * r;
}

float FractalNoise::ComputeFractal(glm::vec3 inputVector)
{
    float a = amplitude;
    float f = frequency;
    float result = SimplexNoise(glm::vec3(inputVector.x * f, inputVector.y * f, inputVector.z)) * a;
    for (int i = 1; i < octaves; i++)
    {
        result += SimplexNoise(glm::vec3(inputVector.x * f, inputVector.y * f, inputVector.z)) * a;
        f *= 2.0f;
        a *= 0.5f;
    }
    return result;
}
