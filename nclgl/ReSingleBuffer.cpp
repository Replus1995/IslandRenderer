#include "ReSingleBuffer.h"

ReSingleBuffer::ReSingleBuffer(uint32_t InWidth, uint32_t InHeight)
	: ReFrameBuffer(InWidth, InHeight)
{
	GenerateScreenTexture(mScreenTex);
	GenerateScreenTexture(mDepthTex, true);

	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mScreenTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthTex, 0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

ReSingleBuffer::~ReSingleBuffer()
{
	glDeleteTextures(1, &mScreenTex);
}

void ReSingleBuffer::WirteDepth(ReSceneBuffer* InSceneBuffer)
{
	glBlitNamedFramebuffer(InSceneBuffer->mFBO, mFBO, 0, 0, mWidth, mHeight, 0, 0, mWidth, mHeight, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
}


