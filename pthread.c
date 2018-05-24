#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define SIZE 10

int v[SIZE];

void * function (void *arg){
	int valor = *(int*)(arg);
	int i;
	if(valor == 1){
		printf("thread 1 executando\n");
		for(i=0;i<SIZE/2;i++){
			v[i] = 1;
		}
	}
	else{
		printf("thread 2 executando\n");
		for(i=SIZE/2;i<SIZE;i++){
			v[i] = 2;
		}
	}
}

int main(){

	pthread_t t1,t2;
	int a1 = 1;
	int a2 = 2;
	int i;
	
	pthread_create(&t1, NULL, function, (void*)(&a1));
	pthread_create(&t2, NULL, function, (void*)(&a2));
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	for(i = 0; i < SIZE; i++){
		printf("%d ", v[i]);
	}
	printf("\n");
	
	exit(0);
}

/*
//thread com numero de gera��es
	pthread_t thread0[NUM_GERACOES/2];
	pthread_t thread1[NUM_GERACOES/2];
	
	//vetor de N posi��es
	int N = NUM_GERACOES;

	pthread thread0, thread1;
		
	//criar a thread
	for(i=0,i<N/2,i++){
		pthread_create(&thread0[i], NULL, minha_funcao_de_entrada,(void *)(&filhoA));
	}
	//criar a thread
	for(i=N/2,i<N,i++){
		pthread_create(&thread1[i], NULL, minha_funcao_de_entrada,(void *)(&filhoB));
	}	
	//juntando as threads
	for(i=0,i<N/2,i++){
		pthread_join(thread0[i], NULL);
	}
	//juntando as threads
	for(i=N/2,i<N,i++){
		pthread_join(thread1[i], NULL);
	}
*/

/*

#include <pthread.h>
#include <stdio.h>

//this function is run by the second thread
void *inc_x(void *x_void_ptr)
{

// increment x to 100
int *x_ptr = (int *)x_void_ptr;
while(++(*x_ptr) < 100);

printf("x increment finished\n");

// the function must return something - NULL will do
return NULL;

}

int main()
{

int x = 0, y = 0;

//show the initial values of x and y
printf("x: %d, y: %d\n", x, y);

// this variable is our reference to the second thread
pthread_t inc_x_thread;

// create a second thread which executes inc_x(&x)
if(pthread_create(&inc_x_thread, NULL, inc_x, &x)) {

fprintf(stderr, "Error creating thread\n");
return 1;

}
// increment y to 100 in the first thread
while(++y < 100);

printf("y increment finished\n");

// wait for the second thread to finish
if(pthread_join(inc_x_thread, NULL)) {

fprintf(stderr, "Error joining thread\n");
return 2;

}

// show the results - x is now 100 thanks to the second thread
printf("x: %d, y: %d\n", x, y);

return 0;

}

*/
