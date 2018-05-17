#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define MUTATION_RATE    0.05

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

void reproduzir(int tam, int population_size, int **matriz, int **population, int NUM_GERACOES){
	
	int l, c;	
	int paiA, paiB;
	
	int **filhoA = (int **)malloc(tam * sizeof(int *));
	int **filhoB = (int **)malloc(tam * sizeof(int *));
	
	for(l=0; l < population_size-1;l+=2){
    	filhoA[l] = (int *)malloc(tam * sizeof(int));
    	filhoB[l] = (int *)malloc(tam * sizeof(int));
    	paiA = l;
    	paiB = l + 1;
		for(c=0; c < tam;c++){
			if(c<(tam/2)){
				filhoA[l][c] = population[paiA][c];
				filhoB[l][c] = population[paiB][c];
			}else{
				filhoA[l][c] = population[paiB][c];
				filhoB[l][c] = population[paiA][c];
			}
		}
		// printf("\n\n");
    }
    
}

	/*
    //printf("5. iniciando exibição de população \n");
    for(l=0; l < population_size; l++){
        for(c=0; c < tam; c++){
            printf("%d ", population[l][c]);
        }
        printf(" -- PESO: %d -- \n", population[l][tam]);        
        printf("\n");
    }
	*/
