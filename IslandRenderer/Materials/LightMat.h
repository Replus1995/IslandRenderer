#pragma once
#include "../../nclgl/ReMaterial.h"

class PointLightMat : public ReMaterial
{
public:
	PointLightMat()
		: ReMaterial("Material_PointLight")
	{
		LoadShader("PointLightVertex.glsl", "PointLightFragment.glsl");
	};
	~PointLightMat() {};

	virtual void SetMaterialParam(const ReMaterialParamPtr& InParam){};
};


class DLightMat : public ReMaterial
{
public:
	DLightMat()
		: ReMaterial("Material_DirectionalLight")
	{
		LoadShader("CombineVertex.glsl", "DLightFragment.glsl");
	};
	~DLightMat() {};

	virtual void SetMaterialParam(const ReMaterialParamPtr& InParam) {};
};