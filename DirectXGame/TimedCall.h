#pragma once
#include <functional>

class TimedCall
{
public:
	TimedCall(std::function<void(void)> f, uint32_t timer);

	void Update();
	bool IsFinished() { return isFinish_; }
private:
	std::function<void(void)>function_;//= std::bind(&MyClass::returnValue, &myClass, std::placeholders::_1);

	uint32_t timer_;
	bool isFinish_ = false;
};
