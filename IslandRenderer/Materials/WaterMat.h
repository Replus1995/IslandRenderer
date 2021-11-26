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
		glDeleteTextures(1, &SkyTex);
	};

	virtual void UpdateRenderParam()
	{
		SetShaderTexture2D("diffuseTex", DiffuseTex, 0);
		SetShaderTexture2D("normTex", NormTex, 1);

		glUniform1i(glGetUniformLocation(GetShader()->GetProgram(), "cubeTex"), 2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_CUBE_MAP, SkyTex);
	};

	void LoadTextures()
	{
		DiffuseTex = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"water.tga", true);
		NormTex = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"waterbump.png", true);
		SetTextureRepeating(DiffuseTex, true);
		SetTextureRepeating(NormTex, true);

		SkyTex = SimpleImage::LoadTextureCubeFromFile(
			TEXTUREDIR"skybox/left.jpg", TEXTUREDIR"skybox/right.jpg",
			TEXTUREDIR"skybox/bottom.jpg", TEXTUREDIR"skybox/top.jpg",
			TEXTUREDIR"skybox/back.jpg", TEXTUREDIR"skybox/front.jpg",
			false);
	};

public:
	GLuint DiffuseTex = 0;
	GLuint NormTex = 0;
	GLuint SkyTex = 0;

};
