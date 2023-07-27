#include "BvhNode.h"
#include "../utils/Utils.h"
#include <iostream>

static bool Compare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b, int axis)
{
	BoundingBox bbox1;
	BoundingBox bbox2;
	if (!a->GetBoundingBox(bbox1) || !b->GetBoundingBox(bbox2))
	{
		return false;
	}
	return bbox1.Min()[axis] < bbox2.Min()[axis];
}

static bool CompareX(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b)
{
	return Compare(a, b, 0);
}

static bool CompareY(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b)
{
	return Compare(a, b, 1);
}

static bool CompareZ(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b)
{
	return Compare(a, b, 2);
}

BvhNode::BvhNode(const HittableList& list) :BvhNode(list.GetAll(), 0, list.GetAll().size()) {}

BvhNode::BvhNode(const std::vector<std::shared_ptr<Hittable>>& objects, uint32_t start, uint32_t end)
{
	auto objs = objects;
	uint32_t span = end - start;
	int axis = Tool::RandomInt(0, 3);
	auto comparator = axis == 0 ? CompareX :
					  axis == 1 ? CompareY :
					              CompareZ;
	if (span == 1)
	{
		left = right = objs[start];
	}
	else if (span == 2)
	{
		if (comparator(objs[start], objs[start + 1]))
		{
			left  = objs[start];
			right = objs[start + 1];
		}
		else
		{
			left  = objs[start + 1];
			right = objs[start];
		}
	}
	else
	{
		std::sort(objs.begin() + start, objs.begin() + end, comparator);
		uint32_t mid = start + span / 2;
		left = std::make_shared<BvhNode>(objs, start, mid);
		right = std::make_shared<BvhNode>(objs, mid, end);
	}
	BoundingBox leftBbox;
	BoundingBox rightBbox;
	if (!left->GetBoundingBox(leftBbox) || !right->GetBoundingBox(rightBbox))
	{
		std::cout << "boundingbox error" << std::endl;
		return;
	}
	aabb = BoundingBox::SurroundingBox(leftBbox, rightBbox);
}

bool BvhNode::Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec)
{
	if (!aabb.Hit(ray, tMin, tMax))
	{
		return false;
	}
	bool leftHit = left->Hit(ray, tMin, tMax, rec);
	bool rightHit = right->Hit(ray, tMin, leftHit ? rec.t : tMax, rec);
	return leftHit || rightHit;
}

bool BvhNode::GetBoundingBox(BoundingBox& out)
{
	out = aabb;
	return true;
}