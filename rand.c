#include <stdio.h>  
#include <stdlib.h>
#include <time.h>

//mudar pra variavel "tam" pra receber a quantia de cidades (para assim fazer a corrente de "1" a N e de volta a "1"
const int NUM=100;
int main()
{
	printf("\n\nPrograma para gerar numeros aleatorios"); //pode ser apagado...

	//declaração das variáveis
	int vetor[NUM], i=0, j=0, cont_linha=0; //usado pra fazer a lista de linhas randomicas

	//inicializando função randômica
	srand(time(NULL));

	//preenchendo o vetor de 100 posições. //modificar pra fazer os vetores das cidades
	for(i=0; i<NUM; i++)
	{
		vetor[i] = (rand()%NUM)+1;

		//verificando se o número já existe, afim de evitar elementos repetidos

		for(j=0; j<i; j++)
		{
			if(vetor[j] == vetor[i])
			{
				vetor[i] = (rand()%NUM)+1;
				j=0;
			}
		}
	}

	printf("\n\n");

	for(i=0; i<NUM; i++)
	{
		printf("%i\t", vetor[i]);
		cont_linha++;

		if(cont_linha == 10)
		{
			printf("\n");
			cont_linha=0;
		}
	}
}
