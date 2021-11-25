#pragma once
#include "PlainMat.h"

class FireFlyMat : public PlainMat
{
public:
	FireFlyMat()
		: PlainMat("Material_FireFly")
	{
		LoadShader("CommonVertex.glsl", "FireFlyFragment.glsl");
	};
	~FireFlyMat() {};
};