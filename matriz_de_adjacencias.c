#include <stdio.h>
#include <stdlib.h>
#define vertices int

struct grafoMatriz {
	int Vertices;
	int Arestas;
	int **MatrizDeAdjacencia;
};

typedef struct grafoMatriz *GrafoMatriz;

GrafoMatriz InicializarGrafoMatriz(int V, int A);
static int **CriarMatriz(int linha, int coluna, int valor);
void inserirArestasGrafoNaoDirecionado(GrafoMatriz G, int v, int w);
void MostrarMatrizDeAdjacenciaGrafoNaoDirecionando(GrafoMatriz G);
void MostrarGrauDosVertices(int QTDvertices, int MatrizGrausDosVertices[][2]);

void main(){
	int i, j, QTDvertices, QTDarestas;
	
	//LEITURA DE ARQUIVOS VIA FORMATO DIMACS
	FILE *arquivo;
	arquivo = fopen("grafo.txt", "r");
	fscanf(arquivo, "%d%d", &QTDvertices, &QTDarestas);
	int matrizDeArestas[QTDarestas][2], MatrizGrausDosVertices[QTDvertices][2];

	printf("O grafo tem %d vertices e %d arestas.\n", QTDvertices, QTDarestas);
	for(i=0; i < QTDarestas; i++){
		for(j=0; j < 2; j++){
			fscanf(arquivo, "%d", &matrizDeArestas[i][j]);
		}
	}
	
	fclose(arquivo);

	GrafoMatriz MeuGrafoMatriz = InicializarGrafoMatriz(QTDvertices, QTDarestas);
	
	int v, w;
	j = 0;
	for(vertices i=0; i < QTDarestas; i++){
		v = matrizDeArestas[i][j];
		w = matrizDeArestas[i][j+1];
		inserirArestasGrafoNaoDirecionado(MeuGrafoMatriz, v-1, w-1);
	}

	MostrarMatrizDeAdjacenciaGrafoNaoDirecionando(MeuGrafoMatriz);

	int grau = 0;
	for(vertices i=0; i < QTDvertices; ++i){
		MatrizGrausDosVertices[i][0] = i + 1;
		for(vertices j=0; j < QTDvertices; ++j){
			if(MeuGrafoMatriz->MatrizDeAdjacencia[i][j] == 1){
				grau++;
			}
		}
		MatrizGrausDosVertices[i][1] = grau;
		grau = 0;
	}
	
	MostrarGrauDosVertices(QTDvertices, MatrizGrausDosVertices);

}

GrafoMatriz InicializarGrafoMatriz(int V, int A){
	GrafoMatriz G = malloc(sizeof *G);
	G->Vertices = V;
	G->Arestas = A;
	G->MatrizDeAdjacencia = CriarMatriz(V, V, 0);
	return G;
}


static int **CriarMatriz(int linha, int coluna, int valor){
    int **m = malloc(linha * sizeof (int *));
    for(vertices i = 0; i < linha; ++i)
    	m[i] = malloc(coluna * sizeof(int *));

    for(vertices i = 0; i < linha; ++i){
    	for(vertices j = 0; j < coluna; ++j)
    		m[i][j] = valor;
   }
    return m;
}

void inserirArestasGrafoNaoDirecionado(GrafoMatriz G, vertices v, vertices w){
	if(G->MatrizDeAdjacencia[v][w] == 0){
		G->MatrizDeAdjacencia[v][w] = 1;
		G->MatrizDeAdjacencia[w][v] = 1;
	}
}

void MostrarMatrizDeAdjacenciaGrafoNaoDirecionando(GrafoMatriz G){
	printf("Matriz de Adjacências do Grafo não direcionado:\n");
	for(vertices v = 0; v < G->Vertices; ++v){
		for(vertices w = 0; w < G->Vertices; ++w)
			printf( "%2d ", G->MatrizDeAdjacencia[v][w]);
		printf("\n");
	}
}

void MostrarGrauDosVertices(int QTDvertices, int MatrizGrausDosVertices[][2]){
	int v, grau = 0;
	printf("\nGraus dos vértices:\n");
	for(vertices i=0; i < QTDvertices; ++i){
		v = MatrizGrausDosVertices[i][0];
		grau = MatrizGrausDosVertices[i][1];
		printf("Vértice %d o grau é %d\n",v,grau);
	}
}
