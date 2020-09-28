//MIRIANE CARDOSO STEFANELLI
//RA 760933
//
//EXERCICIO GINCANA
//IMPLEMENTAÇÃO DE UMA LISTA DE ADJACENCIA E BUSCA EM PROFUNDIDADE

#include <stdio.h>
#include <stdlib.h>

// int contador = 0;

typedef struct _NoGrafo //LISTA DE ADJACENCIA
{
  struct _NoGrafo *proximo;
  int vertice;
} NoGrafo;

typedef struct
{
  NoGrafo **adjacente; //DOIS VERTICES SÃO ADJACENTES SE EXISTIR LIGAÇÃO ENTRE ELES
  int *marcado;
  int numeroVertices;
} Grafo;

void inicializaGrafo(Grafo *g, int numeroVertices)
{
  g->adjacente = (NoGrafo**)malloc(sizeof(NoGrafo*)*numeroVertices);
  g->numeroVertices = numeroVertices;
  g->marcado = (int*)malloc(sizeof(int)*numeroVertices);

  for(int i = 0 ; i < numeroVertices ; i++)
  {
    g->adjacente[i] = NULL;
    g->marcado[i] = 0;
  }
}

void destroiGrafo(Grafo *g)
{
  for(int i = 0 ; i < g->numeroVertices ; i++)
  {
    NoGrafo *no = g->adjacente[i];

    while(no)
    {
      NoGrafo *sacrificio = no;
      no = no->proximo;

      free(sacrificio);
    }
  }
  free(g->adjacente);
  free(g->marcado);

  g->numeroVertices = 0;
  g->adjacente = NULL;
  g->marcado = NULL;
}

void insereAresta(Grafo *g, int vOrigem, int vDestino, int orientacao) //RECEBE O VERTICE PRIMEIRO E O SEGUNDO
{
  if(g == NULL)
    return;
  // if(vOrigem < 0 || vOrigem >= g->numeroVertices)
  //   return;
  // else if(vDestino < 0 || vDestino >= g->numeroVertices)
  //   return;
  // else if(vDestino == vOrigem)
  //   return;

  NoGrafo *no = (NoGrafo*)malloc(sizeof(NoGrafo));

  no->proximo = g->adjacente[vOrigem];
  no->vertice = vDestino;
  g->adjacente[vOrigem] = no;

  if(orientacao == 2)
    insereAresta(g, vDestino, vOrigem, 0);
}

void buscaProfundidade(Grafo *g, int vertice)
{
  NoGrafo *no;

  g->marcado[vertice] = 1;

  for(no = g->adjacente[vertice] ; no != NULL ; no = no->proximo)
  {
    if(g->marcado[no->vertice] == 0)
    {
      // contador++;
      buscaProfundidade(g, no->vertice);
    }
  }
}

int contar(Grafo *g)
{
  int contador = 0;


  // printf("ENTROU NO CONTAR\n");

  for(int i = 0 ; i < g->numeroVertices ; i++)
    if(!g->marcado[i])
    {
      contador++;
      buscaProfundidade(g, i);
      // return(1);
      // printf("CONTADOR DENTRO DO FOR: %d\n\n", contador);
    }
  // printf("PASSOU PELO FOR\n");
  // printf("CONTADOR VALOR: %d\n", contador);

  // return(0);
  return(contador);
}

void imprimir(Grafo *g)
{
  for(int i = 0 ; i < g->numeroVertices ; i++)
  {
    NoGrafo *extra = g->adjacente[i];

    printf("Lista do vertice %d", i);

    while(extra != NULL) //extra != NULL
    {
      printf(" -> %d", extra->vertice);
      extra = extra->proximo;
    }
    printf("\n");
  }
}

void desmarcar(Grafo *g)
{
  for(int i = 0 ; i < g->numeroVertices ; i++)
    g->marcado[i] = 0;
}

int main()
{
  Grafo g;
  int n, m;
  int i, j;
  int p;

  scanf("%d", &n);
  scanf("%d", &m);

  inicializaGrafo(&g, n);

  while(m)
  {
    scanf("%d", &i);
    scanf("%d", &j);

    insereAresta(&g, i - 1, j - 1, 2);

    m--;
  }

  // imprimir(&g);

  // for(int k = 0 ; k < g.numeroVertices ; k++)
  p = contar(&g);

  printf("%d\n", p);

  destroiGrafo(&g);

  return(0);
}
