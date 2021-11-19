#pragma once
#include "../../nclgl/ReMaterial.h"

class SkyBoxMatParam : public ReMaterialParam
{
public:
	SkyBoxMatParam() {};
	~SkyBoxMatParam()
	{
		glDeleteTextures(1, &SkyTex);
	};

	GLuint SkyTex;

	static ReMaterialParamPtr LoadDefault()
	{
		std::shared_ptr<SkyBoxMatParam> NewParam(new SkyBoxMatParam());
		NewParam->SkyTex = SOIL_load_OGL_cubemap(
			TEXTUREDIR"skybox/right.jpg", TEXTUREDIR"skybox/left.jpg",
			TEXTUREDIR"skybox/top.jpg", TEXTUREDIR"skybox/bottom.jpg",
			TEXTUREDIR"skybox/front.jpg", TEXTUREDIR"skybox/back.jpg",
			SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
		return NewParam;
	};
};

class SkyBoxMat : public ReMaterial
{
public:
	SkyBoxMat()
		: ReMaterial("Material_HeightMap")
	{
		LoadShader("SkyboxVertex.glsl", "SkyboxFragment.glsl");
		//LoadShader("SkyboxVertex.glsl", "Skybox_BufferFragment.glsl");
	};
	~SkyBoxMat() {};

	virtual void SetMaterialParam(const ReMaterialParamPtr& InParam)
	{
		std::shared_ptr<SkyBoxMatParam> AParam =
			std::dynamic_pointer_cast<SkyBoxMatParam>(InParam);
		if (AParam)
		{
			glUniform1i(glGetUniformLocation(GetShader()->GetProgram(), "cubeTex"), 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, AParam->SkyTex);
		}
	};

};
