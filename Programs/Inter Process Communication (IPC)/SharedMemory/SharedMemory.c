#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	int segmentId;
	char* segmentPtr;
	struct shmid_ds segmentStatBuf;

	/* Allocate a shared memory segment */
	segmentId = shmget(IPC_PRIVATE, getpagesize(), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	/* Attach shared memory segment to linux provided memory address */
	segmentPtr = (char*) shmat(segmentId, NULL, SHM_RND);
	printf("Shared memory is attached at %p\n", segmentPtr);
	/* Determine segment size */
	shmctl(segmentId, SHM_STAT, &segmentStatBuf);
	printf("Segment size : %u\n", (unsigned int)segmentStatBuf.shm_segsz);
	/* Write a string to the shared memory segment */
	sprintf(segmentPtr, "hello");
	/* Detach Shared memory segment */
	shmdt(segmentPtr);

	/* Attach shared memory segment to user provided memory address */
	segmentPtr = (char*) shmat(segmentId, (void*) 0x5000000, 0);
	printf("Shared memory is reattached at %p\n", segmentPtr);
	/* Print out the string from shared memory */
	printf("%s", segmentPtr);
	/* Detach Shared memory segment */
	shmdt(segmentPtr);

	/* Deallocate the shared memory segment */
	shmctl(segmentId, IPC_RMID, 0);
	return 0;
}

