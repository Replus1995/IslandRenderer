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
			TEXTUREDIR"rusted_west.jpg", TEXTUREDIR"rusted_east.jpg",
			TEXTUREDIR"rusted_up.jpg", TEXTUREDIR"rusted_down.jpg",
			TEXTUREDIR"rusted_south.jpg", TEXTUREDIR"rusted_north.jpg",
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
