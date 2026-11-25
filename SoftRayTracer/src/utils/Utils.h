#pragma once
#include <glm/glm.hpp>
#include <random>
#include <cstdint>

class Tool
{
public:
	static std::mt19937& Generator()
	{
		static thread_local std::mt19937 engine(1);
		return engine;
	}

	static float Random()
	{
		return (Generator()() >> 8) * (1.0f / 16777216.0f);
	}

	static float Random(float min, float max)
	{
		return min + (max - min) * Random();
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
			float squared = glm::dot(d, d);
			if (squared > 1e-20f && squared <= 1)
			{
				return glm::normalize(d);
			}
		}
	}

	static bool NearZero(const glm::vec3& v)
	{
		const auto epsilon = 1e-8;
		return (std::fabs(v.x) < epsilon) && (std::fabs(v.y) < epsilon) && (fabs(v.z) < epsilon);
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

	static glm::vec3 RandomInUnitDisk()
	{
		while (true)
		{
			glm::vec3 v = { Random(-1.0f, 1.0f), Random(-1.0f, 1.0f), 0.0f };
			if (glm::length(v) <= 1)
			{
				return v;
			}
		}
	}

	static int RandomInt(int min, int max)
	{
		return static_cast<int>(Random(min, max + 1));
	}
};