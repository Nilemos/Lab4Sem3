#include "TJobStream.h"

TJobStream::TJobStream(double jobIntense)
{
	if (jobIntense >= 0.0 && jobIntense <= 1.0)
	{
		this->jobIntense = jobIntense;
		lastJobId = 1;
	}
	else
		throw "Err";
}

double TJobStream::GetJobIntens(void) const noexcept
{
	return jobIntense;
}

size_t TJobStream::GetNewJob(void)
{
	if (static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX) <= jobIntense)
	{
		lastJobId++;
		return lastJobId - 1;
	}
	else
		return 0;
}

size_t TJobStream::GetLastJobId(void) const noexcept
{
	return lastJobId;
}