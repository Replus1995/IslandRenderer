#include "SimpleImage.h"
#include <tinygltf/stb_image.h>

unsigned char* SimpleImage::LoadImageFromFile(const std::string& file, int* width, int* height, int* channels, int desired_channels)
{
	unsigned char* data = nullptr;
	FILE* f = fopen(file.c_str(), "rb");
	if (f)
	{
		data = stbi_load_from_file(f, width, height, channels, desired_channels);
		fclose(f);
	}

	return data;
}

void SimpleImage::FreeImage(unsigned char* data)
{
	stbi_image_free(data);
}

GLuint SimpleImage::LoadTexture2DFromFile(const std::string& file, bool mipmap)
{
    int width = 0, height = 0, channels = 0;

    unsigned char* image = LoadImageFromFile(file, &width, &height, &channels, 0);

    if (!image) return 0;

    int iformat = 0, texformat = 0;
    switch (channels)
    {
    case 1:
        iformat = GL_R8;
        texformat = GL_R;
        break;
    case 2:
        iformat = GL_RG8;
        texformat = GL_RG;
        break;
    case 3:
        iformat = GL_RGB8;
        texformat = GL_RGB;
        break;
    case 4:
        iformat = GL_RGBA8;
        texformat = GL_RGBA;
        break;
    default:
        break;
    }

    GLuint tex = 0;

    if (texformat)
    {
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, iformat, width, height, 0, texformat, GL_UNSIGNED_BYTE, image);
        if(mipmap) glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    FreeImage(image);

	return tex;
}

GLuint SimpleImage::LoadTextureCubeFromFile(
    const std::string& negative_x, const std::string& positive_x,
    const std::string& negative_y, const std::string& positive_y,
    const std::string& negative_z, const std::string& positive_z,
    bool mipmap)
{
    int width = 0, height = 0, channels = 0;
    int nwidth = 0, nheight = 0, nchannels = 0;

    unsigned char* images[6] = {0};

    {
        images[0] = LoadImageFromFile(negative_x, &width, &height, &channels, 0);
        if (!images[0]) return 0;
        images[1] = LoadImageFromFile(positive_x, &nwidth, &nheight, &nchannels, 0);
        if (!images[1] || (nwidth != width || nheight != height || nchannels != channels))
        {
            FreeImages(images, 1);
            return 0;
        }
        images[2] = LoadImageFromFile(negative_y, &nwidth, &nheight, &nchannels, 0);
        if (!images[2] || (nwidth != width || nheight != height || nchannels != channels))
        {
            FreeImages(images, 2);
            return 0;
        }
        images[3] = LoadImageFromFile(positive_y, &nwidth, &nheight, &nchannels, 0);
        if (!images[3] || (nwidth != width || nheight != height || nchannels != channels))
        {
            FreeImages(images, 3);
            return 0;
        }
        images[4] = LoadImageFromFile(negative_z, &nwidth, &nheight, &nchannels, 0);
        if (!images[4] || (nwidth != width || nheight != height || nchannels != channels))
        {
            FreeImages(images, 4);
            return 0;
        }
        images[5] = LoadImageFromFile(positive_z, &nwidth, &nheight, &nchannels, 0);
        if (!images[5] || (nwidth != width || nheight != height || nchannels != channels))
        {
            FreeImages(images, 5);
            return 0;
        }
    }
    
    int iformat = 0, texformat = 0;
    switch (channels)
    {
    case 1:
        iformat = GL_R8;
        texformat = GL_R;
        break;
    case 2:
        iformat = GL_RG8;
        texformat = GL_RG;
        break;
    case 3:
        iformat = GL_RGB8;
        texformat = GL_RGB;
        break;
    case 4:
        iformat = GL_RGBA8;
        texformat = GL_RGBA;
        break;
    default:
        break;
    }

    GLuint cubetex = 0;

    if (texformat)
    {
        glGenTextures(1, &cubetex);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubetex);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, mipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, mipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, mipmap);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, iformat, width, height, 0, texformat, GL_UNSIGNED_BYTE, images[0]);//-x
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, iformat, width, height, 0, texformat, GL_UNSIGNED_BYTE, images[1]);//x
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, iformat, width, height, 0, texformat, GL_UNSIGNED_BYTE, images[2]);//-y
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, iformat, width, height, 0, texformat, GL_UNSIGNED_BYTE, images[3]);//y
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, iformat, width, height, 0, texformat, GL_UNSIGNED_BYTE, images[4]);//-z
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, iformat, width, height, 0, texformat, GL_UNSIGNED_BYTE, images[5]);//z

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    FreeImages(images, 6);

    return cubetex;
}

void SimpleImage::FreeImages(unsigned char** images, unsigned int num)
{
    for (unsigned int i = 0; i < num; i++)
    {
        if(images[i]) FreeImage(images[i]);
    }
}
