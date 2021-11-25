#pragma once
#include "ReFrameBuffer.h"
#include "ReSceneBuffer.h"

class ReSingleBuffer : public ReFrameBuffer
{
public:
	ReSingleBuffer(uint32_t InWidth, uint32_t InHeight);
	~ReSingleBuffer();

	void WirteDepth(ReSceneBuffer* InSceneBuffer);

	GLuint mScreenTex;
	GLuint mDepthTex;
};
