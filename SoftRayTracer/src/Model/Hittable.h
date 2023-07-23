#pragma once
#include "../Renderer/Ray.h"

struct HitRecord
{
	glm::vec3 point;
	glm::vec3 normal;
	float t;
	bool frontFace;
	void SetNormal(const Ray& ray, const glm::vec3& out_Normal)
	{
		if (glm::dot(ray.Direction(), out_Normal) < 0)
		{
			frontFace = true;
			normal = out_Normal;
		}
		else
		{
			frontFace = false;
			normal = -out_Normal;
		}
	}
};

class Hittable
{
public:
	Hittable() = default;
	virtual ~Hittable() = default;
	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) = 0;
};