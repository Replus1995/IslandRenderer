#include "ReSceneBuffer.h"

ReSceneBuffer::ReSceneBuffer(uint32_t InWidth, uint32_t InHeight)
	: ReFrameBuffer(InWidth, InHeight)
{
	GLenum ColourBuffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };

	GenerateScreenTexture(mDepthTex, true);
	GenerateScreenTexture(mColourTex);
	GenerateScreenTexture(mNormalTex);
	GenerateScreenTexture(mEmissiveTex);
	GenerateScreenTexture(mMetallicRoughnessTex);

	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColourTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, mNormalTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, mEmissiveTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, mMetallicRoughnessTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthTex, 0);
	glDrawBuffers(4, ColourBuffers);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

ReSceneBuffer::~ReSceneBuffer()
{
	glDeleteTextures(1, &mColourTex);
	glDeleteTextures(1, &mNormalTex);
	glDeleteTextures(1, &mEmissiveTex);
	glDeleteTextures(1, &mMetallicRoughnessTex);
	glDeleteTextures(1, &mDepthTex);
}
