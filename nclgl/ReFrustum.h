#pragma once
#include "Matrix4.h"
#include "Plane.h"
#include "RePrimitiveComponent.h"

class ReFrustum
{
public:
	ReFrustum(void) {};
	~ReFrustum(void) {};

	void FromMatrix(const Matrix4& MatrixVP);
	bool InsideFrustum(RePrimitiveComponentPtr Primitive);

protected:
	Plane planes[6];
};

typedef std::shared_ptr<ReFrustum> ReFrustumPtr;