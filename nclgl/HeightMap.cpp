#include "HeightMap.h"
#include <iostream>
#include "SimpleImage.h"

HeightMap::HeightMap(const std::string& HeightFile, const std::string& ColourFile)
{
	int iWidth, iHeight, iChans;
	//unsigned char* HeightData = SOIL_load_image(HeightFile.c_str(), &iWidth, &iHeight, &iChans, 1);
	unsigned char* HeightData = SimpleImage::LoadImageFromFile(HeightFile.c_str(), &iWidth, &iHeight, &iChans, 1);

	if (!HeightData)
	{
		std::cout << "Heightmap can't load height file!\n";
		return;
	}

	numVertices = iWidth * iHeight;
	numIndices = (iWidth - 1) * (iHeight - 1) * 6;

	vertices.reset(new Vector3[numVertices]);
	textureCoords.reset(new Vector2[numVertices]);
	indices.reset(new GLuint[numIndices]);

	Vector3 vertexScale = Vector3(8.0f, 3.0f, 8.0f);
	Vector2 textureScale = Vector2(1 / 8.0f, 1 / 8.0f);

	for (int z = 0; z < iHeight; z++)
	{
		for (int x = 0; x < iWidth; x++)
		{
			int offset = (z * iWidth) + x;
			vertices[offset] = Vector3((float)(x - iWidth / 2), (float)(HeightData[offset] - 50), (float)(z - iHeight / 2)) * vertexScale;
			textureCoords[offset] = Vector2((float)x, (float)z) * textureScale;
		}
	}

	//SOIL_free_image_data(HeightData);
	SimpleImage::FreeImage(HeightData);

	int i = 0;

	for (int z = 0; z < iHeight - 1; z++)
	{
		for (int x = 0; x < iWidth - 1; x++)
		{
			int a = (z * (iWidth)) + x;
			int b = (z * (iWidth)) + (x + 1);
			int c = ((z + 1) * (iWidth)) + (x + 1);
			int d = ((z + 1) * (iWidth)) + x;

			indices[i++] = a;
			indices[i++] = c;
			indices[i++] = b;

			indices[i++] = c;
			indices[i++] = a;
			indices[i++] = d;
		}
	}


	if (!ColourFile.empty())
	{
		int ColourWidth, ColourHeight, ColourChans;
		unsigned char* ColourData = SimpleImage::LoadImageFromFile(ColourFile.c_str(), &ColourWidth, &ColourHeight, &ColourChans, 4);

		if (ColourData)
		{
			if (ColourWidth != iWidth || ColourHeight != iHeight)
			{
				std::cout << "Heightmap colour file should be the same size as height file!\n";
			}
			else
			{
				colours.reset(new Vector4[numVertices]);
				for (int z = 0; z < ColourHeight; z++)
				{
					for (int x = 0; x < ColourWidth; x++)
					{
						int ColourOffset = (z * ColourWidth) + x;
						int DataOffset = ColourOffset * 4;
						float NewColour[4] = {0};
						for (int c = 0; c < 4; c++)
						{
							NewColour[c] = (float)(ColourData[DataOffset + c]) / 255.0f;
						}
						colours[ColourOffset] = Vector4(NewColour[0], NewColour[1], NewColour[2], NewColour[3]);
						//*(colours + ColourOffset) = Vector4(1, 0, 0, 1);
					}
				}
			}
			SimpleImage::FreeImage(ColourData);
		}
	}
	
	GenerateNormals();
	GenerateTangents();

	BufferData();

	heightmapSize.x = vertexScale.x * (iWidth - 1);
	heightmapSize.y = vertexScale.y * 255.0f;
	heightmapSize.z = vertexScale.z * (iHeight - 1);
}
