#pragma once
#include "../../nclgl/ReMaterial.h"

enum GLTFAlphaMode : int
{
	GLTF_AM_OPAQUE = 0,
	GLTF_AM_MASK,
	GLTF_AM_BLEND
};

class GLTFMat : public ReMaterial
{
public:
	GLTFMat(const std::string& InName)
		: ReMaterial(InName)
	{
		LoadShader("CommonVertex.glsl", "GLTFFragment.glsl");
	};

	GLTFMat(const std::string& InName, const std::string& InVertex, const std::string& InFragment)
		: ReMaterial(InName)
	{
		LoadShader(InVertex, InFragment);
	};

	virtual ~GLTFMat() 
	{
		if (mBaseColorTex) glDeleteTextures(1, &mBaseColorTex);
		if (mMetallicRoughnessTex) glDeleteTextures(1, &mMetallicRoughnessTex);
		if (mNormalTex) glDeleteTextures(1, &mNormalTex);
		if (mOcclutionTex) glDeleteTextures(1, &mOcclutionTex);
		if (mEmissiveTex) glDeleteTextures(1, &mEmissiveTex);
	};

	virtual void UpdateRenderParam()
	{
		SetShaderVector4("baseColor", mBaseColor);
		SetShaderTexture2D("baseColorTex", mBaseColorTex, 0);
		SetShaderFloat("metallic", mMetallic);
		SetShaderFloat("roughness", mRoughness);
		SetShaderTexture2D("metallicRoughnessTex", mMetallicRoughnessTex, 1);
		SetShaderTexture2D("normalTex", mNormalTex, 2);
		SetShaderFloat("normalScale", mNormalScale);
		SetShaderTexture2D("occlutionTex", mOcclutionTex, 3);
		SetShaderFloat("occlutionStrength", mOcclutionStrength);
		SetShaderTexture2D("emissiveTex", mEmissiveTex, 4);
		SetShaderVector3("emissiveFactor", mEmissiveFactor);
		SetShaderInt("alphaMode", mAlphaMode);
		SetShaderFloat("alphaCutoff", mAlphaCutoff);

		SetShaderBool("bUseBaseColorTex", mBaseColorTex ? true : false);
		SetShaderBool("bUseMetallicRoughnessTex", mMetallicRoughnessTex ? true : false);
		SetShaderBool("bUseNormalTex", mNormalTex ? true : false);
		SetShaderBool("bUseOcclutionTex", mOcclutionTex ? true : false);
		SetShaderBool("bUseEmissiveTex", mEmissiveTex ? true : false);
	};

	virtual void LoadGLTFShader()
	{
		
	};

public:
	//PBR//
	Vector4 mBaseColor = Vector4(1, 1, 1, 1);
	GLuint mBaseColorTex = 0;
	float mMetallic = 1.0f;
	float mRoughness = 1.0f;
	GLuint mMetallicRoughnessTex = 0;
	//PBR//
	//Extra//
	GLuint mNormalTex = 0;
	float mNormalScale = 1.0f;
	GLuint mOcclutionTex = 0;
	float mOcclutionStrength = 1.0f;
	GLuint mEmissiveTex = 0;
	Vector3 mEmissiveFactor = Vector3(0, 0, 0);
	//Extra//
	GLTFAlphaMode mAlphaMode = GLTF_AM_OPAQUE;
	float mAlphaCutoff = 0.5f;
	bool mDoubleSided = false;
};

typedef std::shared_ptr<GLTFMat> GLTFMatPtr;
