#pragma once
#include "../../nclgl/ReMaterial.h"

class SkyBoxMat : public ReMaterial
{
public:
	SkyBoxMat()
		: ReMaterial("Material_HeightMap")
	{
		LoadShader("SkyboxVertex.glsl", "SkyboxFragment.glsl");
	};
	~SkyBoxMat() 
	{
		glDeleteTextures(1, &SkyTex);
	};

	virtual void UpdateRenderParam()
	{
		glUniform1i(glGetUniformLocation(GetShader()->GetProgram(), "cubeTex"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, SkyTex);
	};

	void LoadTextures()
	{
		SkyTex = SimpleImage::LoadTextureCubeFromFile(
			TEXTUREDIR"skybox/left.jpg", TEXTUREDIR"skybox/right.jpg",
			TEXTUREDIR"skybox/bottom.jpg", TEXTUREDIR"skybox/top.jpg",
			TEXTUREDIR"skybox/back.jpg", TEXTUREDIR"skybox/front.jpg",
			false);
	};
public:
	GLuint SkyTex = 0;
};
