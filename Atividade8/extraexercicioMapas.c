//MIRIANE CARDOSO STEFANELLI
//RA 760933
//
//IMPLEMENTAÇÃO DE UMA ARVORE GERADORA MINIMA, USANDO ALGORITMO DE PRIM
//A QUAL EU TENTEI FAZER COM LISTA E COM HEAP NO ALGORITMO DE PRIM,
//MAS A IMPLEMENTAÇÃO ERA MUITO COMPLICA, MAIS FACIL DEFINIR PESO DIREITO
//NA ARESTA ENTRE DOIS PONTOS DA MATRIZ
//SAIDA É A SOMA DAS ARESTAS DO MENOR CAMINHO

#include <stdio.h>
#include <stdlib.h>

#define MAX 501; //MAIOR NUMERO DO EXERCICIO

typedef struct
{
  int numeroVertices;
  int *marcado;
  int **adjacente;
} Grafo;

void inicializaGrafo(Grafo *g, int numeroVertices)
{
  g->numeroVertices = numeroVertices;

  g->adjacente = (int**)malloc(sizeof(int*)*numeroVertices);

  for(int i = 0 ; i < numeroVertices ; i++)
    g->adjacente[i] = (int*)malloc(sizeof(int)*numeroVertices);

  g->marcado = (int*)malloc(sizeof (int)*numeroVertices);

  for(int i = 0 ; i < g->numeroVertices ; i++)
  {
    g->marcado[i] = 0;

    for(int j = 0 ; i < g->numeroVertices ; i++)
      g->adjacente[i][j] = 0;
  }
}

void insereAresta(Grafo *g, int vOrigem, int vDestino, int peso, int recursao)
{
  if(g == NULL)
    return;

  g->adjacente[vOrigem][vDestino] = peso;

  if(recursao == 1)
    insereAresta(g, vDestino, vOrigem, peso, 0);
}

void destroiGrafo(Grafo *g)
{
  if(g != NULL)
  {
    for(int i = 0 ; i < g->numeroVertices ; i++)
      if(g->adjacente[i] != NULL)
        free(g->adjacente[i]);

    free(g->marcado);
    free(g->adjacente);
    free(g);
  }
}

void prim(Grafo *g)
{
  if(g == NULL)
    return;

  int somaMenores = 0;
  int menor = 0;
  int marcado = 0;
  int numeroVertices = g->numeroVertices;

  g->marcado[0] = 1; //MARCANDO O ZERO, O PRIMEIRO, TIPO PROFUNDIDADE

  for(int w = 0 ; w < (numeroVertices - 1) ; w++)
  {
    menor = MAX;

    for(int i = 0 ; i < numeroVertices ; i++)
    {
      if(g->marcado[i] == 1)
        for(int j = 0 ; j < numeroVertices ; j++)
          if(i != j) //NÃO CHECAR O MESMO PAR DE ARESTA
            if(g->marcado[j] != 1) //NÃO ESTA MARCADO
              if(g->adjacente[i][j] < menor && g->adjacente[i][j] != 0)
              {
                menor = g->adjacente[i][j];
                marcado = j;
              }

    }
    g->marcado[marcado] = 1;
    somaMenores += menor;
  }

  printf("%d\n", somaMenores);
}

//----------------------------------------------------//

int main()
{
  Grafo *g;
  int n, m;
  int u, v, c;

  g = (Grafo*)malloc(sizeof(Grafo));

  scanf("%d", &n);
  scanf("%d", &m);

  inicializaGrafo(g, n);

  while(m != 0)
  {
    scanf("%d", &u); //ORIGEM
    scanf("%d", &v); //DESTINO
    scanf("%d", &c); //PESO

    insereAresta(g, u - 1, v - 1, c, 1); //RECURSÃO 1 PORQUE NÃO É DIRECIONADO

    m--;
  }

  prim(g);

  destroiGrafo(g);

  return(0);
}
