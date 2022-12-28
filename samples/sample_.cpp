#include <iostream>
#include "TQueue.h"
#include"TProc.h"
#include"TJobStream.h"

using namespace std;

void line()
{
	cout << "==============================================================================" << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	line();

	TQueue<int> q(3);
	q.Push(5);
	cout << q.TopPop() << endl;
	q.Push(4);
	q.Push(3);
	q.Push(2);
	q.Pop();
	q.Push(1);
	cout << q.Top() << endl;
	q.Pop();
	q.Push(20);
	cout << q.Top() << endl;

	line();

	std::srand(std::time(nullptr));
	const size_t tests = 3;
	TProc proc[tests] = { TProc(0.5, 3), TProc(0.2, 3), TProc(0.5, 3) };
	TJobStream stream[tests] = { TJobStream(0.5), TJobStream(0.5), TJobStream(0.2) };
	size_t tacts[tests] = { 10, 10, 10 };
	TQueue<size_t> jobsqueue(10);

	for (size_t i = 0; i < tests; i++)
	{
		std::cout << tacts[i] << " тактов имитации , размер очереди 3, интенсивность потока задач " << stream[i].GetJobIntens() << ", производительность процессора " << proc[i].GetRate() << '.' << std::endl;
		for (size_t j = 0; j < tacts[i]; j++)
		{
			size_t temp_job = stream[i].GetNewJob();
			if (temp_job > 0)
				jobsqueue.Push(temp_job);
			if (!jobsqueue.IsEmpty())
				if (proc[i].RunNewJob(jobsqueue.Top()))
					jobsqueue.Pop();
			proc[i].DoJob();
		}
		jobsqueue.Free();
		std::cout << "Заданий создано " << stream[i].GetLastJobId() << ", заданий обработано " << proc[i].GetJobsDone() << ", количество отказов в обслуживании заданий из-за переполнения очереди " << proc[i].GetOverflowTimes() << ", тактов простоя " << proc[i].GetNoJobsTimes() << ", среднее кол - во тактов на задание. " << (static_cast<double>(tacts[i]) / static_cast<double>(proc[i].GetJobsDone())) << std::endl << std::endl;

	}

	line();

	return 0;
}