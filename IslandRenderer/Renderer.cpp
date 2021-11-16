#include "Renderer.h"
#include <algorithm>

#include "../nclgl/Camera.h"
#include "../nclgl/ReFrustum.h"
#include "../nclgl/ReSceneNode.h"

#include "SceneGenerator.h"


Renderer::Renderer(Window &parent) : OGLRenderer(parent)	
{
	mPrimitiveLib.ReadPrimitivesFromDisk();

	mCamera.reset(new Camera(-45.0f, 0.0f, Vector3(0, 10, 0)));
	mFrustum.reset(new ReFrustum());
	mSceneRoot.reset(new ReSceneNode());

	projMatrix = Matrix4::Perspective(1.0f, 15000.0f, (float)width / (float)height, 45.0f);

	SceneGenerator::Build(mSceneRoot, mPrimitiveLib);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	init = true;
}
Renderer::~Renderer(void)	
{
	ReMaterial::DeleteAllShaders();
}

void Renderer::UpdateScene(float msec)
{
	mCamera->UpdateCamera(msec);
	viewMatrix = mCamera->BuildViewMatrix();
	mFrustum->FromMatrix(projMatrix * viewMatrix);

	mSceneRoot->Update(msec);
}

void Renderer::RenderScene()	{
	glClearColor(0.2f,0.2f,0.2f,1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	FindPrimitivesInFrustum(mSceneRoot);
	SortPrimitives();

	DrawPrimitives();

	ClearPrimitives();
}

void Renderer::FindPrimitivesInFrustum(const std::shared_ptr<ReSceneNode>& InNode)
{
	std::vector<ReNodeComponentPtr> ComponentList;
	InNode->GetAllComponents(ComponentList,
		[](ReNodeComponentPtr& Component) { return Component->IsPrimitive(); });
	for (ReNodeComponentPtr Component : ComponentList)
	{
		RePrimitiveComponentPtr PrimitiveComponent = std::static_pointer_cast<RePrimitiveComponent>(Component);
		if (mFrustum->InsideFrustum(PrimitiveComponent))
		{
			Vector3 CamDir = PrimitiveComponent->GetWorldTransform().GetPositionVector() - mCamera->GetPosition();
			PrimitiveContainer NewContainer;
			NewContainer.Component = PrimitiveComponent;
			NewContainer.Distance = Vector3::Dot(CamDir, CamDir);
			if (PrimitiveComponent->IsTransparent())
			{
				mPrimitives_Transparent.push_back(NewContainer);
			}
			else
			{
				mPrimitives_Opaque.push_back(NewContainer);
			}
		}
	}

	for (auto ChidIter = InNode->GetChildBegin(); ChidIter != InNode->GetChildEnd(); ChidIter++)
	{
		FindPrimitivesInFrustum(*ChidIter);
	}
}

void Renderer::SortPrimitives()
{
	std::sort(mPrimitives_Transparent.rbegin(), mPrimitives_Transparent.rend(), PrimitiveContainer::CompareByDistance);
	std::sort(mPrimitives_Opaque.begin(), mPrimitives_Opaque.end(), PrimitiveContainer::CompareByDistance);
}

void Renderer::ClearPrimitives()
{
	mPrimitives_Transparent.clear();
	mPrimitives_Opaque.clear();
}

void Renderer::DrawPrimitives()
{
	for (const auto& Conatiner : mPrimitives_Opaque)
	{
		DrawPrimitive(Conatiner);
	}
	for (const auto& Conatiner : mPrimitives_Transparent)
	{
		DrawPrimitive(Conatiner);
	}
}

void Renderer::DrawPrimitive(const PrimitiveContainer& Container)
{
	BindShader(Container.Component->GetShader());
	UpdateShaderMatrices();
	Matrix4 ModelMat = Container.Component->GetWorldTransform();
	glUniformMatrix4fv(glGetUniformLocation(Container.Component->GetShader()->GetProgram(), "modelMatrix"), 1, false, ModelMat.values);
	Container.Component->Draw();
}

