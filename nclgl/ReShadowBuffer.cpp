#include "ReShadowBuffer.h"

ReShadowBuffer::ReShadowBuffer(uint32_t InWidth, uint32_t InHeight)
	: ReFrameBuffer(InWidth, InHeight)
{
	GenerateShadowDepthTexture(mDepthTex);

	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthTex, 0);
	glDrawBuffer(GL_NONE);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

ReShadowBuffer::~ReShadowBuffer()
{
	glDeleteTextures(1, &mDepthTex);
}
