#pragma once
#include <memory>
#include "Vector3.h"

class ReFrustumObject
{
public:
	ReFrustumObject() {};
	~ReFrustumObject() {};

	virtual Vector3 GetPosition() const = 0;
	virtual float GetBoundingRadius() const = 0;
};

typedef std::shared_ptr<ReFrustumObject> ReFrustumObjectPtr;