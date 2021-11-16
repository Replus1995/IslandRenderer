#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Mesh.h"
#include <vector>

class SceneNode
{
public:
	SceneNode(Mesh* m = NULL, Vector4 c = Vector4(1, 1, 1, 1));
	~SceneNode(void);
	
	void SetTransform(const Matrix4& matrix) { transform = matrix; }
	const Matrix4& GetTransform() const { return transform; }
	Matrix4 GetWorldTransform() const { return worldtransform; }

	Vector4 GetColour() const { return colour; }
	void SetColour(Vector4 c) { colour = c; }

	Vector3 GetModelScale() const { return modelScale; }
	void SetModelScale(Vector3 s) { modelScale = s; }

	Mesh* GetMesh() const { return mesh; }
	void SetMesh(Mesh* m) { mesh = m; }

	void AddChild(SceneNode* s);

	virtual void Update(float dt);
	virtual void Draw(const OGLRenderer& r);

	std::vector<SceneNode*>::const_iterator GetChildIteratorStart()
	{
		return children.begin();
	}
	std::vector<SceneNode*>::const_iterator GetChildIteratorEnd()
	{
		return children.end();
	}
public:
	float GetBoundingRadius() const { return boundingRadius; }
	void SetBoundingRadius(float f) { boundingRadius = f; }

	float GetCameraDistance() const { return distanceFromCamera; }
	void SetCameraDistance(float f) { distanceFromCamera = f; }

	GLuint GetTexture() const { return texture; }
	void SetTexture(GLuint tex) { texture = tex; }

	static bool CompareByCameraDistance(SceneNode* a, SceneNode* b)
	{
		return (a->distanceFromCamera < b->distanceFromCamera) ? true : false;
	}
	
	 
protected:
	SceneNode* parent;
	std::vector<SceneNode*> children;

	Mesh* mesh;
	Matrix4 worldtransform;
	Matrix4 transform;
	Vector3 modelScale;
	Vector4 colour;
	GLuint texture;

	float distanceFromCamera;
	float boundingRadius;
};
