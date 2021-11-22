#include "ReMaterial.h"

ReMaterial::ReMaterial(const std::string& InName)
	: mName(InName)
	, mShader(NULL)
{
}

bool ReMaterial::LoadShader(const std::string& vertex, const std::string& fragment,
	const std::string& geometry, const std::string& domain, const std::string& hull)
{
	std::string NewShaderFiles[ShaderStage::SHADER_MAX] = { vertex , fragment, geometry, domain, hull };
	for (Shader* TShader : Shader::allShaders)
	{
		bool IsSame = true;
		for (unsigned int i = 0; i < ShaderStage::SHADER_MAX; i++)
		{
			if (NewShaderFiles[i] != TShader->shaderFiles[i])
			{
				IsSame = false;
				break;
			}
		}
		if (IsSame)
		{
			mShader = TShader;
			return true;
		}
	}

	mShader = new Shader(vertex, fragment, geometry, domain, hull);
	return mShader->LoadSuccess();
}

void ReMaterial::DeleteAllShaders()
{
	for (Shader* TShader : Shader::allShaders)
	{
		delete TShader;
	}
	Shader::allShaders.clear();
	Shader::allShaders.shrink_to_fit();
}



void ReMaterial::SetTextureRepeating(GLuint TargetTex, bool Repeating)
{
	glBindTexture(GL_TEXTURE_2D, TargetTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Repeating ? GL_REPEAT : GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Repeating ? GL_REPEAT : GL_CLAMP);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ReMaterial::SetShaderBool(const std::string& ParamName, bool InValue) const
{
	if (!mShader) return;
	glUniform1ui(glGetUniformLocation(mShader->GetProgram(), ParamName.c_str()), InValue);
}

void ReMaterial::SetShaderInt(const std::string& ParamName, int InValue) const
{
	if (!mShader) return;
	glUniform1i(glGetUniformLocation(mShader->GetProgram(), ParamName.c_str()), InValue);
}

void ReMaterial::SetShaderUInt(const std::string& ParamName, unsigned int InValue) const
{
	if (!mShader) return;
	glUniform1ui(glGetUniformLocation(mShader->GetProgram(), ParamName.c_str()), InValue);
}

void ReMaterial::SetShaderFloat(const std::string& ParamName, float InValue) const
{
	if (!mShader) return;
	glUniform1f(glGetUniformLocation(mShader->GetProgram(), ParamName.c_str()), InValue);
}

void ReMaterial::SetShaderVector2(const std::string& ParamName, const Vector2& InVector) const
{
	if (!mShader) return;
	glUniform2fv(glGetUniformLocation(mShader->GetProgram(), ParamName.c_str()), 1, (float*)&InVector);
}

void ReMaterial::SetShaderVector3(const std::string& ParamName, const Vector3& InVector) const
{
	if (!mShader) return;
	glUniform3fv(glGetUniformLocation(mShader->GetProgram(), ParamName.c_str()), 1, (float*)&InVector);
}

void ReMaterial::SetShaderVector4(const std::string& ParamName, const Vector4& InVector) const
{
	if (!mShader) return;
	glUniform4fv(glGetUniformLocation(mShader->GetProgram(), ParamName.c_str()), 1, (float*)&InVector);
}

void ReMaterial::SetShaderMatrix4(const std::string& ParamName, const Matrix4& InMatrix) const
{
	if (!mShader) return;
	glUniformMatrix4fv(glGetUniformLocation(mShader->GetProgram(), ParamName.c_str()), 1, false, InMatrix.values);
}

void ReMaterial::SetShaderTexture2D(const std::string& ParamName, GLuint InTexture, GLuint InTexIndex) const
{
	if (!mShader) return;
	glUniform1i(glGetUniformLocation(mShader->GetProgram(), ParamName.c_str()), InTexIndex);
	glActiveTexture(GL_TEXTURE0 + InTexIndex);
	glBindTexture(GL_TEXTURE_2D, InTexture);

}
