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

	bool LoadFile(const std::string& FileName, bool Instanced = false);

protected:
	static std::string GetFilePathExtension(const std::string& FileName);

	unsigned int LoadGLTFTexture(int InTextureIndex, const tinygltf::Model& InModel);
	void LoadGLTFMaterials(std::vector<std::shared_ptr<GLTFMat>>& OutMaterials, const tinygltf::Model& InModel, bool Instanced);

public:
	std::vector<GLTFMesh> mMeshes;
};