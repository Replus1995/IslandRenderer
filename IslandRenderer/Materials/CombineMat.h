#pragma once
#include "../../nclgl/ReMaterial.h"

class CombinMat : public ReMaterial
{
public:
	CombinMat()
		: ReMaterial("Material_Combine")
	{
		LoadShader("CombineVertex.glsl", "CombineFragment.glsl");
	};
	~CombinMat() {};

	virtual void SetMaterialParam(const ReMaterialParamPtr& InParam) {};

};
