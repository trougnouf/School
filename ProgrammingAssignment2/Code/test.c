#include "test.h"

int main()
{
	initializeTheThings();
	
	pthread_t threads[MAXTHREADS];
	pthreadData threadData[MAXTHREADS];
	
	for(int i=0; i<MAXTHREADS; i++)
	{
		threadData[i].curTask = IDLE;
		pthread_create(threads[i], NULL, thread_structureHandler. (void *) threadData[i]);
	}

	
	// testing spam
	printf("50 %d\n", slInsert(50));
	printf("50 %d\n", slInsert(50));
	printf("48 %d\n", slInsert(48));
	printf("52 %d\n", slInsert(52));
	printf("56 %d\n", slInsert(56));
	printf("70 %d\n", slInsert(70));
	printf("2 %d\n", slInsert(2));
	printf("50 %d\n", slInsert(50));
	printf("1 %d\n", slInsert(1));
	printf("2 %d\n", slInsert(2));
	printf("4 %d\n", slInsert(4));
	printf("3 %d\n", slInsert(3));
	printf("6 %d\n", slInsert(6));
	printf("5 %d\n", slInsert(5));
	printf("10 %d\n", slInsert(10));
	printf("9 %d\n", slInsert(9));
	printf("%d\n", slFind(0));
	printf("%d\n", slFind(11));
	printf("%d\n", slFind(50));
	printf("%d\n", slFind(70));
	printf("%d\n", slRemove(50));
	printf("%d\n", slFind(50));
	printf("%d\n", slFind(70));
}