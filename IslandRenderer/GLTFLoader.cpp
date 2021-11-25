#include "GLTFLoader.h"
#include <iostream>
#include "../nclgl/RePrimitive.h"
#include "GLTFPrimitiveMesh.h"
#include "Materials/MaterialCollection.h"

bool GLTFLoader::LoadFile(const std::string& FileName, bool Instanced)
{
    tinygltf::TinyGLTF tLoader;
    tinygltf::Model tModel;
    std::string ErrStr;
    std::string WarnStr;
    std::string Extension = GetFilePathExtension(FileName);

    bool LoadRes = true;
    if (Extension == "gltf")
        LoadRes = tLoader.LoadASCIIFromFile(&tModel, &ErrStr, &WarnStr, FileName);
    else if (Extension == "glb")
        LoadRes = tLoader.LoadBinaryFromFile(&tModel, &ErrStr, &WarnStr, FileName);
    else
    {
        std::cout << "Unkown file format: " << Extension << std::endl;
        return false;
    }

    if (!LoadRes)
    {
        std::cout << "GLTF load error: " << ErrStr << std::endl;
        return false;
    }
    if (!WarnStr.empty())
        std::cout << "GLTF load warning: " << WarnStr << std::endl;

    std::vector<std::shared_ptr<GLTFMat>> GLTFMaterials;
    LoadGLTFMaterials(GLTFMaterials, tModel, Instanced);

    for (const tinygltf::Mesh tMesh : tModel.meshes)
    {
        GLTFMesh NewMesh;
        for (const tinygltf::Primitive& tPrimitive : tMesh.primitives)
        {
            GLTFPrimitiveMeshPtr tPrimitiveMesh(new GLTFPrimitiveMesh);
            tPrimitiveMesh->LoadPrimitive(tPrimitive, tModel);
            ReMaterialPtr NewMaterial;
            bool bTransparent = false;
            if (tPrimitiveMesh->mMaterialIndex >= 0 && tPrimitiveMesh->mMaterialIndex < GLTFMaterials.size())
            {
                NewMaterial = GLTFMaterials[tPrimitiveMesh->mMaterialIndex];
                bTransparent = GLTFMaterials[tPrimitiveMesh->mMaterialIndex]->mAlphaMode == GLTF_AM_BLEND;
            }
            else
            {
                NewMaterial = ReMaterialPtr(new PlainMat());
            }
            RePrimitivePtr NewPrimitive(new RePrimitive(tPrimitiveMesh, NewMaterial, bTransparent, Instanced));
            NewPrimitive->SetBoundingRadius(tPrimitiveMesh->CalculateMaxRadius() * 1.5);
            NewMesh.mPrimitives.push_back(NewPrimitive);
        }
        mMeshes.push_back(NewMesh);
    }

    return true;
}

std::string GLTFLoader::GetFilePathExtension(const std::string& FileName)
{
    if (FileName.find_last_of(".") != std::string::npos)
        return FileName.substr(FileName.find_last_of(".") + 1);
    return "";
}

unsigned int GLTFLoader::LoadGLTFTexture(int InTextureIndex, const tinygltf::Model& InModel)
{
    if (InTextureIndex < 0 || InTextureIndex >= InModel.textures.size()) return 0;
    const tinygltf::Texture& tTexture = InModel.textures[InTextureIndex];
    if (tTexture.source < 0 || tTexture.source >= InModel.images.size()) return 0;
    const tinygltf::Image& tImage = InModel.images[tTexture.source];
    if (tImage.image.size() == 0) return 0;


    unsigned int tImageFormat = 0, tTexFormat = 0;
    switch (tImage.component)
    {
    case 1:
        tImageFormat = GL_R8;
        tTexFormat = GL_R;
        break;
    case 2:
        tImageFormat = GL_RG8;
        tTexFormat = GL_RG;
        break;
    case 3:
        tImageFormat = GL_RGB8;
        tTexFormat = GL_RGB;
        break;
    case 4:
        tImageFormat = GL_RGBA8;
        tTexFormat = GL_RGBA;
        break;
    default:
        assert(0);
        break;
    }


    GLuint NewTexture = 0;
    glGenTextures(1, &NewTexture);
    glBindTexture(GL_TEXTURE_2D, NewTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, tImageFormat, tImage.width, tImage.height, 0, tTexFormat, GL_UNSIGNED_BYTE, tImage.image.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    return NewTexture;
}

void GLTFLoader::LoadGLTFMaterials(std::vector<std::shared_ptr<GLTFMat>>& OutMaterials, const tinygltf::Model& InModel, bool Instanced)
{
    for (const tinygltf::Material& tMaterial : InModel.materials)
    {
        GLTFMatPtr NewMaterial;
        if (Instanced) 
            NewMaterial.reset(new InstancedGLTFMat(tMaterial.name));
        else 
            NewMaterial.reset(new GLTFMat(tMaterial.name));

        {
            const tinygltf::PbrMetallicRoughness& tPbrParam = tMaterial.pbrMetallicRoughness;
            NewMaterial->mBaseColor = Vector4(tPbrParam.baseColorFactor[0],
                                              tPbrParam.baseColorFactor[1],
                                              tPbrParam.baseColorFactor[2],
                                              tPbrParam.baseColorFactor[3]);
            if (tPbrParam.baseColorTexture.texCoord == 0)
            {
                NewMaterial->mBaseColorTex = LoadGLTFTexture(tPbrParam.baseColorTexture.index, InModel);
            }
            NewMaterial->mMetallic = tPbrParam.metallicFactor;
            NewMaterial->mRoughness = tPbrParam.roughnessFactor;
            if (tPbrParam.metallicRoughnessTexture.texCoord == 0)
            {
                NewMaterial->mMetallicRoughnessTex = LoadGLTFTexture(tPbrParam.metallicRoughnessTexture.index, InModel);
            }
        }
        if (tMaterial.normalTexture.texCoord == 0)
        {
            NewMaterial->mNormalTex = LoadGLTFTexture(tMaterial.normalTexture.index, InModel);
            NewMaterial->mNormalScale = tMaterial.normalTexture.scale;
        }
        if (tMaterial.occlusionTexture.texCoord == 0)
        {
            NewMaterial->mOcclutionTex = LoadGLTFTexture(tMaterial.occlusionTexture.index, InModel);
            NewMaterial->mOcclutionStrength = tMaterial.occlusionTexture.strength;
        }
        if (tMaterial.emissiveTexture.texCoord == 0)
        {
            NewMaterial->mEmissiveTex = LoadGLTFTexture(tMaterial.emissiveTexture.index, InModel);
            NewMaterial->mEmissiveFactor = Vector3(tMaterial.emissiveFactor[0], tMaterial.emissiveFactor[1], tMaterial.emissiveFactor[2]);
        }

        if (tMaterial.alphaMode == "OPAQUE")
        {
            NewMaterial->mAlphaMode = GLTF_AM_OPAQUE;
        }   
        else if (tMaterial.alphaMode == "MASK")
        {
            NewMaterial->mAlphaMode = GLTF_AM_MASK;
            NewMaterial->mAlphaCutoff = tMaterial.alphaCutoff;
        }
        else if (tMaterial.alphaMode == "BLEND")
        {
            NewMaterial->mAlphaMode = GLTF_AM_BLEND;
        }

        OutMaterials.push_back(NewMaterial);
    }
}
