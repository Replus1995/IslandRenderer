#pragma once
#include "OGLRenderer.h"


class ReFrameBuffer
{
public:
	ReFrameBuffer(uint32_t InWidth, uint32_t InHeight) 
		: mWidth(InWidth)
		, mHeight(InHeight)
	{
		glGenFramebuffers(1, &mFBO);
	};
	virtual ~ReFrameBuffer() 
	{
		glDeleteFramebuffers(1, &mFBO);
	};

	void Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
	};

	void Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	};

protected:
	void GenerateScreenTexture(GLuint& Texture, bool bDepth = false)
	{
		glGenTextures(1, &Texture);
		glBindTexture(GL_TEXTURE_2D, Texture);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		GLuint format = bDepth ? GL_DEPTH_COMPONENT24 : GL_RGBA8;
		GLuint type = bDepth ? GL_DEPTH_COMPONENT : GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, type, GL_UNSIGNED_BYTE, NULL);

		glBindTexture(GL_TEXTURE_2D, 0);
	};

	void GenerateShadowDepthTexture(GLuint& Texture)
	{
		glGenTextures(1, &Texture);
		glBindTexture(GL_TEXTURE_2D, Texture);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, mWidth, mHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

protected:
	uint32_t mWidth;
	uint32_t mHeight;
	GLuint mFBO;
};