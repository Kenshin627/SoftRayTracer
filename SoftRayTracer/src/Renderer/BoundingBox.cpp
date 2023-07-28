#include "BoundingBox.h"
#include <algorithm>

BoundingBox::BoundingBox(const glm::vec3& min, const glm::vec3& max) :min(min), max(max) {}

BoundingBox::BoundingBox(const BoundingBox& box1, const BoundingBox& box2)
{
	glm::vec3 box1Min = box1.Min();
	glm::vec3 box1Max = box1.Max();
	glm::vec3 box2Min = box2.Min();
	glm::vec3 box2Max = box2.Max();

	min =
	{
		glm::min(box1Min.x, box2Min.x),
		glm::min(box1Min.y, box2Min.y),
		glm::min(box1Min.z, box2Min.z),
	};

	max =
	{
		glm::max(box1Max.x, box2Max.x),
		glm::max(box1Max.y, box2Max.y),
		glm::max(box1Max.z, box2Max.z),
	};
}

BoundingBox BoundingBox::SurroundingBox(const BoundingBox& box1, const BoundingBox& box2)
{
	glm::vec3 box1Min = box1.Min();
	glm::vec3 box1Max = box1.Max();
	glm::vec3 box2Min = box2.Min();
	glm::vec3 box2Max = box2.Max();

	glm::vec3 min =
	{
		glm::min(box1Min.x, box2Min.x),
		glm::min(box1Min.y, box2Min.y),
		glm::min(box1Min.z, box2Min.z),
	};

	glm::vec3 max =
	{
		glm::max(box1Max.x, box2Max.x),
		glm::max(box1Max.y, box2Max.y),
		glm::max(box1Max.z, box2Max.z),
	};
	return BoundingBox(min, max);
}

bool BoundingBox::Hit(const Ray& r, float minTime, float maxTime)
{
	//for (int a = 0; a < 3; a++) {
		auto tx0 = fmin((min.x - r.Origin().x) / r.Direction().x,
			(max.x - r.Origin().x) / r.Direction().x);
		auto tx1 = fmax((min.x - r.Origin().x) / r.Direction().x,
			(max.x - r.Origin().x) / r.Direction().x);
		minTime = fmax(tx0, minTime);
		maxTime = fmin(tx1, maxTime);
		if (maxTime < minTime)
		return false;

		auto ty0 = fmin((min.y - r.Origin().y) / r.Direction().y,
			(max.y - r.Origin().y) / r.Direction().y);
		auto ty1 = fmax((min.y - r.Origin().y) / r.Direction().y,
			(max.y - r.Origin().y) / r.Direction().y);
		minTime = fmax(ty0, minTime);
		maxTime = fmin(ty1, maxTime);
		if (maxTime < minTime)
			return false;

		auto tz0 = fmin((min.z - r.Origin().z) / r.Direction().z,
			(max.z - r.Origin().z) / r.Direction().z);
		auto tz1 = fmax((min.z - r.Origin().z) / r.Direction().z,
			(max.z - r.Origin().z) / r.Direction().z);
		minTime = fmax(tz0, minTime);
		maxTime = fmin(tz1, maxTime);
		if (maxTime < minTime)
			return false;
	//}
	return true;
}

Axis BoundingBox::LongestAxis()
{
	float x = max.x - min.x;
	float y = max.y - min.y;
	float z = max.z - min.z;
	if ( x >= y && x >=z)
	{
		return Axis::x;
	}
	else if (y >=x && y >= z)
	{
		return Axis::y;
	}
	else
	{
		return Axis::z;
	}
}