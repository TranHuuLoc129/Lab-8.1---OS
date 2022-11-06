#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int numA;
int numB;
int i,j;

void* thread1(void* arg){
	 i = 1;

	while(i<= numA || j<=numB){
		pthread_mutex_lock(&mutex);
		if(i<=numA){
		
			printf("- Phia Bac len cau\n");
			printf("Nguoi thu %d o phia Bac qua cau\n", i);
			printf("- Phia Bac xong\n");
			i++;
		}
		pthread_mutex_unlock(&mutex);
		sleep(1);
		
	}
	
	pthread_exit(NULL);
	
}

void* thread2(void* arg){
	
	j = 1;

	while(j<= numB || i<=numA){
		pthread_mutex_lock(&mutex);
		if(j<=numB){
		
			printf("- Phia Nam len cau\n");
			printf("Nguoi thu %d o phia Nam qua cau\n", j);
			printf("- Phia Nam xong\n");
			j++;
		}

		pthread_mutex_unlock(&mutex);
		sleep(1);
		
	}

	pthread_exit(NULL);
	
}




int main(int argc, char* argv[]){

	printf("So nguoi lang phia Bac: \n");
	scanf("%d", &numA);

	printf("So nguoi lang phia Nam: \n");
	scanf("%d", &numB);

	pthread_t tid[2];

	pthread_create(&tid[0], NULL, thread1, &numA);
	pthread_create(&tid[1], NULL, thread2, &numB);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	return 0;
}
