#include "SceneNode.h"

SceneNode::SceneNode(Mesh* m, Vector4 c)
	: mesh(m)
	, colour(c)
	, parent(NULL)
	, modelScale(Vector3(1,1,1))
	, boundingRadius(1.0f)
	, distanceFromCamera(0.0f)
	, texture(0)
{
}

SceneNode::~SceneNode(void)
{
	for (unsigned int i = 0; i < children.size(); ++i) 
	{
		delete children[i];
	}
}

void SceneNode::AddChild(SceneNode* s)
{
	children.push_back(s);
	s->parent = this;
}

void SceneNode::Update(float dt)
{
	if (parent)
	{
		worldtransform = parent->worldtransform * transform;
	}
	else
	{
		worldtransform = transform;
	}
	for (vector<SceneNode*>::iterator 
		i = children.begin();
		i != children.end(); ++i)
	{
		(*i)->Update(dt);
	}
}

void SceneNode::Draw(const OGLRenderer& r)
{
	if (mesh)
	{
		mesh->Draw();
	}
}
