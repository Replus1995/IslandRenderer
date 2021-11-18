#pragma once
#include "Matrix4.h"
#include "Plane.h"
#include "ReFrustumObject.h"

class ReFrustum
{
public:
	ReFrustum(void) {};
	~ReFrustum(void) {};

	void FromMatrix(const Matrix4& MatrixVP);
	bool InsideFrustum(const Vector3& Position, const float BoundingRadius);
	bool InsideFrustum(const ReFrustumObjectPtr& Object);
	

protected:
	Plane planes[6];
};

typedef std::shared_ptr<ReFrustum> ReFrustumPtr;