#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void primeira_ninhada(int tam, int population_size, int **matriz, int **population){

	//printf("\n\n-- Criando a primeira população aleatória -> "); //pode ser apagado...

    //inicializando a função randômica
    srand(time(NULL));


    int origin_city, actual_city;
    int cont, i, j;
    for(cont=0; cont<population_size; cont++)
	{
       population[cont][tam] = 0;
       origin_city = -1;
       //printf("1.  no laço para geração de população! \n");
       //preenchendo o vetor de 100 posi��es. //modificar pra fazer os vetores das cidades
        for(i=0; i<tam; i++)
        {
            
            actual_city = (rand()%tam);

            if(origin_city != -1){
                while( origin_city != -1 && matriz[origin_city][actual_city] == 0) {
                   actual_city = (rand()%tam);
                }

                //verificando se o n�mero j� existe, afim de evitar elementos repetidos
                for(j=0; j<i; j++)
                {
                    if(population[cont][j] == actual_city)
                    {
                        actual_city = (rand()%tam);
                        j=0;
                    }
                }
        
                // printf("--- origin: %d, destiny: %d =>", origin_city, actual_city);
                // printf(" distancy: %d ---\n", matriz[origin_city][actual_city]);
                population[cont][tam] += matriz[origin_city][actual_city];
            }
            population[cont][i] = actual_city;
            origin_city = actual_city;
        }                     
    }
}