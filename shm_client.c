#include <sys/types.h> //for shared memory
#include <sys/ipc.h>   //for shared memory
#include <sys/shm.h>   //for shared memory
#include <stdio.h>
#include <string.h>

#define SHMSZ   50     //shared memory size
#define SHMNAME 5678   //name for shared memory

int main(int argc, char **argv)
{
	char  *temp1;
	int   count;
	key_t key = SHMNAME;    //key to locate shared memory
	int   shared_memory_id; //id associated with shared memory
	char  *shm, *s;         //access point to shared memory

	if(argc != 2)
	{
		//usage error
		printf("Usage: %s <WORD>\n", argv[0]);
		return -1;
	}

	printf("Client: looking for %d...\n", key);

	//find shared memory associated with the key
	shared_memory_id = shmget(key, SHMSZ, 0666);

	//check for error
	if(shared_memory_id < 0)
	{
		printf("        error: cannot locate shared memory...\n");
		return -1;
	}

	printf("        memory space located... attaching...\n");
	
	printf("        shared_memory_id: %d\n", shared_memory_id);

	//attach shared memory to data space
	shm = shmat(shared_memory_id, (void *)0, 0);

	//check for error
	if(shm == (char *) (-1))
	{
		printf("        error: cannot attached memory...\n");
		return -1;
	}

	printf("        memory was successfully attached!\n");

	printf("        current shared memory = %s\n", shm);

	//store WORD into shared memory
	strncpy(shm, argv[1], SHMSZ);
	
	//this method does not work
	//string must be copied over using the string library
	//shm = argv[1];

	//what the client will insert
	printf("        new shared memory = %s\n", shm);
}
