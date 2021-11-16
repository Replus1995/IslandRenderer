#pragma once
#include "../NCLGL/OGLRenderer.h"
#include "PrimitiveLibrary.h"
#include "PrimitiveContainer.h"

class Camera;
class ReFrustum;
class ReSceneNode;
class RePrimitiveComponent;

class Renderer : public OGLRenderer	{
public:
	Renderer(Window &parent);
	 ~Renderer(void);

	 void UpdateScene(float msec) override;
	 void RenderScene()	override;
	 
protected:
	void FindPrimitivesInFrustum(const std::shared_ptr<ReSceneNode>& InNode);
	void SortPrimitives();
	void ClearPrimitives();
	void DrawPrimitives();
	void DrawPrimitive(const PrimitiveContainer& Container);


protected:
	PrimitiveLibrary mPrimitiveLib;

	std::unique_ptr<Camera> mCamera;
	std::shared_ptr<ReFrustum> mFrustum;
	std::shared_ptr<ReSceneNode> mSceneRoot;


	std::vector<PrimitiveContainer> mPrimitives_Transparent;
	std::vector<PrimitiveContainer> mPrimitives_Opaque;

};
