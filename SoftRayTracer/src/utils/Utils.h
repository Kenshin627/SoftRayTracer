#pragma once
#include <glm/glm.hpp>
#include <random>

class Tool
{
public:
	static float Random(float min, float max)
	{
		static std::uniform_real_distribution<float> distribution(min, max);
		static std::mt19937 generator;
		return distribution(generator);
	}

	static glm::vec3 RandomVector(float min, float max)
	{
		return glm::vec3(Random(min, max), Random(min, max), Random(min, max));
	}

	static glm::vec3 RandomInUnitSphere()
	{
		while (true)
		{
			glm::vec3 d = RandomVector(-1.0f, 1.0f);
			if (glm::length(d) <= 1)
			{
				return glm::normalize(d);
			}
		}
	}

	static bool NearZero(const glm::vec3& v)
	{
		return glm::abs(v.x) < 1e-8 && glm::abs(v.y) < 1e-8 && glm::abs(v.z) < 1e-8;
	}

	static glm::vec3 Reflect()
	{
		
	}
};