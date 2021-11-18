#include "ReSceneBuffer.h"

ReSceneBuffer::ReSceneBuffer(uint32_t InWidth, uint32_t InHeight)
	: ReFrameBuffer(InWidth, InHeight)
{
	GLenum ColourBuffers[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };

	GenerateScreenTexture(mDepthTex, true);
	GenerateScreenTexture(mColourTex);
	GenerateScreenTexture(mNormalTex);

	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColourTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, mNormalTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthTex, 0);
	glDrawBuffers(2, ColourBuffers);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

ReSceneBuffer::~ReSceneBuffer()
{
	glDeleteTextures(1, &mColourTex);
	glDeleteTextures(1, &mNormalTex);
	glDeleteTextures(1, &mDepthTex);
}
