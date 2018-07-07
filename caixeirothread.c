#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include "geneticoseq\primeira_ninhada.h"
#include "geneticothread\darwin.h"

#define MAX 100
#define POP_SIZE 100
#define NUM_GERACOES 100

int main (int argc, char *argv[]) {
	int i = 0, j, l, c, tam;
	char ch[MAX] = "1", nome[MAX], aux[10];
    /*
    Lê o arquivo como argumento
    */
    int t_number = atoi(argv[1]);
    printf("Num of threads %d\n", t_number);

    tdata_t *my_data;
    my_data = (tdata_t *) malloc(sizeof(tdata_t));
    my_data->num_geracoes = NUM_GERACOES;
    my_data->population_size = POP_SIZE;

	FILE *f = fopen(argv[2], "r");
	
	//inicializando a função randômica
    srand(time(0));

    // loop linha a linha ate achar o fim do arquivo
	for(i=0;strcmp(ch, "EOF") != 0;i++){
        if(i == 1){
            fscanf(f, "%s", aux);
			fscanf(f, "%d", &tam); // Pega dimensao do grafo     
            my_data->tam = tam;
		}
		if(i > 1){
			int distancia;     
            my_data->matriz = (int **)malloc(my_data->tam * sizeof(int *));
            my_data->population = (int **)malloc(my_data->population_size * sizeof(int *));
            
			fgets(ch, MAX, f);
			fgets(ch, MAX, f);
            fgets(ch, MAX, f); 
            
            for(l=0; l < my_data->tam;l++){
                my_data->matriz[l] = (int *) malloc(my_data->tam * sizeof(int));
                for(c=0; c < my_data->tam;c++){
                    fscanf(f, "%d", &distancia);
                    my_data->matriz[l][c] = distancia;
                    // printf("%d ", matriz[l][c]);
                }
                // printf("\n\n");
            }
                  
            for (j = 0; j < my_data->population_size; j++){
                //o tamanho de cada indivíduo deve ser tam + 1 para que o último elemento armazene o peso/distância
                my_data->population[j] = (int *)malloc((my_data->tam+1) * sizeof(int));
            }
            primeira_ninhada(my_data->tam, my_data->population_size, my_data->matriz, my_data->population);

            pthread_t threads[t_number];
            for (j = 0; j < t_number; j++){
                pthread_t t1;
                pthread_create(&(threads[j]), NULL, reproduzir, (void *)(&my_data));
            }

            for (j = 0; j < t_number; j++){
                pthread_join(threads[j], NULL);
            }

            //reproduzir(tam, POP_SIZE, matriz, population, NUM_GERACOES);

            int melhor_distancia = -1;
            for(j = 0; j < my_data->population_size; j++){
                int distancia = my_data->population[j][my_data->tam];
                if(melhor_distancia == -1 || distancia < melhor_distancia){
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
	return 0;
}
