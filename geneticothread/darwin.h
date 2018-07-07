#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define MUTATION_RATE    0.05

typedef struct thread_data {
 int **matriz;
 int **population;
 int num_geracoes;
 int tam;
 int population_size;
 } tdata_t;

int pop_size = 0;

void new_ger(int population_size, int filho, int distancia, int **geracao){
    int i;
    int maior_indice = 0;
    for(i=0; i < population_size; i++){
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


void *reproduzir(void *args){

    printf("Eu sou uma thread!");

    tdata_t *my_data;
    my_data = *(tdata_t **) args;

    int **population = my_data->population;
    int **matriz = my_data->matriz;
    int tam = my_data->tam;
    int pop_size = my_data->population_size;
    int NUM_GERACOES = my_data->num_geracoes;

    int l, c, i, j, cont;
    int origin_city, actual_city;
    int crossoverPoint;	
    int mutateThisGene;
	int num_filhos = pop_size * 10;
	
	// SRAND REMOVIDO DE DARWIN

    for (i = 0; i < NUM_GERACOES; i++) {
	    int **filhos = malloc(num_filhos * sizeof(int *)); //MODIFICADO
        //criei esse vetor para armazenar as menores distâncias
	    int **nova_geracao = malloc(pop_size * sizeof(int *)); //MODIFICADO
        for (cont = 0; cont < pop_size; cont++){
            nova_geracao[cont] = malloc(2 * sizeof(int));
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

            	
            new_ger(pop_size, l, filhos[l][tam], nova_geracao);	

            // new_ger(pop_size, l, filhos[l][tam], nova_geracao);	
        }	
	
        for(j=0; j < pop_size; j++){	
           //printf(" - %d (%d) --", j, nova_geracao[j][0]);   	
           // printf(" - %d (%d) - PESO: %d --", j, nova_geracao[j][0], nova_geracao[j][1]);    	
           // printf("\n");	
           population[j] = filhos[nova_geracao[j][0]];	
        }	
	
	
     }	     

}