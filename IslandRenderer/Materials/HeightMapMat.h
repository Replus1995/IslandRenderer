#pragma once
#include "../../nclgl/ReMaterial.h"

class HeightMapMatParam : public ReMaterialParam
{
public:
	HeightMapMatParam() {};
	~HeightMapMatParam() 
	{
		glDeleteTextures(1, &DiffuseTex);
		glDeleteTextures(1, &BumpTex);
	};

	GLuint DiffuseTex;
	GLuint BumpTex;

	static ReMaterialParamPtr LoadDefault()
	{
		std::shared_ptr<HeightMapMatParam> NewParam(new HeightMapMatParam());
		NewParam->DiffuseTex = SOIL_load_OGL_texture(TEXTUREDIR"Barren Reds.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
		NewParam->BumpTex = SOIL_load_OGL_texture(TEXTUREDIR"Barren RedsDOT3.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
		SetTextureRepeating(NewParam->DiffuseTex, true);
		SetTextureRepeating(NewParam->BumpTex, true);
		return NewParam;
	};
};

class HeightMapMat : public ReMaterial
{
public:
	HeightMapMat()
		: ReMaterial("Material_HeightMap")
	{
		LoadShader("BumpVertex.glsl", "HeightMap_BufferFragment.glsl");
	};
	~HeightMapMat() {};

	virtual void SetMaterialParam(const ReMaterialParamPtr& InParam)
	{
		std::shared_ptr<HeightMapMatParam> AParam = 
			std::dynamic_pointer_cast<HeightMapMatParam>(InParam);
		if (AParam)
		{
			SetShaderTexture2D("diffuseTex", AParam->DiffuseTex, 0);
			SetShaderTexture2D("bumpTex", AParam->BumpTex, 1);
		}
	};

};
