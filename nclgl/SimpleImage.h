#pragma once
#include <string>
#include <glad/glad.h>

class SimpleImage
{
public:

	static unsigned char* LoadImageFromFile(const std::string& file, int* width, int* height, int* channels, int desired_channels);
	static void FreeImage(unsigned char* data);
	static GLuint LoadTexture2DFromFile(const std::string& file, bool mipmap);
	static GLuint LoadTextureCubeFromFile(const std::string& negative_x, const std::string& positive_x,
										  const std::string& negative_y, const std::string& positive_y, 
										  const std::string& negative_z, const std::string& positive_z, 
										  bool mipmap);
protected:
	static void FreeImages(unsigned char** images, unsigned int num);
};