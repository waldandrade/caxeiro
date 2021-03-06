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

void reproduzir(int tam, int population_size, int MainVect[], int population[], int NUM_GERACOES){
	
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

    int l, c, i, j, cont;
    int origin_city, actual_city;
    int crossoverPoint;	
    int mutateThisGene;
	int num_filhos = population_size * 10;
	
	// SRAND REMOVIDO DE DARWIN

    for (i = 0; i < NUM_GERACOES; i++) {
        // printf ("#%d\n", i);
	    int **filhos = malloc(num_filhos * sizeof(int *)); //MODIFICADO
        //criei esse vetor para armazenar as menores distâncias
	    int **nova_geracao = malloc(population_size * sizeof(int *)); //MODIFICADO
        for (cont = 0; cont < population_size; cont++){
            nova_geracao[cont] = malloc(2 * sizeof(int));
            nova_geracao[cont][0] = -1;
            nova_geracao[cont][1] = 0;	
        }	
	
        for(l=0; l < num_filhos; l++){	
            	
            int paia = (rand()%population_size);	
            int paib = (rand()%population_size);	
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
                        actual_city = population[(paia * (tam + 1)) + c]; //MODIFICADO
                    }else{	
                        actual_city = population[(paib * (tam + 1)) + c]; //MODIFICADO
                    }	
                }	
                if(origin_city != -1){	
                    for(j = 0; j < c; j++){	
                        if(actual_city == filhos[l][j] || MainVect[(tam * origin_city) + actual_city] == 0){  	
                            actual_city = rand() % tam;  	
                            j = 0;                            	
                        }	
                    }	
                }     	
                if(origin_city != -1){	
                    filhos[l][tam] += MainVect[(tam * origin_city) + actual_city];	
                }	
                filhos[l][c] = actual_city;	
                origin_city = actual_city;	
            }	
	
            // printf("PESO: %d --\n", filhos[l][tam]);	
	
            //criei essa chamada para dentro dela fazer o calculo necessário	
            new_ger(population_size, l, filhos[l][tam], nova_geracao);	
        }	

        int z;
        for(j=0; j < population_size; j++){	
           //printf(" - %d (%d) --", j, nova_geracao[j][0]);   	
           // printf(" - %d (%d) - PESO: %d --", j, nova_geracao[j][0], nova_geracao[j][1]);    	
           // printf("\n");
           for(z = 0; z < (tam + 1); z++){
            population[(j * (tam + 1)) + z] = filhos[nova_geracao[j][0]][z];
           }		
        }	
	
        //free (nova_geracao);	
        //free (filhos);	
	
     }	     

}
