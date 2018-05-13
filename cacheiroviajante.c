#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

int main (int argc, char *argv[]) {
	int i = 0, l, c, aux[10], tam;
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
            int matriz[tam][tam];

            for(l=0; l < tam;l++){
                for(c=0; c < tam;c++){
                    fscanf(f, "%d", &distancia);
                    printf("%d ", distancia);
                    matriz[l][c] = distancia;
                }
                printf("\n");
            }

			if(strcmp(ch, "EOF")){
				printf("acabou\n");
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