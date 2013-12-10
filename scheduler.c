
#include <stdio.h>

#include "dispatcher.h"

#define SCHED_MAX_PRIORITY 2
#define STARVATION_THRESHOLD 10
#define MAX_THREADS 5
LIST_ENTRY ReadyQueues[2];

typedef struct _STARVATION_COUNT{
	PDISPATCHER_TASK task;
	int cycles;
}STARVATION_COUNT;

STARVATION_COUNT * starvationCount = NULL;
int threadCount = 0;

void UpdateStarvationCount(PDISPATCHER_TASK nextThread)
{
	//increase starvation count of all threads which are not the nextTask
	//set starvationCount of the nextTask to 0
	int i;
	for(i=0; i< threadCount; i++)
	{
		if(starvationCount[i].task == nextThread)
		{
			starvationCount[i].cycles = 0;
		}else{
			starvationCount[i].cycles++;
		}
	}

}

PDISPATCHER_TASK Schedule(PDISPATCHER_TASK OldThread) {

	PDISPATCHER_TASK NextTask;
	PLIST_ENTRY NextTaskListEntry;
	PLIST_ENTRY ReadyQueue;

	//test for starvation
	int i;
	for(i=0; i< threadCount; i++)
	{
		if(starvationCount[i].cycles >= 10)
		{
			starvationCount[i].cycles = 0;
			return starvationCount[i].task;
		}
	}

	if (!IsListEmpty(&ReadyQueues[SCHED_PRIORITY_HIGH]))
	{
		ReadyQueue = &ReadyQueues[1];
	}
	else if (!IsListEmpty(&ReadyQueues[SCHED_PRIORITY_LOW]))
	{
		ReadyQueue = &ReadyQueues[0];
	}
	else
		return OldThread;

	NextTaskListEntry = RemoveHeadList(ReadyQueue);

	// get list entry for next task
	NextTask = CONTAINING_RECORD(NextTaskListEntry, DISPATCHER_TASK, Link);

	UpdateStarvationCount(NextTask);

	// re-insert task at list tail, but skip the "idle" thread
	if (OldThread)
	{
		InsertTailList(&ReadyQueues[OldThread->Priority], &OldThread->Link);
	}

	// return result
	return NextTask;
}

BOOLEAN InitializeScheduler()
{
	InitializeListHead(&ReadyQueues[0]);
	InitializeListHead(&ReadyQueues[1]);

	return TRUE;
}

BOOLEAN AddThread(PDISPATCHER_TASK Thread)
{
	if(starvationCount == NULL)
	{
		//init starvationCount to array of ThreadCount
		starvationCount = (STARVATION_COUNT*) malloc(sizeof(STARVATION_COUNT) * MAX_THREADS);
	}

	if (Thread->Priority != SCHED_PRIORITY_HIGH && Thread->Priority != SCHED_PRIORITY_LOW)
	{
		return FALSE;
	}

	InsertTailList(&ReadyQueues[Thread->Priority], &Thread->Link);

	//init starvation struct for new thread
	starvationCount[threadCount].task = Thread;
	starvationCount[threadCount].cycles = 0;

	threadCount++;

	return TRUE;
}
