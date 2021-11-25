#pragma once
#include <memory>
#include <vector>
#include "../nclgl/Vector3.h"
#include "../nclgl/Quaternion.h"

class Camera;

struct CamKeyFrame
{
	Vector3 Location;
	Quaternion Rotation;
	float Time;
};

class CameraRoute
{
public:
	CameraRoute(const std::shared_ptr<Camera>& InCamera);
	~CameraRoute() {};

	void UpdateCamera(float msec);
	void PrepareForStart();
	void GenDefaultRoute();

protected:
	std::shared_ptr<Camera> mCam;
	float mTime = 0.0f;
	std::vector<CamKeyFrame> mKeyFrames;
	unsigned int mNextFrameId = 0;
	Vector3 mLastLocation;
	Quaternion mLastRotation;
};