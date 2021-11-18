#pragma once
#include "../../nclgl/ReMaterial.h"

class PlainMat : public ReMaterial
{
public:
	PlainMat()
		: ReMaterial("Material_Plain")
	{
		LoadShader("BumpVertex.glsl", "Plain_BufferFragment.glsl");
	};
	~PlainMat() {};

	virtual void SetMaterialParam(const ReMaterialParamPtr& InParam) {};

};