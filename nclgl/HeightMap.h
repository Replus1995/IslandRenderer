#pragma once
#include <string>
#include "Mesh.h"

class HeightMap : public Mesh
{
public:
	HeightMap(const std::string& HeightFile, const std::string& ColourFile);
	~HeightMap(void) {};

	Vector3 GetHeightmapSize() const { return heightmapSize; };

protected:
	Vector3 heightmapSize;
};
