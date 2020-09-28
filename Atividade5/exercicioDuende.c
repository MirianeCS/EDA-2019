//MIRIANE CARDOSO STEFANELLI
//RA 760933
//
//EXERCICIO DUENDE PERDIDO
//IMPLEMENTAÇÃO DE UM GRAFO EM MATRIZ DE ADJACENCIA E BUSCA EM LARGURA COM AUXILIO DE FILA

#include <stdio.h>
#include <stdlib.h>
#define MAX 10 //NUMERO MÁXIMO DADO PELO EXERCÍCIO

typedef struct
{
  int numeroVertices;
  int numeroArestas;
  int *marcado;
  char **adjacente;
} Grafo;

//----------------------------------------------------------//

typedef struct _no
{
  struct _no *proximo;
  int valor;
} No;

typedef struct
{
  No *primeiro;
  int indice;
} Fila;

//----------------------------------------------------------//
//FILA

void iniciarFila(Fila *f)
{
  // f = (Fila*) malloc(sizeof(Fila));
  f->primeiro = NULL;
  f->indice = 0;
}

int vaziaFila(Fila *f)
{
  if(f->primeiro)
    return (0);
  else
    return (1);
}

int tamanhoFila(Fila *f)
{
  return(f->indice);
}

void destroiFila(Fila *f)
{
  if(f->primeiro)
  {
    No *extra = f->primeiro;
    No *extra2;

    if(extra->proximo == NULL)
      free(extra);

    while(extra->proximo)
    {
      extra2 = extra;
      extra = extra->proximo;
      free(extra2);
    }
    f->primeiro = NULL;
  }
}

void insereFila(Fila *f, int dado)
{
  No *novo = (No*)malloc(sizeof(No));
  novo->valor = dado;

  No *extra = f->primeiro;

  if(f->primeiro)
  {
    while(extra->proximo != NULL)
      extra = extra->proximo;

    extra->proximo = novo;
    novo->proximo = NULL;
  }
  else
  {
    f->primeiro = novo;
    novo->proximo = NULL;
  }

  f->indice++;
}

int removeFila(Fila *f)
{
  int extra;
  No *extra2;

  extra2 = f->primeiro;
  extra = extra2->valor;

  f->primeiro = f->primeiro->proximo;

  free(extra2);

  if(f->indice != 0)
    f->indice--;

  return(extra);
}

int primeiroF(Fila *f)
{
  if(f->primeiro == NULL)
    return (0);

  No *extra = f->primeiro;

  while(extra->proximo != NULL)
    extra = extra->proximo;

  return(extra->valor);
}

void imprimiFila(Fila *f)
{
  No *extra = f->primeiro;

  while(extra != NULL)
  {
    printf("%d ", extra->valor);
    extra = extra->proximo;
  }
  printf("\n");
}

//----------------------------------------------------------//
//GRAFOS

void percursoLargura(Grafo *g, int v, Fila *f)
{
  int vertice;

  iniciarFila(f);

  g->marcado[v] = 1;
  insereFila(f, v);

  while(!vaziaFila(f))
  {
    vertice = primeiroF(f);

    removeFila(f);

    for(int i = 0 ; i < g->numeroVertices ; i++)
      if(g->adjacente[vertice][i] == 1 && !g->marcado[i])
      {
        g->marcado[i] = g->marcado[vertice] + 1;
        insereFila(f, i);
      }
  }
}

void adicionaAresta(Grafo *g, int vertice1, int vertice2)
{
  if(g == NULL)
    return;
  else
  {
    g->adjacente[vertice1][vertice2] = 1;
    g->numeroArestas++;
  }
}

int adicionaArestaGrafo(int labirinto[MAX][MAX], Grafo *g, int linhas, int colunas)
{
  int retorno = 0;
  for(int i = 0 ; i < linhas ; i++)
    for(int j = 0 ; j < colunas ; j++)
      if(labirinto[i][j] != 2) //NÃO PODE SER DOIS PORQUE O 2 É PAREDE DE CRISTAL
      {
        if(i > 0)
          if(labirinto[i - 1][j] != 2)
          {
            adicionaAresta(g, (i * colunas) + j, ((i - 1) * colunas) + j);
            retorno = 1;
          }

        if((i + 1) < linhas) //FINAL DAS LINHAS
          if(labirinto[i + 1][j] != 2)
          {
            adicionaAresta(g, (i * colunas) + j, ((i + 1) * colunas) + j);
            retorno = 1;
          }

        if(j > 0)
          if(labirinto[i][j - 1] != 2)
          {
            adicionaAresta(g, (i * colunas) + j, ((i * colunas) + (j - 1)));
            retorno = 1;
          }

        if((j + 1) < colunas) //FINAL DAS COLUNAS
          if(labirinto[i][j + 1] != 2)
          {
            adicionaAresta(g, (i * colunas) + j, ((i * colunas) + (j + 1)));
            retorno = 1;
          }
      }
  return(retorno);
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

void inicializaGrafo(Grafo *g, int numeroVertices)
{
  g->numeroVertices = numeroVertices;
  g->numeroArestas = 0;

  g->adjacente = (char**)malloc(sizeof(char*)*numeroVertices);

  for(int i = 0 ; i < numeroVertices ; i++)
    g->adjacente[i] = (char*)malloc(sizeof(char)*numeroVertices);

  g->marcado = (int*)malloc(sizeof (int)*numeroVertices);
}

int main()
{
  int linhas, colunas;
  int saidaI, saidaJ;
  int labirinto[MAX][MAX];
  Grafo *g;
  int extra;
  int menor = 1000;
  Fila f;
  int retorno;

  g = (Grafo*)malloc(sizeof(Grafo));

  scanf("%d", &linhas);
  scanf("%d", &colunas);

  inicializaGrafo(g, linhas * colunas); //MATRIZ QUADRADA

  for(int i = 0 ; i < linhas ; i++)
    for(int j = 0 ; j < colunas ; j++)
    {
      scanf("%d", &labirinto[i][j]); //MONTANDO MATRIZ
    }

  for(int i = 0 ; i < linhas ; i++)
    for(int j = 0 ; j < colunas ; j++)
      if(labirinto[i][j] == 3) //ACHANDO COORDENADAS DA SAÍDA
      {
        saidaI = i;
        saidaJ = j;
      }

  retorno = adicionaArestaGrafo(labirinto, g, linhas, colunas);

  // if(retorno == 0)
  //   printf("DEU RUIM AQUI\n");

  percursoLargura(g, saidaI * colunas + saidaJ, &f);

  for(int i = 0 ; i < linhas ; i++) //ACHANDO O MENOR CAMINHO
    for(int j = 0 ; j < colunas ; j++)
      if(labirinto[i][j] == 0 && g->marcado[(i * colunas) + j])
      {
        extra = g->marcado[i * colunas + j] - 1;

        if(extra < menor)
        {
          // printf("MENOR ANTERIOR: %d\n", menor);
          // printf("EXTRA: %d\n", extra);
          menor = extra;
          // printf("NOVO MENOR: %d\n\n", menor);
        }
      }

  printf("%d\n", menor);

  // imprimiFila(&f);

  destroiFila(&f);
  destroiGrafo(g);
  return(0);
}
