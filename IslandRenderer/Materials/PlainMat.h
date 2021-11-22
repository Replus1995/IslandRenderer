#pragma once
#include "../../nclgl/ReMaterial.h"

class PlainMat : public ReMaterial
{
public:
	PlainMat()
		: ReMaterial("Material_Plain")
	{
		LoadShader("CommonVertex.glsl", "PlainFragment.glsl");
	};
	~PlainMat() {};

	virtual void UpdateRenderParam() {};

};