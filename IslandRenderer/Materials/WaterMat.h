#pragma once
#include "../../nclgl/ReMaterial.h"

class WaterMat : public ReMaterial
{
public:
	WaterMat()
		: ReMaterial("Material_Water")
	{
		//LoadShader("WaterVertex.glsl", "WaterFragment.glsl");
		LoadShader("WaterVertex.glsl", "WaterLateFragment.glsl");
	};
	~WaterMat() 
	{
		glDeleteTextures(1, &DiffuseTex);
		glDeleteTextures(1, &NormTex);
	};

	virtual void UpdateRenderParam()
	{
		SetShaderTexture2D("diffuseTex", DiffuseTex, 0);
		SetShaderTexture2D("normTex", NormTex, 1);
	};

	void LoadTextures()
	{
		DiffuseTex = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"water.tga", true);
		NormTex = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"waterbump.png", true);
		SetTextureRepeating(DiffuseTex, true);
		SetTextureRepeating(NormTex, true);
	};

public:
	GLuint DiffuseTex = 0;
	GLuint NormTex = 0;

};
