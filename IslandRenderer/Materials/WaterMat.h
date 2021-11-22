#pragma once
#include "../../nclgl/ReMaterial.h"

class WaterMat : public ReMaterial
{
public:
	WaterMat()
		: ReMaterial("Material_Water")
	{
		LoadShader("WaterVertex.glsl", "WaterFragment.glsl");
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
		DiffuseTex = SOIL_load_OGL_texture(TEXTUREDIR"water.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
		NormTex = SOIL_load_OGL_texture(TEXTUREDIR"waterbump.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
		SetTextureRepeating(DiffuseTex, true);
		SetTextureRepeating(NormTex, true);
	};

public:
	GLuint DiffuseTex = 0;
	GLuint NormTex = 0;

};
