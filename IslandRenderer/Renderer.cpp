#include "Renderer.h"
#include <algorithm>

#include "../nclgl/Matrix3.h"
#include "../nclgl/Camera.h"
#include "../nclgl/ReFrustum.h"
#include "../nclgl/ReSceneNode.h"
#include "../nclgl/RePrimitiveComponent.h"
#include "../nclgl/RePointLightComponent.h"
#include "../nclgl/ReDLight.h"
#include "../nclgl/ReShadowBuffer.h"
#include "../nclgl/ReSceneBuffer.h"
#include "../nclgl/ReLightBuffer.h"

#include "SceneGenerator.h"
#include "PrimitiveFilter.h"
#include "PointLightFilter.h"
#include "ShadowFilter.h"
#include "DayLooper.h"
#include "CameraRoute.h"

#include "Materials/ShadowMat.h"


Renderer::Renderer(Window &parent) : OGLRenderer(parent)	
{
	mPrimitiveLib.ReadPrimitivesFromDisk();

	mCamera.reset(new Camera(-30.0f, 0.0f, Vector3(0, 250.0f, 0)));
	mCamRoute.reset(new CameraRoute(mCamera));
	mCamRoute->GenDefaultRoute();
	mCamRoute->PrepareForStart();
	bUseCamRoute = false;

	mProjMatrix_Cam = Matrix4::Perspective(1.0f, 15000.0f, (float)width / (float)height, 90.0f);

	mSceneRoot.reset(new ReSceneNode());
	mCamFrustum.reset(new ReFrustum());

	SceneGenerator::Build(mCamera, mSceneRoot, mPrimitiveLib);

	mCombinePrim = mPrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_COMBINE);
	mSkyBoxPrim = mPrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_SKY_BOX);

	mPrimFilter.reset(new PrimitiveFilter(mCamera, mCamFrustum));
	mPLightFilter.reset(new PointLightFilter(mCamera, mCamFrustum));

	mDLight.reset(new ReDLight(mPrimitiveLib.GetPrimitive(PrimitiveIndex::PRI_DIRECT_LIGHT)));
	Vector3 tDLightDir = Matrix3::Rotation(-60, Vector3(0, 0, 1)) * Vector3(0, -1, 0);
	mDLight->UpdateDLightParam(tDLightDir, Vector4(1, 1, 1, 1), 0.9f, SceneRadius);

	mDayLooper.reset(new DayLooper(mDLight));

	mShadowMat_DLight.reset(new ShadowMat());
	mShadowFilter_DLight.reset(new ShadowFilter());
	

	mShadowBuffer_DLight.reset(new ReShadowBuffer(ShadowSize, ShadowSize));
	mSceneBuffer.reset(new ReSceneBuffer(width, height));
	mLightBuffer.reset(new ReLightBuffer(width, height));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	bRenderShadow = true;

	init = true;
}
Renderer::~Renderer(void)	
{
	ReMaterial::DeleteAllShaders();
}

void Renderer::UpdateScene(float msec)
{
	if (bUseCamRoute)
	{
		mCamRoute->UpdateCamera(msec);
	}
	else
	{
		mCamera->UpdateCamera(msec);
	}
	
	mSceneRoot->Update(msec);

	if (bEnableDayLoop)
	{
		mDayLooper->UpdateDaylight(msec);
		bRenderShadow = true;
	}
	
}

void Renderer::RenderScene()	{
	glClearColor(0.2f,0.2f,0.2f,1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	if (bRenderShadow)
	{
		DrawShadowBuffer();
		bRenderShadow = false;
	}
	

	modelMatrix.ToIdentity();
	viewMatrix = mCamera->BuildViewMatrix();
	projMatrix = Matrix4::Perspective(1.0f, 10000.0f, (float)width / (float)height, 45.0f);
	mCamFrustum->FromMatrix(projMatrix * viewMatrix);

	DrawSceneBuffer();
	DrawLightBuffer();

	glClearColor(0.2f, 0.2f, 0.2f, 1);

	CombineBuffers();
	DrawSkyBox();

	modelMatrix.ToIdentity();
	viewMatrix.ToIdentity();
	projMatrix.ToIdentity();

	BindShader(0);
}

void Renderer::ToggleCameraRoute()
{
	bUseCamRoute = !bUseCamRoute;
	if (bUseCamRoute)
	{
		mCamRoute->PrepareForStart();
	}
}

int Renderer::TryBindShader(Shader* NewShader)
{
	if (currentShader == NewShader) return 1;
	BindShader(NewShader);
	return 0;
}

void Renderer::UpdateMatrixVP(const Matrix4& ProjMatrix, const Matrix4& ViewMatrix)
{
	if (currentShader) {
		glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "viewMatrix"), 1, false, ViewMatrix.values);
		glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "projMatrix"), 1, false, ProjMatrix.values);
	}
}

void Renderer::UpdateMatrixModel(const Matrix4& ModelMatrix)
{
	if (currentShader) {
		glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "modelMatrix"), 1, false, ModelMatrix.values);
	}
}

void Renderer::UpdateMatrixShadow(const Matrix4& ShadowMatrix)
{
	if (currentShader) {
		glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "shadowMatrix"), 1, false, ShadowMatrix.values);
	}
}

void Renderer::DrawQpaque()
{
	for (const auto& Conatiner : mPrimFilter->mPrimitives_Opaque)
	{
		DrawPrimitive(Conatiner.Component, true);
	}
}

void Renderer::DrawTransparent()
{
	for (const auto& Conatiner : mPrimFilter->mPrimitives_Transparent)
	{
		DrawPrimitive(Conatiner.Component, true);
	}
}

void Renderer::DrawPrimitive(const std::shared_ptr<RePrimitiveComponent>& Primitive, bool bUseMaterial)
{
	if (bUseMaterial)
	{
		if (TryBindShader(Primitive->GetShader()) == 0)
		{
			UpdateMatrixVP(projMatrix, viewMatrix);
		}
	}
	Matrix4 ModelMatrix = Primitive->GetWorldTransform();
	UpdateMatrixModel(ModelMatrix);
	Primitive->Draw(bUseMaterial);
}

void Renderer::DrawInstanced()
{
	for (const auto& tIter : mPrimFilter->mInstancedPrimitives)
	{
		DrawPrimitiveIntanced(tIter.first, tIter.second, true);
	}
}

void Renderer::DrawPrimitiveIntanced(const std::shared_ptr<RePrimitive>& Primitive, const std::vector<Matrix4>& ModelMatrices, bool bUseMaterial)
{
	if (bUseMaterial)
	{
		if (TryBindShader(Primitive->GetMaterial()->GetShader()) == 0)
		{
			UpdateMatrixVP(projMatrix, viewMatrix);
		}
	}
	std::unique_ptr<float[]> ModelMatrixBuffer(new float[16 * ModelMatrices.size()]);
	for (size_t i = 0; i < ModelMatrices.size(); i++)
	{
		memcpy(ModelMatrixBuffer.get() + 16 * i, ModelMatrices[i].values, 16 * sizeof(float));
	}
	glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "modelMatrices"), ModelMatrices.size(), false, ModelMatrixBuffer.get());
	if (bUseMaterial)
	{
		Primitive->GetMaterial()->UpdateRenderParam();
	}
	Primitive->GetMesh()->DrawInstanced(ModelMatrices.size());
}

void Renderer::DrawShadowOpaque_DLight()
{
	for (const auto& Primitive : mShadowFilter_DLight->mPrimitives_Opaque)
	{
		DrawPrimitive(Primitive, false);
	}
}

void Renderer::UpdateLightShaderParams(Shader* InShader)
{
	glUniform1i(glGetUniformLocation(InShader->GetProgram(), "colourTex"), 0);
	glUniform1i(glGetUniformLocation(InShader->GetProgram(), "depthTex"), 1);
	glUniform1i(glGetUniformLocation(InShader->GetProgram(), "normTex"), 2);
	glUniform1i(glGetUniformLocation(InShader->GetProgram(), "metallicRoughnessTex"), 3);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mSceneBuffer->mColourTex);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mSceneBuffer->mDepthTex);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, mSceneBuffer->mNormalTex);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, mSceneBuffer->mMetallicRoughnessTex);

	glUniform3fv(glGetUniformLocation(InShader->GetProgram(), "cameraPos"), 1, (float*)&mCamera->GetPosition());
	glUniform2f(glGetUniformLocation(InShader->GetProgram(), "pixelSize"), 1.0f / width, 1.0f / height);

	Matrix4 invViewProj = (projMatrix * viewMatrix).Inverse();
	glUniformMatrix4fv(glGetUniformLocation(InShader->GetProgram(), "inverseProjView"), 1, false, invViewProj.values);
}

void Renderer::DrawDirectionalLight()
{
	if(TryBindShader(mDLight->GetShader()) == 0)
	{
		UpdateLightShaderParams(mDLight->GetShader());
		UpdateMatrixShadow(mShadowMatrix_DLight);
		glUniform1i(glGetUniformLocation(mDLight->GetShader()->GetProgram(), "shadowTex"), 4);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, mShadowBuffer_DLight->mDepthTex);
	}
	mDLight->Draw();
}

void Renderer::DrawPointLights()
{
	for (const auto& PointLight : mPLightFilter->mPointLights)
	{
		DrawPointLight(PointLight);
	}
}

void Renderer::DrawPointLight(const std::shared_ptr<RePointLightComponent>& PointLight)
{
	if (TryBindShader(PointLight->GetShader()) == 0)
	{
		UpdateShaderMatrices();
		UpdateMatrixVP(projMatrix, viewMatrix);
		UpdateMatrixModel(Matrix4());
		UpdateLightShaderParams(PointLight->GetShader());
	}
	PointLight->Draw();
}

void Renderer::DrawShadowBuffer()
{
	Matrix4 ViewMatrix_DLight = Matrix4::BuildViewMatrix(mDLight->GetPosition(), Vector3(0, 0, 0));
	Matrix4 ProjMatrix_DLight = Matrix4::Orthographic(1.0f, mDLight->GetDistance() + SceneRadius, SceneRadius / 2.0f, -SceneRadius / 2.0f, SceneRadius / 2.0f, -SceneRadius / 2.0f);
	//Matrix4 ProjMatrix_DLight = Matrix4::Perspective(1.0f, mDLight->GetDistance() + SceneRadius, 1, 90);
	mShadowMatrix_DLight = ProjMatrix_DLight * ViewMatrix_DLight;

	mShadowFilter_DLight->FindPrimitives(mSceneRoot);

	mShadowBuffer_DLight->Bind();
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, ShadowSize, ShadowSize);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	BindShader(mShadowMat_DLight->GetShader());
	UpdateMatrixVP(ProjMatrix_DLight, ViewMatrix_DLight);

	DrawShadowOpaque_DLight();

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glViewport(0, 0, width, height);
	mShadowBuffer_DLight->Unbind();

	mShadowFilter_DLight->ClearPrimitives();
}

void Renderer::DrawSceneBuffer()
{
	mSceneBuffer->Bind();

	glClearColor(0, 0, 0, 0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	mPrimFilter->FindPrimitives(mSceneRoot);
	mPrimFilter->SortPrimitives();

	DrawQpaque();
	DrawInstanced();
	glDepthMask(GL_FALSE);
	DrawTransparent();
	glDepthMask(GL_TRUE);

	mPrimFilter->ClearPrimitives();

	mSceneBuffer->Unbind();
}

void Renderer::DrawLightBuffer()
{
	mLightBuffer->Bind();

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBlendFunc(GL_ONE, GL_ONE);

	DrawDirectionalLight();

	glCullFace(GL_FRONT);
	glDepthFunc(GL_ALWAYS);
	glDepthMask(GL_FALSE);

	mPLightFilter->FindPointLights(mSceneRoot);

	DrawPointLights();

	mPLightFilter->ClearPointLights();

	
	glCullFace(GL_BACK);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mLightBuffer->Unbind();
}

void Renderer::CombineBuffers()
{
	const ReMaterialPtr& CombineMaterial = mCombinePrim->GetMaterial();

	BindShader(CombineMaterial->GetShader());

	CombineMaterial->SetShaderTexture2D("colourTex", mSceneBuffer->mColourTex, 0);
	CombineMaterial->SetShaderTexture2D("diffuseLight", mLightBuffer->mDiffuseTex, 1);
	CombineMaterial->SetShaderTexture2D("specularLight", mLightBuffer->mSpecularTex, 2);
	CombineMaterial->SetShaderTexture2D("emissiveTex", mSceneBuffer->mEmissiveTex, 3);

	mCombinePrim->DrawMesh();
}

void Renderer::DrawSkyBox()
{
	glDepthMask(GL_FALSE);

	BindShader(mSkyBoxPrim->GetMaterial()->GetShader());

	UpdateMatrixVP(projMatrix, viewMatrix);

	mSkyBoxPrim->UpdateMaterialParams();
	mSkyBoxPrim->GetMaterial()->SetShaderFloat("colourScale", mDLight->GetStrength() > 0.5 ? 1.0 : 0.2);
	mSkyBoxPrim->GetMaterial()->SetShaderTexture2D("sceneTex", mSceneBuffer->mEmissiveTex, 1);
	mSkyBoxPrim->DrawMesh();

	glDepthMask(GL_TRUE);
}

