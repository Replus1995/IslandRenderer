#include "ReFrustum.h"

void ReFrustum::FromMatrix(const Matrix4& MatrixVP)
{
	Vector3 xaxis = Vector3(MatrixVP.values[0], MatrixVP.values[4], MatrixVP.values[8]);
	Vector3 yaxis = Vector3(MatrixVP.values[1], MatrixVP.values[5], MatrixVP.values[9]);
	Vector3 zaxis = Vector3(MatrixVP.values[2], MatrixVP.values[6], MatrixVP.values[10]);
	Vector3 waxis = Vector3(MatrixVP.values[3], MatrixVP.values[7], MatrixVP.values[11]);

	planes[0] = Plane(waxis - xaxis, (MatrixVP.values[15] - MatrixVP.values[12]), true);
	planes[1] = Plane(waxis + xaxis, (MatrixVP.values[15] + MatrixVP.values[12]), true);
	planes[2] = Plane(waxis + yaxis, (MatrixVP.values[15] + MatrixVP.values[13]), true);
	planes[3] = Plane(waxis - yaxis, (MatrixVP.values[15] - MatrixVP.values[13]), true);
	planes[4] = Plane(waxis + zaxis, (MatrixVP.values[15] + MatrixVP.values[14]), true);
	planes[5] = Plane(waxis - zaxis, (MatrixVP.values[15] - MatrixVP.values[14]), true);
}

bool ReFrustum::InsideFrustum(const Vector3& Position, const float BoundingRadius)
{
	for (size_t p = 0; p < 6; p++)
	{
		if (!planes[p].SphereInPlane(Position, BoundingRadius))
		{
			return false;
		}
	}
	return true;
}

bool ReFrustum::InsideFrustum(const ReFrustumObjectPtr& Object)
{
	Vector3 Position = Object->GetPosition();
	float Radius = Object->GetBoundingRadius();

	for (size_t p = 0; p < 6; p++)
	{
		if (!planes[p].SphereInPlane(Position, Radius))
		{
			return false;
		}
	}
	return true;
}
