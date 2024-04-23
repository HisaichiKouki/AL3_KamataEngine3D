#include "TimedCall.h"

TimedCall::TimedCall(std::function<void(void)> f, uint32_t timer)
{
	function_ = f;
	timer_ = timer;
}


void TimedCall::Update()
{
	if (isFinish_)
	{
		return;
	}
	timer_--;
	if (timer_ <= 0)
	{
		isFinish_ = true;
		function_();
	}
}
