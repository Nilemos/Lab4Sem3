#pragma once
#include "TQueue.h"

#include <cstdlib>

class TProc
{
private:
	double procRate;
	TQueue<size_t> jobs;
	size_t jobsDone;
	size_t overflowTimes;
	size_t noJobsTimes;
public:
	TProc(double Rate, size_t MaxJobs);
	double GetRate(void) const noexcept;
	size_t IsProcBusy(void) const noexcept;
	bool IsProcFull(void) const noexcept;
	size_t RunNewJob(size_t JobId);
	size_t DoJob(void);
	size_t GetJobsDone(void) const noexcept;
	size_t GetOverflowTimes(void) const noexcept;
	size_t GetNoJobsTimes(void) const noexcept;
};
