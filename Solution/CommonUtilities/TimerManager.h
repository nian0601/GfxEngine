#pragma once

#include "CUString.h"
#include "Timer.h"
#include <vector>
#include "CUMap.h"

namespace CU
{
	typedef unsigned int TimerHandle;

	class TimerManager
	{
	public:
		TimerManager();

		void StartTimer(const CU::String<80>& aName);
		Time StopTimer(const CU::String<80>& aName);

		const Timer& GetTimer(TimerHandle aId) const;
		const Timer& GetMasterTimer() const;
		TimerHandle CreateTimer();
		void Update();
		void PauseAll();
		void StartAll();

		void CapFrameRate(float aFrameRate);

	private:
		Timer myMasterTimer;
		TimeUnit GetTime();
		std::vector<Timer> myTimerList;
		TimeUnit myLastTime;
		unsigned long long myFrequency;

		Map<CU::String<80>, TimeUnit> myTimers;
	};
}