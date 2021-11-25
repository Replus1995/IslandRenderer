#include "RePointLightComponent.h"

RePointLightComponent::RePointLightComponent(const RePrimitivePtr& InPrim, const Vector4& InColour, const float InRadius)
	: mLightPrim(InPrim)
	, mLightColour(InColour)
	, mLightRadius(InRadius)
{

}

RePointLightComponent::~RePointLightComponent()
{
}

void RePointLightComponent::Draw()
{
	glUniform3fv(glGetUniformLocation(GetShader()->GetProgram(), "lightPos"), 1, (float*)&GetPosition());
	glUniform4fv(glGetUniformLocation(GetShader()->GetProgram(), "lightColour"), 1, (float*)&mLightColour);
	glUniform1f(glGetUniformLocation(GetShader()->GetProgram(), "lightRadius"),mLightRadius);

	mLightPrim->DrawMesh();
}

ReMaterialPtr RePointLightComponent::GetMaterial() const
{
	return mLightPrim ? mLightPrim->GetMaterial() : nullptr;
}

Shader* RePointLightComponent::GetShader() const
{
	return mLightPrim ? mLightPrim->GetMaterial()->GetShader() : nullptr;
}
