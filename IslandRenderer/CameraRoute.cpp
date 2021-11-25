#include "CameraRoute.h"
#include "../nclgl/Camera.h"

CameraRoute::CameraRoute(const std::shared_ptr<Camera>& InCamera)
	: mCam(InCamera)
{
};


void CameraRoute::UpdateCamera(float msec)
{
	if (mKeyFrames.size() == 0) return;

	mTime += msec;
	CamKeyFrame tNestFrame = mKeyFrames[mNextFrameId];
	while(mTime >= tNestFrame.Time)
	{
		mTime -= tNestFrame.Time;
		mLastLocation = tNestFrame.Location;
		mLastRotation = tNestFrame.Rotation;
		mNextFrameId++;
		if (mNextFrameId >= mKeyFrames.size()) 
			mNextFrameId = 0;
		tNestFrame = mKeyFrames[mNextFrameId];
	}

	float tPercent = mTime / tNestFrame.Time;
	Quaternion CurRotation = Quaternion::Lerp(mLastRotation, tNestFrame.Rotation, tPercent);
	Vector3 CurLocation = mLastLocation * (1 - tPercent) + tNestFrame.Location * tPercent;

	mCam->SetPosition(CurLocation);
	mCam->SetQuat(CurRotation);
}

void CameraRoute::PrepareForStart()
{
	mLastLocation = mCam->GetPosition();
	mLastRotation = mCam->GetQuat();
	mNextFrameId = 0;
	mTime = 0.0f;
}

void CameraRoute::GenDefaultRoute()
{
	mKeyFrames.push_back(CamKeyFrame{ Vector3(53.844433, 756.858643, 1196.924194), Quaternion(-0.317242, 0.019120, -0.006398, 0.948130), 5 });
	mKeyFrames.push_back(CamKeyFrame{ Vector3(53.844433, 756.858643, 1196.924194), Quaternion(-0.317242, 0.019120, -0.006398, 0.948130), 3 });
	mKeyFrames.push_back(CamKeyFrame{ Vector3(77.365044, 151.473709, 163.154785), Quaternion(-0.242995, -0.185865, 0.047498, 0.950869), 5 });
	mKeyFrames.push_back(CamKeyFrame{ Vector3(77.365044, 151.473709, 163.154785), Quaternion(-0.242995, -0.185865, 0.047498, 0.950869), 3 });
	//mKeyFrames.push_back(CamKeyFrame{ Vector3(77.365044, 151.473709, 163.154785),  Quaternion(-0.122763, -0.031524, 0.003901, 0.991928), 1 });
	//mKeyFrames.push_back(CamKeyFrame{ Vector3(77.365044, 151.473709, 163.154785),  Quaternion(-0.122763, -0.031524, 0.003901, 0.991928), 0.5 });
	//mKeyFrames.push_back(CamKeyFrame{ Vector3(-90.358292, 126.631195, -267.434204), Quaternion(-0.122763, -0.031524, 0.003901, 0.991928), 5 });
	//mKeyFrames.push_back(CamKeyFrame{ Vector3(-90.358292, 126.631195, -267.434204), Quaternion(-0.122763, -0.031524, 0.003901, 0.991928), 3 });
	mKeyFrames.push_back(CamKeyFrame{ Vector3(77.365044, 151.473709, 163.154785), Quaternion(-0.077625, 0.095226, -0.007449, 0.992397), 1 });
	mKeyFrames.push_back(CamKeyFrame{ Vector3(77.365044, 151.473709, 163.154785), Quaternion(-0.077625, 0.095226, -0.007449, 0.992397), 0.5 });
	mKeyFrames.push_back(CamKeyFrame{ Vector3(-16.214478, 151.473709, -353.641296), Quaternion(-0.077625, 0.095226, -0.007449, 0.992397), 5 });
	mKeyFrames.push_back(CamKeyFrame{ Vector3(-16.214478, 151.473709, -353.641296), Quaternion(-0.077625, 0.095226, -0.007449, 0.992397), 3 });

}
