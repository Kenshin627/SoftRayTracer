#include "HittableList.h"

void HittableList::AddObject(const std::shared_ptr<Hittable>& obj)
{
	objects.push_back(obj);
}

bool HittableList::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec)
{
	bool hitted = false;
	HitRecord record;
	float closetHit = tMax;
	for (auto& hittable : objects)
	{
		if (hittable->Hit(ray, tMin, closetHit, record))
		{
			hitted = true;
			closetHit = record.t;
			rec = record;
		}
	}
	return hitted;
}

bool HittableList::GetBoundingBox(BoundingBox& out)
{
	bool firstObject = true;
	BoundingBox bbox;
	for (const auto& obj : objects)
	{
		if (!obj->GetBoundingBox(bbox))
		{
			
			return false;
		}
		else 
		{
			out = firstObject ? bbox : BoundingBox(bbox, out);
		}
		firstObject = false;
	}
	return true;
}