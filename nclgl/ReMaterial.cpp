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

void ReMaterial::SetShaderTexture2D(const std::string& ParamName, GLuint InTexture, GLuint InTexIndex)
{
	if (!mShader) return;
	glUniform1i(glGetUniformLocation(mShader->GetProgram(), ParamName.c_str()), InTexIndex);
	glActiveTexture(GL_TEXTURE0 + InTexIndex);
	glBindTexture(GL_TEXTURE_2D, InTexture);

}

void ReMaterial::SetShaderVector3(const std::string& ParamName, const Vector3& InVector)
{
	if (!mShader) return;
	glUniform3fv(glGetUniformLocation(mShader->GetProgram(), ParamName.c_str()), 1, (float*)&InVector);
}

void ReMaterial::SetShaderMatrix(const std::string& ParamName, const Matrix4& InMatrix)
{
	if (!mShader) return;
	glUniformMatrix4fv(glGetUniformLocation(mShader->GetProgram(), ParamName.c_str()), 1, false, InMatrix.values);
}
