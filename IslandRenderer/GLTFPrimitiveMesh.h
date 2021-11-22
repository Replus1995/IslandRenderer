#pragma once
#include "../nclgl/Mesh.h"
#include <tinygltf/tiny_gltf.h>

class GLTFPrimitiveMesh : public Mesh
{
public:
	GLTFPrimitiveMesh() {};
	~GLTFPrimitiveMesh() {};

	void LoadPrimitive(const tinygltf::Primitive& InPrimitive, tinygltf::Model& InModel);

private:
	float GetBufferFloat(const unsigned char*& CurBufferPos, int InComponentType);
	unsigned int GetBufferUInt(const unsigned char*& CurBufferPos, int InComponentType);

	bool ReadVector2FromAccessor(std::unique_ptr<Vector2[]>& OutVectors, const tinygltf::Accessor& InAccessor, tinygltf::Model& InModel);
	bool ReadVector3FromAccessor(std::unique_ptr<Vector3[]>& OutVectors, const tinygltf::Accessor& InAccessor, tinygltf::Model& InModel);
	bool ReadVector4FromAccessor(std::unique_ptr<Vector4[]>& OutVectors, const tinygltf::Accessor& InAccessor, tinygltf::Model& InModel);
	bool ReadUIntFromAccessor(std::unique_ptr<unsigned int[]>& OutUInts, const tinygltf::Accessor& InAccessor, tinygltf::Model& InModel);

public:
	int mMaterialIndex = -1;
};

typedef std::shared_ptr<GLTFPrimitiveMesh> GLTFPrimitiveMeshPtr;