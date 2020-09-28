//MIRIANE CARDOSO STEFANELLI
//RA 760933
//
//EXERCICIO MAPAS
//IMPLEMENTAÇÃO DE UMA ARVORE GERADORA MÍNIMA, ONDE TEMOS PESOS NAS ARESTAS
//SAIDA É A SOMA DAS ARESTAS QUE IDENTIFICAM O MENOR CAMINHO

#include <stdio.h>
#include <stdlib.h>
#define MAX 501

//IMPLEMENTAÇÃO LISTA DE ADJACÊNCIA
typedef struct _NoGrafo //LISTA DE ADJACENCIA
{
  struct _NoGrafo *proximo;
  int vertice;
  int peso;
} NoGrafo;

typedef struct
{
  NoGrafo *inicio;
} Lista;

typedef struct
{
  Lista *adjacente; //DOIS VERTICES SÃO ADJACENTES SE EXISTIR LIGAÇÃO ENTRE ELES
  int *marcado;
  int numeroVertices;
} Grafo;

//--------------------------------------------------------------//

//HEAP PARA MELHORAR IMPLEMENTAÇÃO DO ALGORITMO DE PRIM
typedef struct
{
  int vertice;
  int valor;
} NoHeap;

typedef struct
{
  NoHeap **vetor;
  int *posicao;
  int numeroNos; //NUMERO DE NOS PRESENTES
  int tamanho; //NUMERO MAXIMO
} Heap;

//--------------------------------------------------------------//

NoGrafo *novoNoLista(int vertice, int peso)
{
  NoGrafo *no = (NoGrafo*)malloc(sizeof(NoGrafo));

  no->vertice = vertice;
  no->peso = peso;
  no->proximo = NULL;

  return(no);
}

void inicializaGrafo(Grafo *g, int numeroVertices)
{
  g->adjacente = (Lista*)malloc(sizeof(Lista)*numeroVertices);
  g->numeroVertices = numeroVertices;

  for(int i = 0 ; i < numeroVertices ; i++)
  {
    g->adjacente[i].inicio = NULL;
    // g->marcado[i] = 0;
  }
}

void destroiGrafo(Grafo *g)
{
  for(int i = 0 ; i < g->numeroVertices ; i++)
  {
    NoGrafo *no = g->adjacente[i].inicio;

    while(no)
    {
      NoGrafo *sacrificio = no;
      no = no->proximo;

      free(sacrificio);
    }
  }
  free(g->adjacente);
  // free(g->marcado);

  g->numeroVertices = 0;
  g->adjacente = NULL;
  // g->marcado = NULL;
}

void insereAresta(Grafo *g, int vOrigem, int vDestino, int peso, int recursao) //RECEBE O VERTICE PRIMEIRO E O SEGUNDO
{
  if(g == NULL)
    return;

  //MUDANDO O ALGORITMO PORQUE O GRAFO NÃO É DIRECIONADO

  // NoGrafo *no = (NoGrafo*)malloc(sizeof(NoGrafo));
  NoGrafo *no;

  no = novoNoLista(vDestino, peso);
  no->proximo = g->adjacente[vOrigem].inicio;
  g->adjacente[vOrigem].inicio = no;
  // g->adjacente[vOrigem].inicio->peso = peso;

  if(recursao == 1)
    insereAresta(g, vDestino, vOrigem, peso, 0);
}

// void imprimir(Grafo *g)
// {
//   for(int i = 0 ; i < g->numeroVertices ; i++)
//   {
//     NoGrafo *extra = g->adjacente[i];
//
//     printf("Lista do vertice %d", i);
//
//     while(extra != NULL) //extra != NULL
//     {
//       printf(" -> %d PESO %d", extra->vertice, extra->peso);
//       extra = extra->proximo;
//     }
//     printf("\n");
//   }
// }

//--------------------------------------------------------------//

//HEAP

NoHeap *novoNo(int vertice, int valor)
{
  NoHeap *no;

  no = (NoHeap*)malloc(sizeof(NoHeap));

  no->vertice = vertice;
  no->valor = valor;

  return(no);
}

// int vazia(Heap *heap)
// {
//   if(heap->numeroNos == 0)
//    return(1);
//   return(0);
// }

Heap *inicializaHeap(int tamanho)
{
  Heap *heap;

  heap = (Heap*)malloc(sizeof(Heap));
  heap->vetor = (NoHeap**)malloc(tamanho * sizeof(NoHeap*));
  heap->posicao = (int*)malloc(tamanho * sizeof(int));

  heap->numeroNos = 0;
  heap->tamanho = tamanho;

  return(heap);
}

//MUDANDO DE LUGAR, FUNÇÃO SWAP
void trocarLugarNo(NoHeap **a, NoHeap **b)
{
  NoHeap *extra;

  extra = *a;
  *a = *b;
  *b = extra;
}

//A TAL DA HEAPIFY DA HEAP
void heapify(Heap *heap, int indice)
{
  int menor;
  int direita;
  int esquerda;

  //COLOCANDO AS POSICOES NA HEAP
  menor = indice;
  direita = (2 * indice) + 2;
  esquerda = (2 * indice) + 1;

  if(esquerda < heap->numeroNos)
    if(heap->vetor[esquerda]->valor < heap->vetor[menor]->valor)
      menor = esquerda;

  if(direita < heap->numeroNos)
    if(heap->vetor[direita]->valor < heap->vetor[menor]->valor)
      menor = direita;

  if(menor != indice)
  {
    NoHeap *noMenor, *noIndice;

    noMenor = heap->vetor[menor];
    noIndice = heap->vetor[indice];

    heap->posicao[noMenor->vertice] = indice; //TROCANDO AS POSICOES
    heap->posicao[noIndice->vertice] = menor;

    trocarLugarNo(&heap->vetor[menor], &heap->vetor[indice]);

    heapify(heap, menor);
  }
}

//RECEBER O MENOR NO
NoHeap *menorNo(Heap *heap)
{
  if(heap->numeroNos == 0)
    return(NULL);

  NoHeap *raiz, *ultimo;

  raiz = heap->vetor[0]; //GUARDA O NO RAIZ

  ultimo = heap->vetor[heap->numeroNos - 1];
  heap->vetor[0] = ultimo; //TROCA RAIZ PELO ULTIMO NO

  heap->posicao[raiz->vertice] = heap->numeroNos - 1;
  heap->posicao[ultimo->vertice] = 0;

  heap->numeroNos--; //DECREMENTANDO A HEAP

  heapify(heap, 0);

  return(raiz);
}

//DECREMENTAR O VALOR DO VERTICE
void diminuiValor(Heap *heap, int vertice, int valor)
{
  int posicao;

  posicao = heap->posicao[vertice];
  heap->vetor[posicao]->valor = valor;

  while(posicao != 0 && heap->vetor[posicao]->valor < heap->vetor[(posicao - 1) / 2]->valor)
  {
    heap->posicao[heap->vetor[posicao]->vertice] = (posicao - 1) / 2;
    heap->posicao[heap->vetor[(posicao - 1) / 2]->vertice] = posicao;

    trocarLugarNo(&heap->vetor[posicao], &heap->vetor[(posicao - 1) / 2]);

    posicao = (posicao - 1) / 2;
  }
}

//VERIFICA SE TEM NA HEAP
int verificaHeap(Heap *heap, int vertice)
{
  if(heap->posicao[vertice] >= heap->numeroNos)
    return(0);
  return(1);
}

//IMPRIMINDO HEAP
void imprimirHeap(int vetor[], int n)
{
  for(int i = 1 ; i < n ; i++)
    printf("%d - %d\n", vetor[i], i);


  // NoGrafo *extra;
  //
  // int contador = 0;
  //
  // for(int i = 1 ; i < n ; i++)
  // {
  //   extra = g.adjacente[i].inicio;
  //   contador += extra->peso;
  // }
  //
  // printf("DENTRO DO PRINT: %d", contador);
}

//ALGORITMO DE PRIM PARA ACHAR MENOR CAMINHO
int prim(Grafo *g)
{
  Heap *heap;
  int pai[g->numeroVertices];
  int menorValor[g->numeroVertices];

  int somaMenores = 0;

  heap = inicializaHeap(g->numeroVertices);

  //COLOCANDO VALORES
  for(int i = 1 ; i < g->numeroVertices ; i++)
  {
    pai[i] = -1;
    menorValor[i] = MAX;
    heap->vetor[i] = novoNo(i, menorValor[i]);
    heap->posicao[i] = i;
  }

  menorValor[0] = 0;
  heap->vetor[0] = novoNo(0, menorValor[0]);
  heap->posicao[0] = 0;

  heap->numeroNos = g->numeroVertices;

  int menorMenorValor;

  while(heap->numeroNos != 0) //ENQUANTO NÃO ESVAZIAMOS A HEAP
  {
    NoHeap *no = menorNo(heap);
    int vertice = no->vertice;

    NoGrafo *extra = g->adjacente[vertice].inicio;

    while(extra != NULL) //CHECANDO OS PROXIMOS
    {
      int v = extra->vertice;

      if(verificaHeap(heap, v))
        if(extra->peso < menorValor[v])
        {
          menorValor[v] = extra->peso;
          pai[v] = vertice;

          menorMenorValor += menorValor[v];

          // printf("MENOR VALOR DOS MENORVALOR: %d\n", menorMenorValor);

          diminuiValor(heap, v, menorValor[v]); //DECREMENTA

          somaMenores += extra->peso;

          // printf("SOMAMENORES DOS PAIS: %d\n", somaMenores);
          //
          // printf("OI\n");
          // printf("PAI[%d]: %d\n", v, pai[v]);
        }

      extra = extra->proximo;
    }
  }

  // for(int i = 1 ; i < g->numeroVertices ; i++)
  //   somaMenores += menorValor[i];

  int contador = 0;
  NoGrafo *extra;

  for(int i = 1 ; i < g->numeroVertices ; i++)
  {
    int j = pai[i];

    extra = g->adjacente[j].inicio;

    // printf("PESO DO VERTICE %d = %d \n", j, extra->peso);

    contador += extra->peso;
  }

  // printf("CONTADOR: %d\n", contador);

  // imprimirHeap(pai, g->numeroVertices);

  return(contador);
}


// int algoritmoPrim(Grafo *g, int origem, int *pai)
// {
//   int destino;
//   int primeiroElemento;
//   double menorPeso;
//
//   //INICIALIZANDO O VETOR COM -1 EM TODOS AS POSIÇÕES DOS VERTICES
//   for(int i = 0 ; i < g->numeroVertices ; i++)
//     pai[i] = (-1);
//
//   pai[origem] = origem;
//
//   while(1)
//   {
//     primeiroElemento = 1;
//
//     //PERCORRENDO TODOS OS VÉRTICES
//     for(int i = 0 ; i < g->numeroVertices ; i++)
//       if(pai[i] != -1)
//         for(int j = 0 ; j < g->marcado[i] ; j++)
//         {
//           if(pai[g->adjacente[i] == -1)
//           {
//
//           }
//
//         }
//
//     if(primeiroElemento == 1)
//       break;
//
//     pai[destino] = origem;
//   }
// }

int main()
{
  Grafo g;
  int n, m;
  int u, v, c;

  scanf("%d", &n);
  scanf("%d", &m);

  inicializaGrafo(&g, n);

  while(m != 0)
  {
    scanf("%d", &u); //ORIGEM
    scanf("%d", &v); //DESTINO
    scanf("%d", &c); //PESO

    insereAresta(&g, u - 1, v - 1, c, 1);

    m--;
  }

  printf("%d\n", prim(&g));

  // imprimir(&g);

  return(0);
}
