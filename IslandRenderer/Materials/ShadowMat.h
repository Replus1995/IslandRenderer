#pragma once
#include "../../nclgl/ReMaterial.h"

class ShadowMat : public ReMaterial
{
public:
	ShadowMat()
		: ReMaterial("Material_Shadow")
	{
		LoadShader("ShadowVertex.glsl", "ShadowFragment.glsl");
	};
	~ShadowMat() {};

	virtual void SetMaterialParam(const ReMaterialParamPtr& InParam) {};
};
