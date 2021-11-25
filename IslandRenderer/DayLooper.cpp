#include "DayLooper.h"
#include <iostream>
#include "../nclgl/ReDLight.h"
#include "../nclgl/Matrix3.h"

void DayLooper::UpdateDaylight(float msec)
{
	float CurAngle = RadToDeg(acos(Vector3::Dot(Vector3(0, -1, 0), mDayLight->GetDirVector().Normalised())));
	if (mDayLight->GetDirVector().x != 0)
	{
		CurAngle *= mDayLight->GetDirVector().x / abs(mDayLight->GetDirVector().x);
	}
	float NextAngle = CurAngle + msec * mLoopSpeed;
	if (NextAngle > 75.0f)
	{
		NextAngle += -150.0f;
		float CurStrength = mDayLight->GetStrength();
		mDayLight->SetStrength(CurStrength > 0.5 ? 0.1 : 0.9);
	}
	Vector3 tDLightDir = Matrix3::Rotation(NextAngle, Vector3(0, 0, 1)) * Vector3(0, -1, 0);
	mDayLight->SetDirVector(tDLightDir);
}