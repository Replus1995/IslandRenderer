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
	PlainMat(const std::string& InName)
		: ReMaterial("Material_Plain")
	{};
	~PlainMat() {};

	virtual void UpdateRenderParam() 
	{
		SetShaderVector4("baseColour", mBaseColour);
		SetShaderVector3("emissiveColour", mEmissiveColour);
		SetShaderBool("flatNormal", bFlatNormal);
	};

public:
	Vector4 mBaseColour = Vector4(1,1,1,1);
	Vector3 mEmissiveColour = Vector3(0,0,0);
	bool bFlatNormal = false;
};