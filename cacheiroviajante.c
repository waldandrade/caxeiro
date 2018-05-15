#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "geneticoseq\primeira_ninhada.h"
#include "geneticoseq\darwin.h"

#define MAX 100
#define POP_SIZE 5
#define NUM_GERACOES 50

int main (int argc, char *argv[]) {
	int i = 0, j, cont, l, c, aux[10], tam;
	char ch[MAX], nome[MAX];

    /*
    Lê o arquivo como argumento
    */
	FILE *f = fopen(argv[1], "r");

    // loop linha a linha ate achar o fim do arquivo
	for(i=0;strcmp(ch, "EOF") != 0;i++){
        if(i == 1){
            fscanf(f, "%s", &aux);
			fscanf(f, "%d", &tam); // Pega dimensao do grafo
			printf("%s: %d\n", aux, tam);
		}
		if(i > 1){
			fgets(ch, MAX, f);
			fgets(ch, MAX, f);
            fgets(ch, MAX, f); 
            int distancia;     
            int **matriz = malloc(tam * sizeof(*matriz));       

            for(l=0; l < tam;l++){
                matriz[l] = malloc(tam * sizeof(*matriz[l]));
                for(c=0; c < tam;c++){
                    fscanf(f, "%d", &distancia);
                    matriz[l][c] = distancia;
                    // printf("%d ", matriz[l][c]);
                }
                // printf("\n\n");
            }
            
            printf("Matriz carregada! \n\n");
      
            int **population = malloc(POP_SIZE * sizeof(*population));
            for (j = 0; j < POP_SIZE; j++){
                //o tamanho de cada indivíduo deve ser tam + 1 para que o último elemento armazene o peso/distância
                population[j] = malloc((tam+1) * sizeof(*population[j]));
            }

            primeira_ninhada(tam, POP_SIZE, matriz, population);

            /*
             * 
             * População tem a primeira geração. O ideal é que continuemos passando a referência para que não precisemos mexer muito a estrutura.
             * 
             */
            reproduzir(tam, POP_SIZE, matriz, population, NUM_GERACOES);

            int melhor_distancia = NULL;
            for(j = 0; j < POP_SIZE; j++){
                int distancia = population[j][tam];
                if(melhor_distancia == NULL || distancia < melhor_distancia){
                    melhor_distancia = distancia;
                }
            }

			if(strcmp(ch, "EOF")){
				printf("A melhor distância encontrada é: %d \n", melhor_distancia);
				fclose(f);
				break;
			}
		}
		// salva nome do arquivo e consome linhas
		if(i < 1){
			if(i==0){
				fscanf(f, "%s", ch);
				fscanf(f, "%s", nome);
				fgets(ch, MAX, f);
			}
			else{
				fgets(ch, MAX, f); 
			}
		}
	}
    
}
