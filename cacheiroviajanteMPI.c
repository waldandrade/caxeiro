#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "CaicheiroMPI\primeira_ninhada.h"
#include "CaicheiroMPI\darwin.h"

#include<mpi.h>

#define MAX 100
#define POP_SIZE 500
#define NUM_GERACOES 100

int main (int argc, char *argv[]) {
	
	int i = 0, j, l, c, tam;
	char ch[MAX] = "1", nome[MAX], aux[10];

	int id, qtdnodes, n;
	
	MPI_Status status;
	
	MPI_Init(&argc,&argv); /* inicializacao */

	MPI_Comm_rank(MPI_COMM_WORLD, &id); /* quem sou? */

	MPI_Comm_size(MPI_COMM_WORLD, &qtdnodes); /* quantos s�o? */

    /*
    Lê o arquivo como argumento
    */
	FILE *f = fopen(argv[1], "r");
	
	//inicializando a função randômica
    srand(time(0)+id); //MODIFICADO

    // loop linha a linha ate achar o fim do arquivo
	for(i=0;strcmp(ch, "EOF") != 0;i++){
        if(i == 1){
            fscanf(f, "%s", aux);
			fscanf(f, "%d", &tam); // Pega dimensao do grafo
			printf("%s: %d\n", aux, tam);
		}
		if(i > 1){
			int distancia;
            int MainVect[tam * tam];
            int vec = 0;
			int **matriz = (int **)malloc(tam * sizeof(int *));
            int population[POP_SIZE * (tam + 1)];
            
			fgets(ch, MAX, f);
			fgets(ch, MAX, f);
            fgets(ch, MAX, f); 
            
            for(l=0; l < tam;l++){
                matriz[l] = (int *) malloc(tam * sizeof(int));
                for(c=0; c < tam;c++){
                    fscanf(f, "%d", &distancia);
                    matriz[l][c] = distancia;
                    // printf("%d ", matriz[l][c]);
                }
                // printf("\n\n");
            }
            
            for(l = 0; l < tam; l++){
            	for(c = 0; c < tam; c++){
            		MainVect[vec] = matriz[l][c];
            		vec = vec + 1;
				}
			}
		
	if (id==0) { /* sou o zero? */

		primeira_ninhada(tam, POP_SIZE, MainVect, population);

		for (j = 0; j < qtdnodes; j++){
			MPI_Send(&population, (POP_SIZE * (tam+1)), MPI_INT, j, 100, MPI_COMM_WORLD);
		}

	}else{ /* sou um dos outros */

		MPI_Recv(&population, (POP_SIZE * (tam+1)), MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
	
	}

	reproduzir(tam, POP_SIZE, MainVect, population, NUM_GERACOES);

	/* termina */
			

            int melhor_distancia = -1;
            for(j = 0; j < POP_SIZE; j++){
                int distancia = population[(j * (tam+1)) + tam];
                if(melhor_distancia == -1 || distancia < melhor_distancia){
                    melhor_distancia = distancia;
                }
            }

			if(strcmp(ch, "EOF")){
				printf("Sou o processo %d e a melhor distância que encontrei foi: %d \n", id, melhor_distancia);
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

	MPI_Finalize();

	return 0;

}
