#pragma once
#include "ReFrameBuffer.h"

class ReLightBuffer : public ReFrameBuffer
{
public:
	ReLightBuffer(uint32_t InWidth, uint32_t InHeight);
	~ReLightBuffer();

	GLuint mDiffuseTex;
	GLuint mSpecularTex;
};
