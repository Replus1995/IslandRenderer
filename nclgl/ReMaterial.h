#pragma once
#include <memory>
#include "Shader.h"

class ReMaterialParam
{
public:
	ReMaterialParam() {};
	virtual ~ReMaterialParam() {};

	static void SetTextureRepeating(GLuint TargetTex, bool Repeating) 
	{
		glBindTexture(GL_TEXTURE_2D, TargetTex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Repeating ? GL_REPEAT : GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Repeating ? GL_REPEAT : GL_CLAMP);
		glBindTexture(GL_TEXTURE_2D, 0);
	};
};

typedef std::shared_ptr<ReMaterialParam> ReMaterialParamPtr;

class ReMaterial
{
public:
	ReMaterial(const std::string& InName);
	virtual ~ReMaterial() {};

	const std::string& GetName() { return mName; };

	bool LoadShader(const std::string& vertex, const std::string& fragment,
		const std::string& geometry = "", const std::string& domain = "", const std::string& hull = "");
	Shader* GetShader() { return mShader; };
	
	void SetShaderTexture2D(const std::string& ParamName, GLuint InTexture, GLuint InTexIndex) const;
	void SetShaderVector2(const std::string& ParamName, const Vector2& InVector) const;
	void SetShaderVector3(const std::string& ParamName, const Vector3& InVector) const;
	void SetShaderMatrix(const std::string& ParamName, const Matrix4& InMatrix) const;

	virtual void SetMaterialParam(const ReMaterialParamPtr& InParam) {};

	static void DeleteAllShaders();

protected:
	std::string mName;
	Shader* mShader;
};

typedef std::shared_ptr<ReMaterial> ReMaterialPtr;
