#include "GLTFPrimitiveMesh.h"
#include <iostream>
#include <SOIL/SOIL.h>

float GLTFPrimitiveMesh::GetBufferFloat(const unsigned char*& CurBufferPos, int InComponentType)
{
    float tValue = 0.0f;
    switch (InComponentType)
    {
    /*case TINYGLTF_COMPONENT_TYPE_BYTE:
        tValue = *((char*)CurBufferPos);
        CurBufferPos += sizeof(char);
        break;*/
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
        tValue = float(*CurBufferPos) / 255.0f;
        CurBufferPos += sizeof(unsigned char);
        break;
    /*case TINYGLTF_COMPONENT_TYPE_SHORT:
        tValue = *((short*)CurBufferPos);
        CurBufferPos += sizeof(short);
        break;*/
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
        tValue = float(*((unsigned short*)CurBufferPos)) / 65535.0f;
        CurBufferPos += sizeof(unsigned short);
        break;
    /*case TINYGLTF_COMPONENT_TYPE_INT:
        tValue = *((int*)CurBufferPos);
        CurBufferPos += sizeof(int);
        break;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
        tValue = *((unsigned int*)CurBufferPos);
        CurBufferPos += sizeof(unsigned int);
        break;*/
    case TINYGLTF_COMPONENT_TYPE_FLOAT:
        tValue = *((float*)CurBufferPos);
        CurBufferPos += sizeof(float);
        break;
    /*case TINYGLTF_COMPONENT_TYPE_DOUBLE:
        tValue = *((double*)CurBufferPos);
        CurBufferPos += sizeof(double);
        break;*/
    default:
        assert(0);
        break;
    }

    return tValue;
}


unsigned int GLTFPrimitiveMesh::GetBufferUInt(const unsigned char*& CurBufferPos, int InComponentType)
{
    unsigned int tValue = 0.0f;
    switch (InComponentType)
    {
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
        tValue = *CurBufferPos;
        CurBufferPos += sizeof(unsigned char);
        break;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
        tValue = *((unsigned short*)CurBufferPos);
        CurBufferPos += sizeof(unsigned short);
        break;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
        tValue = *((unsigned int*)CurBufferPos);
        CurBufferPos += sizeof(unsigned int);
        break;
    default:
        assert(0);
        break;
    }

    return tValue;
}

bool GLTFPrimitiveMesh::ReadVector2FromAccessor(std::unique_ptr<Vector2[]>& OutVectors, const tinygltf::Accessor& InAccessor, tinygltf::Model& InModel)
{
    if (InAccessor.type != TINYGLTF_TYPE_VEC2) return false;
    const tinygltf::BufferView& tBufferView = InModel.bufferViews[InAccessor.bufferView];
    const tinygltf::Buffer& tBuffer = InModel.buffers[tBufferView.buffer];

    const unsigned char* BufferStart = tBuffer.data.data() + tBufferView.byteOffset + InAccessor.byteOffset;
    OutVectors.reset(new Vector2[InAccessor.count]);

    int tByteStride = InAccessor.ByteStride(tBufferView);

    for (size_t i = 0; i < InAccessor.count; i++)
    {
        Vector2 tVector;
        const unsigned char* CurBufferPos = BufferStart + tByteStride * i;
        tVector.x = GetBufferFloat(CurBufferPos, InAccessor.componentType);
        tVector.y = GetBufferFloat(CurBufferPos, InAccessor.componentType);
        OutVectors[i] = tVector;
    }
    return true;
}

bool GLTFPrimitiveMesh::ReadVector3FromAccessor(std::unique_ptr<Vector3[]>& OutVectors, const tinygltf::Accessor& InAccessor, tinygltf::Model& InModel)
{
    if (InAccessor.type != TINYGLTF_TYPE_VEC3) return false;
    const tinygltf::BufferView& tBufferView = InModel.bufferViews[InAccessor.bufferView];
    const tinygltf::Buffer& tBuffer = InModel.buffers[tBufferView.buffer];
    
    const unsigned char* BufferStart = tBuffer.data.data() + tBufferView.byteOffset + InAccessor.byteOffset;
    OutVectors.reset(new Vector3[InAccessor.count]);
    
    int tByteStride = InAccessor.ByteStride(tBufferView);

    for (size_t i = 0; i < InAccessor.count; i++)
    {
        Vector3 tVector;
        const unsigned char* CurBufferPos = BufferStart + tByteStride * i;
        tVector.x = GetBufferFloat(CurBufferPos, InAccessor.componentType);
        tVector.y = GetBufferFloat(CurBufferPos, InAccessor.componentType);
        tVector.z = GetBufferFloat(CurBufferPos, InAccessor.componentType);
        OutVectors[i] = tVector;
    }
    return true;
}

bool GLTFPrimitiveMesh::ReadVector4FromAccessor(std::unique_ptr<Vector4[]>& OutVectors, const tinygltf::Accessor& InAccessor, tinygltf::Model& InModel)
{
    if (InAccessor.type != TINYGLTF_TYPE_VEC3 && InAccessor.type != TINYGLTF_TYPE_VEC4) return false;
    const tinygltf::BufferView& tBufferView = InModel.bufferViews[InAccessor.bufferView];
    const tinygltf::Buffer& tBuffer = InModel.buffers[tBufferView.buffer];

    const unsigned char* BufferStart = tBuffer.data.data() + tBufferView.byteOffset + InAccessor.byteOffset;
    OutVectors.reset(new Vector4[InAccessor.count]);

    int tByteStride = InAccessor.ByteStride(tBufferView);

    for (size_t i = 0; i < InAccessor.count; i++)
    {
        Vector4 tVector;
        const unsigned char* CurBufferPos = BufferStart + tByteStride * i;
        tVector.x = GetBufferFloat(CurBufferPos, InAccessor.componentType);
        tVector.y = GetBufferFloat(CurBufferPos, InAccessor.componentType);
        tVector.z = GetBufferFloat(CurBufferPos, InAccessor.componentType);
        if (InAccessor.type == TINYGLTF_TYPE_VEC4)
            tVector.w = GetBufferFloat(CurBufferPos, InAccessor.componentType);
        else
            tVector.w = 1.0f;
        OutVectors[i] = tVector;
    }
    return true;
}

bool GLTFPrimitiveMesh::ReadUIntFromAccessor(std::unique_ptr<unsigned int[]>& OutUInts, const tinygltf::Accessor& InAccessor, tinygltf::Model& InModel)
{
    if (InAccessor.type != TINYGLTF_TYPE_SCALAR) return false;
    const tinygltf::BufferView& tBufferView = InModel.bufferViews[InAccessor.bufferView];
    const tinygltf::Buffer& tBuffer = InModel.buffers[tBufferView.buffer];

    const unsigned char* BufferStart = tBuffer.data.data() + tBufferView.byteOffset + InAccessor.byteOffset;
    OutUInts.reset(new unsigned int[InAccessor.count]);

    int tByteStride = InAccessor.ByteStride(tBufferView);

    for (size_t i = 0; i < InAccessor.count; i++)
    {
        const unsigned char* CurBufferPos = BufferStart + tByteStride * i;
        OutUInts[i] = GetBufferUInt(CurBufferPos, InAccessor.componentType);
    }
    return true;
}


void GLTFPrimitiveMesh::LoadPrimitive(const tinygltf::Primitive& InPrimitive, tinygltf::Model& InModel)
{
    for (auto it = InPrimitive.attributes.begin(); it != InPrimitive.attributes.end(); it++)
    {
        if (it->second < 0) continue;

        const tinygltf::Accessor& tAccessor = InModel.accessors[it->second];

        if (it->first.compare("POSITION") == 0)
        {
            ReadVector3FromAccessor(vertices, tAccessor, InModel);
            numVertices = tAccessor.count;
        }
        else if (it->first.compare("NORMAL") == 0)
        {
            ReadVector3FromAccessor(normals, tAccessor, InModel);
        }
        else if (it->first.compare("TANGENT") == 0)
        {
            ReadVector4FromAccessor(tangents, tAccessor, InModel);
        }
        else if (it->first.compare("TEXCOORD_0") == 0)
        {
            ReadVector2FromAccessor(textureCoords, tAccessor, InModel);
        }
        else if (it->first.compare("COLOR_0") == 0)
        {
            ReadVector4FromAccessor(colours, tAccessor, InModel);
        }
    }

    if (InPrimitive.indices >= 0)
    {
        const tinygltf::Accessor& tAccessor = InModel.accessors[InPrimitive.indices];
        ReadUIntFromAccessor(indices, tAccessor, InModel);
        numIndices = tAccessor.count;
    }

    if (!colours)
    {
        colours.reset(new Vector4[numVertices]);
        for (size_t i = 0; i < numVertices; i++)
        {
            colours[i] = Vector4(1, 1, 1, 1);
        }
    }

    if(!normals) GenerateNormals();
    if(!tangents) GenerateTangents();

    BufferData();

    type = InPrimitive.mode;
    mMaterialIndex = InPrimitive.material;
}
