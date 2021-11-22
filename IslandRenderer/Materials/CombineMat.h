#pragma once
#include "../../nclgl/ReMaterial.h"

class CombinMat : public ReMaterial
{
public:
	CombinMat()
		: ReMaterial("Material_Combine")
	{
		LoadShader("QuadVertex.glsl", "CombineFragment.glsl");
	};
	~CombinMat() {};

	virtual void UpdateRenderParam() {};

};
