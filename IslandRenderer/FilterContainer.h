#pragma once
#include<memory>

class RePrimitiveComponent;

struct PrimitiveContainer
{
	std::shared_ptr<RePrimitiveComponent> Component = nullptr;
	float Distance = 0;

	static bool CompareByDistance(const PrimitiveContainer& a, const PrimitiveContainer& b)
	{
		return (a.Distance < b.Distance) ? true : false;
	}
};