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

	static glm::vec3 Reflect(const glm::vec3& in, const glm::vec3& n)
	{
		return glm::dot(-in, n) * n * 2.0f + in;
	}

	static glm::vec3 Reflact(const glm::vec3& in, const glm::vec3& n, float ior)
	{
		float cosTheta = glm::min(glm::dot(-in, n), 1.0f);
		glm::vec3 outPerp = ior * (in + cosTheta * n);
		float perpLen = glm::length(outPerp);
		glm::vec3 parallel = -glm::sqrt(std::fabs(1.0f - perpLen * perpLen)) * n;
		return glm::normalize(outPerp + parallel);
	}

	static glm::vec3 RandomInUnitCircle()
	{
		while (true)
		{
			glm::vec3 v = { Random(-1.0f, 1.0f), Random(-1.0f, 1.0f), 0 };
			if (glm::length(v) <= 1)
			{
				return glm::normalize(v);
			}
		}
	}
};