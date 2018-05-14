#include <stdlib.h>
#include <stdio.h>

void reproduzir(int tam, int population_size, int **matriz, int **population, int NUM_GERACOES){
	
	int l, c;	
	int pai;
	
	int **filhoA = malloc(tam * sizeof(*filhoA));
	int **filhoB = malloc(tam * sizeof(*filhoB));
	
	for(l=0; l < population_size-1;l++){
    filhoA[l] = malloc(tam * sizeof(*filhoA[l]));
		for(c=0; c < tam;c++){
			if(c<(tam/2)){
			pai = l;
			filhoA[l][c] = population[pai][c];
			}else{
			pai = l+1;
			filhoA[l][c] = population[pai][c];
			}
		}
		// printf("\n\n");
    }
    
    for(l=0; l < population_size-1;l++){
    filhoB[l] = malloc(tam * sizeof(*filhoB[l]));
		for(c=0; c < tam;c++){
			if(c<(tam/2)){
			pai = l+1;
			filhoB[l][c] = population[pai][c];
			}else{
			pai = l;
			filhoB[l][c] = population[pai][c];
			}
		}
		// printf("\n\n");
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
}
