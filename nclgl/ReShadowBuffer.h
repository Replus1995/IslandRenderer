#pragma once
#include "ReFrameBuffer.h"


class ReShadowBuffer : public ReFrameBuffer
{
public:
	ReShadowBuffer(uint32_t InWidth, uint32_t InHeight);
	~ReShadowBuffer();

	GLuint mDepthTex;
};