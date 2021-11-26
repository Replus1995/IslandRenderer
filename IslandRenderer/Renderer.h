#pragma once
#include "../NCLGL/OGLRenderer.h"
#include "PrimitiveLibrary.h"

class Camera;
class ReFrustum;
class ReSceneNode;
class ReMaterial;
class RePrimitive;
class RePrimitiveComponent;
class RePointLightComponent;
class ReDLight;
class ReShadowBuffer;
class ReSceneBuffer;
class ReLightBuffer;
class ReSingleBuffer;

class ShadowFilter;
class PrimitiveFilter;
class PointLightFilter;

class DayLooper;
class CameraRoute;

class Renderer : public OGLRenderer	{
public:
	Renderer(Window &parent);
	 ~Renderer(void);

	 void UpdateScene(float msec) override;
	 void RenderScene()	override;

	 void ToggleDayLoop() { bEnableDayLoop = !bEnableDayLoop; };
	 void ToggleCameraRoute();
	 
protected:
	int TryBindShader(Shader* NewShader);
	void UpdateMatrixVP(const Matrix4& ProjMatrix, const Matrix4& ViewMatrix);
	void UpdateMatrixModel(const Matrix4& ModelMatrix);
	void UpdateMatrixShadow(const Matrix4& ShadowMatrix);
	
	void DrawQpaque();
	void DrawTransparentOpaque();
	void DrawPrimitive(const std::shared_ptr<RePrimitiveComponent>& Primitive, bool bUseMaterial);
	void DrawInstanced();
	void DrawPrimitiveIntanced(const std::shared_ptr<RePrimitive>& Primitive, const std::vector<Matrix4>& ModelMatrices, bool bUseMaterial);

	void DrawTransparent();
	void DrawPrimitiveForward(const std::shared_ptr<RePrimitiveComponent>& Primitive, bool bUseMaterial);

	void DrawShadowOpaque_DLight();

	void UpdateLightShaderParams(Shader* InShader);

	void DrawDirectionalLight();
	void DrawPointLights();
	void DrawPointLight(const std::shared_ptr<RePointLightComponent>& PointLight);

	void DrawShadowBuffer();
	void DrawSceneBuffer();
	void DrawLightBuffer();
	void CombineBuffers();

	void DrawSkyBox();

protected:
	const int ShadowSize = 4096;
	const float SceneRadius = 3000;

	PrimitiveLibrary mPrimitiveLib;

	std::shared_ptr<Camera> mCamera;
	Matrix4 mProjMatrix_Cam;
	bool bUseCamRoute = true;
	std::unique_ptr<CameraRoute> mCamRoute;

	std::shared_ptr<ReSceneNode> mSceneRoot;

	std::shared_ptr<ReFrustum> mCamFrustum;
	std::unique_ptr<PrimitiveFilter> mPrimFilter;
	std::unique_ptr<PointLightFilter> mPLightFilter;

	std::shared_ptr<ReDLight> mDLight;
	bool bEnableDayLoop = false;
	std::unique_ptr<DayLooper> mDayLooper;

	std::shared_ptr<ReMaterial> mShadowMat_DLight;
	std::unique_ptr<ShadowFilter> mShadowFilter_DLight;
	Matrix4 mShadowMatrix_DLight;
	bool bRenderShadow;
	std::unique_ptr<ReShadowBuffer> mShadowBuffer_DLight;

	std::unique_ptr<ReSceneBuffer> mSceneBuffer;
	std::unique_ptr<ReLightBuffer> mLightBuffer;

	std::shared_ptr<RePrimitive> mSkyBoxPrim;
	std::shared_ptr<RePrimitive> mCombinePrim;
};
