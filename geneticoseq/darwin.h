#include <stdlib.h>
#include <stdio.h>

void reproduzir(int tam, int population_size, int **population){

    int l, c;

    //printf("5. iniciando exibição de população \n");
    for(l=0; l < population_size; l++){
        for(c=0; c < tam; c++){
            printf("%d ", population[l][c]);
        }
        printf(" -- PESO: %d -- \n", population[l][tam]);        
        printf("\n");
    }

}