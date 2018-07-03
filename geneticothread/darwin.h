#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define MUTATION_RATE    0.05

typedef struct thread_data {
 int **geracao;
 int filho;
 int distancia;
} tdata_t;

int pop_size = 0;

//void new_ger(int population_size, int filho, int distancia, int **geracao){
void *new_ger(void *args){

    tdata_t *my_data;
    my_data = *(tdata_t **) args;

    int **geracao = my_data->geracao;
    int filho = my_data->filho;
    int distancia = my_data->distancia;

    int i;
    int maior_indice = 0;
    for(i=0; i < pop_size; i++){
        if(geracao[i][0] == -1){
            maior_indice = i;
            break;
        }
        else if(geracao[i][1] > geracao[maior_indice][1]){ 
            maior_indice = i;
        }
    }
    if(geracao[maior_indice][0] == -1 || distancia < geracao[maior_indice][1]){
        geracao[maior_indice][0] = filho;
        geracao[maior_indice][1] = distancia;
    }
}

void reproduzir(int tam, int population_size, int **matriz, int **population, int NUM_GERACOES){
	
	// int l, c;	
	// int paiA, paiB;
	
	// int **filhoA = (int **)malloc(tam * sizeof(int *));
	// int **filhoB = (int **)malloc(tam * sizeof(int *));
	
	// for(l=0; l < population_size-1;l+=2){
    // 	filhoA[l] = (int *)malloc(tam * sizeof(int));
    // 	filhoB[l] = (int *)malloc(tam * sizeof(int));
    // 	paiA = l;
    // 	paiB = l + 1;
	// 	for(c=0; c < tam;c++){
	// 		if(c<(tam/2)){
	// 			filhoA[l][c] = population[paiA][c];
	// 			filhoB[l][c] = population[paiB][c];
	// 		}else{
	// 			filhoA[l][c] = population[paiB][c];
	// 			filhoB[l][c] = population[paiA][c];
	// 		}
	// 	}
    // }

    pop_size = population_size;

    int l, c, i, j, cont;
    int origin_city, actual_city;
    int crossoverPoint;	
    int mutateThisGene;
	int num_filhos = pop_size * 10;
    srand(time(NULL));

    for (i = 0; i < NUM_GERACOES; i++) {
        printf ("#%d\n", i);
	    int **filhos = malloc(num_filhos * sizeof(*filhos));
        //criei esse vetor para armazenar as menores distâncias
	    int **nova_geracao = (int **)malloc(pop_size * sizeof(int *));
        for (cont = 0; cont < pop_size; cont++){
            nova_geracao[cont] = (int *)malloc(2 * sizeof(int));
            nova_geracao[cont][0] = -1;
            nova_geracao[cont][1] = 0;	
        }	
	
        for(l=0; l < num_filhos; l++){	
            	
            int paia = (rand()%pop_size);	
            int paib = (rand()%pop_size);	
            // o espaço final servirá para o peso/distância	
            filhos[l] = malloc((tam + 1) * sizeof(int)); //MODIFICADO
            filhos[l][tam] = 0;	
 	
            origin_city = -1;	
            	
            crossoverPoint  =  rand() % tam;	
	
            mutateThisGene = rand() % (int)(1.0 / MUTATION_RATE);	
            for(c=0; c < tam;c++){	
                if(mutateThisGene == 0){                    	
                    actual_city = rand() % tam;
                    mutateThisGene = 1;  //MODIFICADO
                }else{	
                    if(c<crossoverPoint){	
                        actual_city = population[paia][c];        	
                    }else{	
                        actual_city = population[paib][c];                    	
                    }	
                }	
                if(origin_city != -1){	
                    for(j = 0; j < c; j++){	
                        if(actual_city == filhos[l][j] || matriz[origin_city][actual_city] == 0){  	
                            actual_city = rand() % tam;  	
                            j = 0;                            	
                        }	
                    }	
                }     	
                if(origin_city != -1){	
                    filhos[l][tam] += matriz[origin_city][actual_city];	
                }	
                filhos[l][c] = actual_city;	
                origin_city = actual_city;	
            }	
	
            // printf("PESO: %d --\n", filhos[l][tam]);	
	
            tdata_t *my_data;
            my_data = (tdata_t *) malloc(sizeof(tdata_t));
            my_data->geracao = nova_geracao;
            my_data->filho = l;
            my_data->distancia = filhos[l][tam];

            //criei essa chamada para dentro dela fazer o calculo necessário	
            pthread_t t1;
            pthread_create(&t1, NULL, new_ger, (void *)(&my_data));
            pthread_join(t1, NULL);

            // new_ger(pop_size, l, filhos[l][tam], nova_geracao);	
        }	
	
        for(j=0; j < pop_size; j++){	
           //printf(" - %d (%d) --", j, nova_geracao[j][0]);   	
           printf(" - %d (%d) - PESO: %d --", j, nova_geracao[j][0], nova_geracao[j][1]);    	
           printf("\n");	
           population[j] = filhos[nova_geracao[j][0]];	
        }	
	
        //free (nova_geracao);	
        //free (filhos);	
	
     }	     

}

// Criando as threads
// pthread_t t1,t2;
// pthread_create(&t1, NULL, reproduzir, (void*)(&tam));
// pthread_join(t1, NULL);
