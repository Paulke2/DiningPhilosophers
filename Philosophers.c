#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> 
#define Num_philosophers 5
#define Num_chopsticks 5
sem_t chop_stick[5];
//sem_t hungry;
int hungry=0;
sem_t eating;
typedef struct arg_data {
	int thread_number;
} arg_data;
 
void* philosopher(void* arg)
{
	arg_data*current_thread_data = (arg_data*)arg;
 while(hungry==0);
    while (hungry<10) {
 //wait left chop, 
 sem_wait(&eating);
 	sem_wait(&chop_stick[(current_thread_data->thread_number+1)%Num_philosophers]);
	printf("philosopher %d has picked up chopstick number %d\n",current_thread_data->thread_number, ((current_thread_data->thread_number+1)%Num_philosophers));
	
	sem_wait(&chop_stick[current_thread_data->thread_number]);
      	printf("philosopher %d has picked up chopstick number %d is ready to eat\n",current_thread_data->thread_number, current_thread_data->thread_number);
	printf("philosopher %d is eating \n",current_thread_data->thread_number);
	printf("philosopher %d is finished eating! \n",current_thread_data->thread_number);

	sem_post(&eating);
	
	sem_post(&chop_stick[(current_thread_data->thread_number+1)%Num_philosophers]);
	sem_post(&chop_stick[current_thread_data->thread_number]);
hungry++;

    }
    return NULL;
}
 
int main()
{
 
 //sem_init(&hungry,0,0); 
 pthread_t id[Num_philosophers];
 arg_data arg_arr[Num_philosophers];
 sem_init(&eating,0,1);
    for (int i = 0; i < Num_philosophers; i++) {
 //init list of chopsticks
    sem_init(&chop_stick[i],0,1);
	arg_arr[i].thread_number = i;
        // create philosopher processes
        pthread_create(&id[i], NULL,
                       philosopher, &arg_arr[i]);
 
        printf("Philosopher %d is thinking\n", i);
	if(i == Num_philosophers -1){
		//this is so they all become hungry at the same time
		hungry =1;
	}
    }
 
    for (int i = 0; i < Num_philosophers; i++){
 
        pthread_join(id[i], NULL);
}
return 0;
}
