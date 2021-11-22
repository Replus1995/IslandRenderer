#pragma once
#include <memory>
#include <vector>
#include <tinygltf/tiny_gltf.h>

class RePrimitive;
class GLTFMat;

struct GLTFMesh
{
	std::vector<std::shared_ptr<RePrimitive>> mPrimitives;
};

class GLTFLoader
{
public:
	GLTFLoader() {};
	~GLTFLoader() {};

	bool LoadFile(const std::string& FileName);

protected:
	static std::string GetFilePathExtension(const std::string& FileName);
	static bool LoadTextureData(tinygltf::Image* image, const int image_idx, std::string* err,
		std::string* warn, int req_width, int req_height,
		const unsigned char* bytes, int size, void* userdata);

	unsigned int LoadGLTFTexture(int InTextureIndex, const tinygltf::Model& InModel);
	void LoadGLTFMaterials(std::vector<std::shared_ptr<GLTFMat>>& OutMaterials, const tinygltf::Model& InModel);

public:
	std::vector<GLTFMesh> mMeshes;
};