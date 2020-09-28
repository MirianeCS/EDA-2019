//MIRIANE CARDOSO STEFANELLI
//RA 760933
//
//EXERCICIO IR E VIR
//IMPLEMENTAÇÃO DE UM BUSCA EM PROFUNDIDADE PARA GARANTIR QUE AS RUAS TENHAM INTERSECÇÃO
//IMPLEMENTAÇÃO DE UM PONTEIRO PARA PONTEIRO

#include <stdio.h>
#include <stdlib.h>

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
      buscaProfundidade(g, no->vertice);
  }
}

int verificar(Grafo *g, int vertice)
{
  buscaProfundidade(g, vertice);

  for(int i = 0 ; i < g->numeroVertices ; i++)
    if(!g->marcado[i])
      return (0);

  return (1);
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
  int v, w, orientacao;
  int p;

  scanf("%d", &n);
  scanf("%d", &m);

  while(n != 0 || m != 0)
  {
    inicializaGrafo(&g, n);

    for(int i = m ; i != 0 ; i--)
    {
      scanf("%d", &v);
      scanf("%d", &w);
      scanf("%d", &orientacao);

      insereAresta(&g, v - 1, w - 1, orientacao);
    }

    p = 1;

    // imprimir(&g);
    for(int i = 0 ; i < g.numeroVertices && p != 0; i++)
    {
      p = verificar(&g, i);
      desmarcar(&g);
    }

    printf("%d\n", p);


    scanf("%d", &n);
    scanf("%d", &m);
  }

  destroiGrafo(&g);
  return (0);
}
