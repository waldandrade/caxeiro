#include <stdlib.h>
#include <stdio.h>

void primeira_ninhada(int tam, int **matriz){
    int l, c;
    for(l=0; l < tam; l++){
        for(c=0; c < tam; c++){
            printf("%d ", matriz[l][c]);
        }
        printf("\n");
    }
}