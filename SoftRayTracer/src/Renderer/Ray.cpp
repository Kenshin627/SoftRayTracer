#include "Ray.h"

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction):origin(origin
), direction(direction)
{
	
}

glm::vec3 Ray::At(float t) const
{
	return origin + t * direction;
}