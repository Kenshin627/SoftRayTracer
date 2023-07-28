#include "Box.h"
#include <memory>

Box::Box(const glm::vec3& center, uint32_t width, uint32_t height, uint32_t depth, const std::shared_ptr<Material>& mat) :Hittable(mat)
{
	float hw = width / 2.0f;
	float hh = height / 2.0f;
	float hd = depth / 2.0f;
	glm::vec3 min = center - glm::vec3(hw, hh, depth);
	glm::vec3 max = center + glm::vec3(hw, hh, depth);
	aabb = BoundingBox(min, max);
	//faces	
	//XYPlane
	std::shared_ptr<XYPlane> xyMin = std::make_shared<XYPlane>(min.x, max.x, min.y, max.y, min.z, mat);
	std::shared_ptr<XYPlane> xyMax = std::make_shared<XYPlane>(min.x, max.x, min.y, max.y, max.z, mat);

	//XZPlane
	std::shared_ptr<XZPlane> xzMin = std::make_shared<XZPlane>(min.x, max.x, min.z, max.z, min.y, mat);
	std::shared_ptr<XZPlane> xzMax = std::make_shared<XZPlane>(min.x, max.x, min.z, max.z, max.y, mat);

	//YZPlane
	std::shared_ptr<YZPlane> yzMin = std::make_shared<YZPlane>(min.y, max.y, min.z, max.z, min.x, mat);
	std::shared_ptr<YZPlane> yzMax = std::make_shared<YZPlane>(min.y, max.y, min.z, max.z, max.x, mat);

	faces.AddObject(xyMin);
	faces.AddObject(xyMax);
	faces.AddObject(xzMin);
	faces.AddObject(xzMax);
	faces.AddObject(yzMin);
	faces.AddObject(yzMax);
}

bool Box::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec)
{
	return faces.Hit(ray, tMin, tMax, rec);
}

bool Box::GetBoundingBox(BoundingBox& out)
{
	out = aabb;
	return true;
}