#include "Sphere.h"

Sphere::Sphere(const glm::vec3& center, float radius) :center(center), radius(radius) {}

//(p-c)(p-c) = r^2
//(ray.Origin() + t * ray.Direction() - center) * (ray.Origin() + t * ray.Direction() - center) - r^2 = 0
//t^2 direction.direction + 2t.direction.(origin-center) + (origin - center).(origin - center) - r^2 = 0
bool Sphere::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec)
{
	glm::vec3 oc = ray.Origin() - center;
	float a = glm::dot(ray.Direction(), ray.Direction());
	float b = 2 * glm::dot(ray.Direction(), oc);
	float half_b = b * 0.5;
	float c = glm::dot(oc, oc) - radius * radius;
	float discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
	{
		return false;
	}
	float sqrtd = glm::sqrt(discriminant);
	float root = (-half_b - sqrtd) / a;
	if (root < tMin || root > tMax)
	{
		root = (-half_b + sqrtd) / a;
		if (root < tMin || root > tMax)
		{
			return false;
		}
	}
	rec.point = ray.At(root);
	rec.t = root;
	glm::vec3 out_normal = glm::normalize(rec.point - center);
	rec.SetNormal(ray, out_normal);
}
