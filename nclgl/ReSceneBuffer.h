#pragma once
#include "ReFrameBuffer.h"

class ReSceneBuffer : public ReFrameBuffer
{
public:
	ReSceneBuffer(uint32_t InWidth, uint32_t InHeight);
	~ReSceneBuffer();

	GLuint mColourTex;
	GLuint mNormalTex;
	GLuint mEmissiveTex;
	GLuint mDepthTex;
};