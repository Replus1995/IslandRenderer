#pragma once
#include <memory>
#include "Shader.h"
#include "SimpleImage.h"

class ReMaterial
{
public:
	ReMaterial(const std::string& InName);
	virtual ~ReMaterial() {};

	const std::string& GetName() { return mName; };

	bool LoadShader(const std::string& vertex, const std::string& fragment,
		const std::string& geometry = "", const std::string& domain = "", const std::string& hull = "");
	Shader* GetShader() { return mShader; };
	
	static void SetTextureRepeating(GLuint TargetTex, bool Repeating);

	void SetShaderBool(const std::string& ParamName, bool InValue) const;
	void SetShaderInt(const std::string& ParamName, int InValue) const;
	void SetShaderUInt(const std::string& ParamName, unsigned int InValue) const;
	void SetShaderFloat(const std::string& ParamName, float InValue) const;
	void SetShaderVector2(const std::string& ParamName, const Vector2& InVector) const;
	void SetShaderVector3(const std::string& ParamName, const Vector3& InVector) const;
	void SetShaderVector4(const std::string& ParamName, const Vector4& InVector) const;
	void SetShaderMatrix4(const std::string& ParamName, const Matrix4& InMatrix) const;
	void SetShaderTexture2D(const std::string& ParamName, GLuint InTexture, GLuint InTexIndex) const;

	virtual void UpdateRenderParam() {};

	static void DeleteAllShaders();

protected:
	std::string mName;
	Shader* mShader;
};

typedef std::shared_ptr<ReMaterial> ReMaterialPtr;
