#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/shm.h>
#define SIZE 256

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void* thread(void* arg){  //vo
	pthread_mutex_lock(&mutex);
	
	FILE * fp;

	//
	int *shm, shmid;
	key_t key;
		
	key =ftok(".",1) ;
		
	shmid = shmget(key, SIZE, IPC_CREAT | 0666);
	
	shm = (int *) shmat(shmid, 0,0);
	//


	if ((fp = fopen(arg, "r")) == NULL) {
            printf("\nCannot open file.");
            return 0;
	}

	char arr[20];

	while(fgets(arr, 20, fp) != NULL){
		
		if(arr[0] == '+'){
			arr[0] = ' ';
			shm[0] = shm[0] + atoi(arr);
		}
		else{
			arr[0] = ' ';
			shm[0] = shm[0] - atoi(arr);
			if(shm[0] < 0){
				printf("Warning: Balance under 0.00\n");
			}
		}
	}
	pthread_mutex_unlock(&mutex);

	sleep(1);
	
	if(shm[0] < 0){
		printf("Warning: Balance under 0.00\n");
	}
	else{
		printf("Final Balance: %d\n",shm[0]);
	}
	
}


int main(int argc, char* argv[]){

	int *shm, shmid;
	key_t key;

	if((key =ftok(".",1)) == -1){
		
		
		perror("Key created.\n");
		return 1;
	}

	shmid = shmget(key, SIZE, IPC_CREAT | 0666);
	if(shmid == -1){

		
		perror ("Shared memory created.\n");
		return 2;

	}
	
	shm = (int *) shmat(shmid, 0,0);
	
	shm[0] = 0;

	int numthread = argc -1;

	pthread_t tid[numthread];


	int i; 

	for(i=0; i< numthread; i++){
	      pthread_create(&tid[i], NULL, thread, argv[i+1]);
	}

	for(i = 0; i<numthread; i++){
		pthread_join(tid[i], NULL);
		
	}


	

	return 0;
}
