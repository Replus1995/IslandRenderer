#pragma once
#include "../../nclgl/ReMaterial.h"

class HeightMapMat : public ReMaterial
{
public:
	HeightMapMat()
		: ReMaterial("Material_HeightMap")
	{
		//LoadShader("CommonVertex.glsl", "HeightMapFragment.glsl");
		LoadShader("CommonVertex.glsl", "HeightMapMoreFragment.glsl");
	};
	~HeightMapMat() 
	{
		glDeleteTextures(1, &GrassColor);
		glDeleteTextures(1, &GrassNorm);
		glDeleteTextures(1, &GrassRough);
		glDeleteTextures(1, &GrassOcc);
		glDeleteTextures(1, &SandColor);
		glDeleteTextures(1, &SandNorm);
		glDeleteTextures(1, &SandRough);
		glDeleteTextures(1, &SandOcc);
		glDeleteTextures(1, &CliffColor);
		glDeleteTextures(1, &CliffNorm);
		glDeleteTextures(1, &CliffRough);
		glDeleteTextures(1, &CliffOcc);
		glDeleteTextures(1, &BottomColor);
		glDeleteTextures(1, &BottomNorm);
		glDeleteTextures(1, &BottomRough);
		glDeleteTextures(1, &BottomOcc);
	};

	virtual void UpdateRenderParam()
	{
		SetShaderTexture2D("grassColor", GrassColor, 0);
		SetShaderTexture2D("grassNorm", GrassNorm, 1);
		SetShaderTexture2D("grassRough", GrassRough, 2);
		SetShaderTexture2D("grassOcc", GrassOcc, 3);
		SetShaderTexture2D("sandColor", SandColor, 4);
		SetShaderTexture2D("sandNorm", SandNorm, 5);
		SetShaderTexture2D("sandRough", SandRough, 6);
		SetShaderTexture2D("sandOcc", SandOcc, 7);
		SetShaderTexture2D("cliffColor", CliffColor, 8);
		SetShaderTexture2D("cliffNorm", CliffNorm, 9);
		SetShaderTexture2D("cliffRough", CliffRough, 10);
		SetShaderTexture2D("cliffOcc", CliffOcc, 11);
		SetShaderTexture2D("bottomColor", BottomColor, 12);
		SetShaderTexture2D("bottomNorm", BottomNorm, 13);
		SetShaderTexture2D("bottomRough", BottomRough, 14);
		SetShaderTexture2D("bottomOcc", BottomOcc, 15);
	};

	void LoadTextures()
	{
		GrassColor = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"Terrain/Grass/GrassColor.jpg", true);
		GrassNorm = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"Terrain/Grass/GrassNormal.jpg", true);
		GrassRough = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"Terrain/Grass/GrassRough.jpg", true);
		GrassOcc = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"Terrain/Grass/GrassOcc.jpg", true);
		SandColor = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"Terrain/Sand/SandColor.png", true);
		SandNorm = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"Terrain/Sand/SandNormal.png", true);
		SandRough = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"Terrain/Sand/SandRough.jpg", true);
		SandOcc = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"Terrain/Sand/SandOcc.jpg", true);
		CliffColor = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"Terrain/Rock/RockColor.png", true);
		CliffNorm = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"Terrain/Rock/RockNormal.png", true);
		CliffRough = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"Terrain/Rock/RockRough.jpg", true);
		CliffOcc = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"Terrain/Rock/RockOcc.jpg", true);
		BottomColor = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"Terrain/Pebbles/PebblesColor.png", true);
		BottomNorm = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"Terrain/Pebbles/PebblesNormal.png", true);
		BottomRough = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"Terrain/Pebbles/PebblesRough.jpg", true);
		BottomOcc = SimpleImage::LoadTexture2DFromFile(TEXTUREDIR"Terrain/Pebbles/PebblesOcc.jpg", true);

		SetTextureRepeating(GrassColor, true);
		SetTextureRepeating(GrassNorm, true);
		SetTextureRepeating(GrassRough, true);
		SetTextureRepeating(GrassOcc, true);
		SetTextureRepeating(SandColor, true);
		SetTextureRepeating(SandNorm, true);
		SetTextureRepeating(SandRough, true);
		SetTextureRepeating(SandOcc, true);
		SetTextureRepeating(CliffColor, true);
		SetTextureRepeating(CliffNorm, true);
		SetTextureRepeating(CliffRough, true);
		SetTextureRepeating(CliffOcc, true);
		SetTextureRepeating(BottomColor, true);
		SetTextureRepeating(BottomNorm, true);
		SetTextureRepeating(BottomRough, true);
		SetTextureRepeating(BottomOcc, true);
	};

public:
	GLuint GrassColor = 0;
	GLuint GrassNorm = 0;
	GLuint GrassRough = 0;
	GLuint GrassOcc = 0;
	GLuint SandColor = 0;
	GLuint SandNorm = 0;
	GLuint SandRough = 0;
	GLuint SandOcc = 0;
	GLuint CliffColor = 0;
	GLuint CliffNorm = 0;
	GLuint CliffRough = 0;
	GLuint CliffOcc = 0;
	GLuint BottomColor = 0;
	GLuint BottomNorm = 0;
	GLuint BottomRough = 0;
	GLuint BottomOcc = 0;
};
