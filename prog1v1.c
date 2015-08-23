#include <stdio.h>
#include <time.h>
#include <sys/time.h> 
#include <limits.h>
#include <math.h>

double tempo()
{
	struct timeval tv;
	gettimeofday(&tv,0);
	return tv.tv_sec + tv.tv_usec/1e3;
}

int main(void) {
	double t1,t2;
    int elapsedTime;
	srand(time(NULL));
	int i, j, m, k;
	int menorvalor[3]; 		/* Onde a posição 0 é o valor, a posição 1 é a coordenada I e a 2 a coordenada J */
	int maiorvalor[3];		/* Onde a posição 0 é o valor, a posição 1 é a coordenada I e a 2 a coordenada J */
	int maiorpi[2];			/* Onde a posição 0 é o valor, a posição 1 é a coordenada I */
	int menorpi[2];			/* Onde a posição 0 é o valor, a posição 1 é a coordenada I */
	int desviopadrao;

	while(1) {
		printf("Digite o valor de M:");
		scanf ("%d",&m);
		printf("Digite o valor de K:");
		scanf ("%d",&k);

		if(m == 0 || k == 0) {
			break;
		}

		int matriz[m][k];
		int produtointerno[m]; //para guardar os resultados dos cálculos do produto interno.

		for(i = 0; i < m; i++) {
			for(j = 0; j < k; j++) {
				matriz[i][j] = (rand() % 100) - 50;
			}
		}

		menorvalor[0] = 50;
		maiorvalor[0] = -50;

		/*Começar contador*/
		t1 = tempo();

		/* Acha o menor e o maior valor da matriz */
		for(i = 0; i < m; i++) {
			for(j = 0; j < k; j++) {
				if(matriz[i][j] < menorvalor[0]) {
					menorvalor[0] = matriz[i][j];
					menorvalor[1] = i;
					menorvalor[2] = j;
				}

				if(matriz[i][j] > maiorvalor[0]) {
					maiorvalor[0] = matriz[i][j];
					maiorvalor[1] = i;
					maiorvalor[2] = j;
				}
			}
		}

		printf("O menor valor eh %d com coordenada %dx%d \n", menorvalor[0], menorvalor[1], menorvalor[2]);
		printf("O maior valor eh %d com coordenada %dx%d \n", maiorvalor[0], maiorvalor[1], maiorvalor[2]);

		/* Calcula os produtos internos */
		for(i = 0; i < m; i++) { 
			produtointerno[i] = 0;
			for(j = 0; j < k; j++) {
				produtointerno[i] += matriz[i][j] * matriz[j][i];
			}
		}

		/* Calcula o menor e maior valor e desvio padrão dos produtos internos */
		maiorpi[0] = INT_MIN;
		menorpi[0] = INT_MAX;
		desviopadrao = 0;
		double somapi = 0.0;
		for(i = 0; i < m; i++) {
			if(produtointerno[i] < menorpi[0]) {
				menorpi[0] = produtointerno[i];
				menorpi[1] = i;
			}
			if(produtointerno[i] > maiorpi[0]) {
				maiorpi[0] = produtointerno[i];
				maiorpi[1] = i;
			}
			somapi += produtointerno[i];
		}

		double media = somapi / m;
		printf("O menor valor do PI eh %d com coordenada %d\n", menorpi[0], menorpi[1]);
		printf("O maior valor do PI eh %d com coordenada %d\n", maiorpi[0], maiorpi[1]);		
		printf("A media do produto interno eh %lf\n", media);

		somapi = 0.0;
		for(i = 0; i < m; i++) {
			somapi += (produtointerno[i] - media) * (produtointerno[i] - media);
		}
		// double desvio = sqrt((somapi/m));
		// printf("O desvio padrao eh %lf\n", desvio);

		t2 = tempo();
		/*Terminar contador*/

		printf("O tempo para executar essas funções foi de %lfms \n", t2 - t1);
	}

	printf("O programa terminou.\n");
}