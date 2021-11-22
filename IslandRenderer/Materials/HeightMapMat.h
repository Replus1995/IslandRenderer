#pragma once
#include "../../nclgl/ReMaterial.h"

class HeightMapMat : public ReMaterial
{
public:
	HeightMapMat()
		: ReMaterial("Material_HeightMap")
	{
		LoadShader("CommonVertex.glsl", "HeightMapFragment.glsl");
	};
	~HeightMapMat() 
	{
		glDeleteTextures(1, &GrassColor);
		glDeleteTextures(1, &GrassNorm);
		glDeleteTextures(1, &SandColor);
		glDeleteTextures(1, &SandNorm);
		glDeleteTextures(1, &CliffColor);
		glDeleteTextures(1, &CliffNorm);
		glDeleteTextures(1, &BottomColor);
		glDeleteTextures(1, &BottomNorm);
	};

	virtual void UpdateRenderParam()
	{
		SetShaderTexture2D("grassColor", GrassColor, 0);
		SetShaderTexture2D("grassNorm", GrassNorm, 1);
		SetShaderTexture2D("sandColor", SandColor, 2);
		SetShaderTexture2D("sandNorm", SandNorm, 3);
		SetShaderTexture2D("cliffColor", CliffColor, 4);
		SetShaderTexture2D("cliffNorm", CliffNorm, 5);
		SetShaderTexture2D("bottomColor", BottomColor, 6);
		SetShaderTexture2D("bottomNorm", BottomNorm, 7);
	};

	void LoadTextures()
	{
		GrassColor = SOIL_load_OGL_texture(TEXTUREDIR"Terrain/Grass/GrassColor.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
		GrassNorm = SOIL_load_OGL_texture(TEXTUREDIR"Terrain/Grass/GrassNormal.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
		SandColor = SOIL_load_OGL_texture(TEXTUREDIR"Terrain/Sand/SandColor.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
		SandNorm = SOIL_load_OGL_texture(TEXTUREDIR"Terrain/Sand/SandNormal.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
		CliffColor = SOIL_load_OGL_texture(TEXTUREDIR"Terrain/Rock/RockColor.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
		CliffNorm = SOIL_load_OGL_texture(TEXTUREDIR"Terrain/Rock/RockNormal.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
		BottomColor = SOIL_load_OGL_texture(TEXTUREDIR"Terrain/Pebbles/PebblesColor.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
		BottomNorm = SOIL_load_OGL_texture(TEXTUREDIR"Terrain/Pebbles/PebblesNormal.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

		SetTextureRepeating(GrassColor, true);
		SetTextureRepeating(GrassNorm, true);
		SetTextureRepeating(SandColor, true);
		SetTextureRepeating(SandNorm, true);
		SetTextureRepeating(CliffColor, true);
		SetTextureRepeating(CliffNorm, true);
		SetTextureRepeating(BottomColor, true);
		SetTextureRepeating(BottomNorm, true);
	};

public:
	GLuint GrassColor = 0;
	GLuint GrassNorm = 0;
	GLuint SandColor = 0;
	GLuint SandNorm = 0;
	GLuint CliffColor = 0;
	GLuint CliffNorm = 0;
	GLuint BottomColor = 0;
	GLuint BottomNorm = 0;
};
