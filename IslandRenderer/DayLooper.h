#pragma once
#include <memory>

class ReDLight;

class DayLooper
{
public:
	DayLooper(const std::shared_ptr<ReDLight>& InDayLight)
		: mDayLight(InDayLight)
	{};
	~DayLooper() {};

	void UpdateDaylight(float msec);

protected:
	std::shared_ptr<ReDLight> mDayLight;
	float mLoopSpeed = 20.0f;
};