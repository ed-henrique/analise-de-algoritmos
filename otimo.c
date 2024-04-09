/* Arquivo otimo.c
*  Aluno: Herbert Oliveira Rocha - UFRR
*  Projeto e Analise de Algoritmos
* */
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>

struct timeval t1, t2;
double elapsedTime;
/*para o calculo do tempo*/
unsigned long time_diff(struct timeval a, struct timeval b){
	struct timeval res;
	timersub(&a, &b, &res);
	return res.tv_sec * 1000000 + res.tv_usec;
}
int N; /* numero de vertices */
int *ciclo; /* ciclo atual */

int *melhor_ciclo; /* melhor ciclo encontrado */
int *melhor_ciclo2; /* melhor ciclo obtido com 2opt */

int *explorado; /* vetor para armazenar se o vertice foi explorado pelo DFS*/
int **g; /* matriz de distancias */
int nivel=0; /* profundidade alcancada pelo DFS*/
int min=10000; /* usado para selecionar o menor ciclo */

int medeciclo(int *t){
	int i;
	int l=0;
	for(i=0;i<N-1;i++)
		l=l+g[t[i]][t[i+1]];
		l=l+g[t[N-1]][t[0]];

	return l;
}

/* Esta funcao implementa o algoritmo DFS modificado para
* poder percorrer todos os caminhos possiveis. Apos o retorno, o vertice
* eh desmarcado como explorado, permitindo que ele seja explorado novamente */
void dfs(int v, int nivel){
	int i,j,dist;
	explorado[v]=1;
	ciclo[nivel]=v;
	if(nivel==N-1){
		/* completou um ciclo */
		dist=medeciclo(ciclo);		
		if(dist<min){
			min=dist;			
			for(j=0;j<N;j++)
				melhor_ciclo[j]=ciclo[j];
		}
	}
	for(i=0;i<N;i++){
		if(!explorado[i]){
			dfs(i,nivel+1);
			explorado[i]=0;
		}
	}
}

int main(int argc, char **argv){
	int i,j,k;
	FILE *fd;
	double l; /* comprimento do ciclo */	
	char buf[20];	
	/* Testa os argumentos da linha de comando */
	if(argc!=2){
		printf("Uso: %s <arquivo>\n", argv[0]);
		exit(0);
	}
	fd=fopen(argv[1],"r");	
	do{
		fscanf(fd,"%s",buf);
		if(strcmp(buf,"DIMENSION:")==0)
			fscanf(fd," %d",&N);
		else if(strcmp(buf,"DIMENSION")==0)
			fscanf(fd," : %d",&N);
	}while(strcmp(buf,"EDGE_WEIGHT_SECTION")!=0);
	
	 /* Aloca memoria para os vetores e matrizes */
	ciclo=(int*)malloc(N*sizeof(int));
	explorado=(int*)malloc(N*sizeof(int));
	melhor_ciclo=(int*)malloc(N*sizeof(int));
	g=(int**)malloc(N*sizeof(int*));
	
	for(i=0;i<N;i++)
		g[i]=(int*)malloc(N*sizeof(int));	
	/* Leitura da matriz g */
	for(i=0;i<N;i++){
		g[i][i]=0;
		for(j=i+1;j<N;j++){
			fscanf(fd,"%d",&g[i][j]);
			g[j][i]=g[i][j];
		}
	}
	//para o tempo inicial
	gettimeofday(&t1, NULL);
	for(i=0;i<N;i++)
		explorado[i]=0;		
		dfs(0,0);	
	/* Resultado */
	for(i=0;i<N;i++)
		printf("%d\n",melhor_ciclo[i]);
	//printf("------ %d\n", medeciclo(melhor_ciclo));
	//para o tempo final
	gettimeofday(&t2, NULL);
	//imprimi o tempo em milisegundos								
	printf("\n Tempo de Execucao: ---> %lf \n",time_diff(t2, t1)/100000.0);		
	return 0;
}
