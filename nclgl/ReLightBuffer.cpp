#include "ReLightBuffer.h"

ReLightBuffer::ReLightBuffer(uint32_t InWidth, uint32_t InHeight)
	: ReFrameBuffer(InWidth,InHeight)
{
	GLenum ColourBuffers[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };

	GenerateScreenTexture(mDiffuseTex);
	GenerateScreenTexture(mSpecularTex);

	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mDiffuseTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, mSpecularTex, 0);
	glDrawBuffers(2, ColourBuffers);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

ReLightBuffer::~ReLightBuffer()
{
	glDeleteTextures(1, &mDiffuseTex);
	glDeleteTextures(1, &mSpecularTex);
}
