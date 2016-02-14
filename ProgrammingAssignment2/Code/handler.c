/*
This file contains anything that isn't specific to one particular data structure
or test case.
*/

/*
TODO: Add x-fast trie functions to switch() statement
*/
#include <stdint.h>
#include <pthread.h>
#include <sys/time.h>

#include "handler.h"
#include "testcase1.h"
//#include "skiplist.h"

#include <unistd.h>

#define VERBOSE 0


void* thread_dsHandler(void* args)
{
	pthreadData * sharedData = (pthreadData *)args;

	for(;;)
	{
		char retStat;
		switch(((pthreadData *)args)->curState)
		{
		// define thread behavior here (and/or call functions)
			case FIND:
				retStat = (slFind(sharedData->slHead, sharedData->ioData)!=NULL);
				#if VERBOSE
				printf(	"Found %d in skiplist: %d\n",
				sharedData->ioData, retStat);
				#endif
				//...
				break;
			case INSERT:
				retStat = slInsert(sharedData->slHead, sharedData->ioData);
				#if VERBOSE
				printf(	"Added %d to skiplist: %d\n",
				sharedData->ioData, retStat);
				#endif
				if(retStat == 1)
					;//TODO call xInsert()
				break;
			case REMOVE:
				retStat = slRemove(sharedData->slHead, sharedData->ioData);
				//...
				#if VERBOSE
				printf(	"Removed %d from skiplist: %d\n",
					sharedData->ioData, retStat);
				#endif
				break;
			case IDLE:
				continue;
				break;
			case TERM:
				pthread_exit(NULL);
				break;
			default:
				break;
			
		}
		((pthreadData *)args)->curState = IDLE;
	}
}



int main()
{
	// load test case
	Task * todoList = loadTestCase();
	
	// start timer
	struct timeval begTime;
	gettimeofday(&begTime, NULL);

	// init Data Structures
	
	slNode * slHead = slInit();
	
	// init Threads
	pthread_t threads[NUMTHREADS];
	pthreadData threadData[NUMTHREADS];
	for(uint8_t i=0; i<NUMTHREADS; i++)
	{
		threadData[i].curState = IDLE;
		threadData[i].slHead = slHead;
		pthread_create(&threads[i], NULL, thread_dsHandler, (void *) &threadData[i]);
	}
	
	// task and thread scheduler
	for(int tsk=0; tsk < NUMTASKS;)
	{
		for(uint8_t thr=0; thr<NUMTHREADS; thr++)
		{
			if(threadData[thr].curState == IDLE)
			{
				threadData[thr].ioData = todoList[tsk].inData;
				threadData[thr].curState = todoList[tsk].task;
				tsk++;
			}
		}
	}
	// terminate all threads
	for(uint8_t thr=0; thr<NUMTHREADS; thr++)
	{
		threadData[thr].curState = TERM;
		pthread_join(threads[thr], NULL);
	}
	
	printf("Time elapsed: %lfs\n", getTimeElapsed(&begTime));
}

double getTimeElapsed(struct timeval * begTime)
{
	struct timeval curTime;
	gettimeofday(&curTime, NULL);
	return (double)	((curTime.tv_usec - (*begTime).tv_usec)/1000000. +
			curTime.tv_sec - (*begTime).tv_sec);
}
