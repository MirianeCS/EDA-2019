//MIRIANE CARDOSO STEFANELLI
//RA 760933
//
//IMPLEMENTAÇÃO DE ORDENAÇÃO TOPOLÓGICA USANDO ALGORITMO DE KHAN
//E UMA LISTA DE ADJACENCIA. INSERÇÃO DOS NOS EM UMA HEAP (PEDIDO PELO PROFESSOR)
//SE NÃO POSSUIR MANEIRA DE REALIZAR AS TAREFAS, PRINTA *
//OU, SE POSSUIR, PRINTA O CAMINHO

#include <stdio.h>
#include <stdlib.h>

//IMPLEMENTAÇÃO LISTA DE ADJACÊNCIA
typedef struct _NoGrafo //LISTA DE ADJACENCIA
{
  struct _NoGrafo *proximo;
  int vertice;
} NoGrafo;

typedef struct
{
  NoGrafo *inicio;
  int grau;
  int tamanho;
} Lista;

typedef struct
{
  Lista *adjacente; //DOIS VERTICES SÃO ADJACENTES SE EXISTIR LIGAÇÃO ENTRE ELES
  int *marcado;
  int numeroVertices;
} Grafo;

//--------------------------------------------------------------//

//HEAP PARA MELHORAR IMPLEMENTAÇÃO DO ALGORITMO
typedef struct
{
  int vertice;
  int valor;
} NoHeap;

typedef struct
{
  int *vetor;
  int numeroNos; //NUMERO DE NOS PRESENTES
  int tamanho; //NUMERO MAXIMO
  int *posicao;
} Heap;

//-------------------------------------------------------//

NoGrafo *novoNoLista(int vertice)
{
  NoGrafo *no = (NoGrafo*)malloc(sizeof(NoGrafo));

  no->vertice = vertice;
  no->proximo = NULL;

  return(no);
}

void inicializaGrafo(Grafo *g, int numeroVertices)
{
  g->adjacente = (Lista*)malloc(sizeof(Lista)*numeroVertices);
  g->numeroVertices = numeroVertices;
  g->marcado = (int*)malloc(sizeof(int)*numeroVertices);

  for(int i = 0 ; i < numeroVertices ; i++)
  {
    g->adjacente[i].inicio = NULL;
    g->adjacente[i].tamanho = 0;
    g->adjacente[i].grau = 0;
    g->marcado[i] = 0;
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
  free(g->marcado);

  g->numeroVertices = 0;
  g->adjacente = NULL;
  g->marcado = NULL;
}

void insereAresta(Grafo *g, int vOrigem, int vDestino) //RECEBE O VERTICE PRIMEIRO E O SEGUNDO
{
  if(g == NULL)
    return;

  NoGrafo *no;

  // printf("CHEGOU AQUI\n");

  no = (NoGrafo*)malloc(sizeof(NoGrafo));

  if(g->adjacente[vOrigem].tamanho == 0)
    no->proximo = NULL;
  else
    no->proximo = g->adjacente[vOrigem].inicio;

  no->vertice = vDestino;
  g->adjacente[vOrigem].inicio = no;
  g->adjacente[vOrigem].tamanho++;

  g->adjacente[vDestino].grau++;

  // printf("INSERIU NO GRAFO\n");
}

//-------------------------------------------------------//

NoHeap *novoNo(int vertice, int valor)
{
  NoHeap *no;

  no = (NoHeap*)malloc(sizeof(NoHeap));

  no->vertice = vertice;
  no->valor = valor;

  return(no);
}

int verificaHeap(Heap *heap, int vertice)
{
  if(heap->vetor[vertice] >= heap->numeroNos)
    return(0);
  return(1);
}

//MUDANDO DE LUGAR, FUNÇÃO SWAP
void trocarLugarNo(Heap *heap, int a, int b)
{
  int extra;

  extra = heap->vetor[a];
  heap->vetor[a] = heap->vetor[b];
  heap->vetor[b] = extra;
}

void inserirHeap(Heap *heap, int dado)
{
  if(heap == NULL)
    return;

  // printf("ENTROU NO INSERIR\n");

  int posicao;
  posicao = heap->numeroNos;

  heap->vetor[posicao] = dado;

  while(posicao != 0 && (heap->vetor[posicao] < heap->vetor[(posicao - 1) / 2]))
  {
    trocarLugarNo(heap, posicao, (posicao - 1) / 2);
    posicao = (posicao - 1) / 2;
  }

  heap->numeroNos++;
}

int vazia(Heap *heap)
{
  if(heap->numeroNos == 0)
   return(1);
  return(0);
}

//A TAL DA HEAPIFY DA HEAP
void heapify(Heap *heap, int indice)
{
  int menor;
  int direita;
  int esquerda;

  menor = indice;
  direita = (2 * indice) + 2;
  esquerda = (2 * indice) + 1;

  if(direita < heap->numeroNos)
    if(heap->vetor[direita] < heap->vetor[menor])
      menor = direita;

  if(esquerda < heap->numeroNos)
    if(heap->vetor[esquerda] < heap->vetor[menor])
      menor = esquerda;

  if(menor != indice)
  {
    int noMenor, noIndice;

    noMenor = heap->vetor[menor];
    noIndice = heap->vetor[indice];

    heap->posicao[noMenor] = indice;
    heap->posicao[noIndice] = menor;

    trocarLugarNo(heap, menor, indice);

    heapify(heap, menor);
  }
}

int menorNo(Heap *heap)
{
  if(heap->numeroNos == 0)
    return(0);

  int raiz, ultimo;

  raiz = heap->vetor[0]; //GUARDA O NO RAIZ

  ultimo = heap->vetor[heap->numeroNos - 1];
  heap->vetor[0] = ultimo; //TROCA RAIZ PELO ULTIMO NO

  heap->posicao[raiz] = heap->numeroNos - 1;
  heap->posicao[ultimo] = 0;

  heap->numeroNos--; //DECREMENTANDO A HEAP

  heapify(heap, 0);

  return(raiz);
}

int primeiroElemento(Heap *heap)
{
  if(heap == NULL)
    return(0);

  if(heap->numeroNos == 1) //APENAS UM ELEMENTO
  {
    heap->numeroNos--;
    return(heap->vetor[heap->numeroNos]);
  }

  int primeiro = heap->vetor[0]; //GUARDANDO A RAIZ

  heap->numeroNos--;
  heap->vetor[0] = heap->vetor[heap->numeroNos];

  heapify(heap, 0);

  return(primeiro);
}

void imprimirHeap(int vetor[], int n)
{
  for(int i = 1 ; i < n ; i++)
    printf("%d - %d\n", vetor[i], i);
}

Heap *inicializaHeap(int tamanho)
{
  Heap *heap;

  heap = (Heap*)malloc(sizeof(Heap));
  heap->vetor = (int*)malloc(tamanho * sizeof(int));
  heap->posicao = (int*)malloc(tamanho * sizeof(int));

  heap->numeroNos = 0;
  heap->tamanho = tamanho;

  return(heap);
}

void resultado(Grafo *g, int contador, int vetorAlgoritmo[])
{
  if(contador == g->numeroVertices)
    for(int i = 0 ; i < g->numeroVertices ; i++)
      printf("%d\n", vetorAlgoritmo[i]);
  else
    printf("*\n");
}

//ORDENAÇÃO TOPOLOGIA SLIDE AULA 10
void ordenacaoKahn(Grafo *g)
{
  Heap *heap;
  int *vetorAlgoritmo;
  int primeiro;
  int contador = 0; //INICIA CONTADOR
  int v = g->numeroVertices;
  NoGrafo *extra;

  heap = inicializaHeap(g->numeroVertices); //INICIALIZA FILA


  for(int i = 0 ; i < v ; i++)
    if(g->adjacente[i].grau == 0)
    {
      if(g->marcado[i] == 0)
      {
        // printf("OI\n");
        inserirHeap(heap, i); //INSERE NA FILA
        // printf("PASSOU DO INIHEAP\n");
      }
    }

  vetorAlgoritmo = (int*)malloc(sizeof(int)*v);

  while(heap->numeroNos != 0) //ENQUANTO NÃO ESTIVER VAZIA
  {
    // printf("ENTROU NO ALG\n");
    primeiro = primeiroElemento(heap); //RETIRA O PRIMEIRO ELEMENTO

    extra = g->adjacente[primeiro].inicio; //RECEBE O PRIMEIRO ELEMENTO

    while(extra != NULL)
    {
      g->adjacente[extra->vertice].grau--; //REDUZ GRAU DE ENTRADA DOS ADJAENTES

      if(g->adjacente[extra->vertice].grau == 0)
        inserirHeap(heap, extra->vertice); //QUANDO FOREM FONTES, INSERIR EM S

      extra = extra->proximo; //PULA PARA O PROXIMO
    }

    vetorAlgoritmo[contador] = primeiro; //SALVANDO ELEMENTOS PARA IMPRIMIR DEPOIS
    contador++;
    // printf("CONTADOR: %d\n", contador);
  }

  // printf("NUMERO DE VERTICES: %d\n", g->numeroVertices);

  resultado(g, contador, vetorAlgoritmo);

  free(heap);
  free(vetorAlgoritmo);
}


int main()
{
  Grafo g;
  int n, m;
  int a, b;

  scanf("%d", &n);
  scanf("%d", &m);

  // printf("ANTES DO INICIALIZA\n");

  inicializaGrafo(&g, n);

  // printf("CHEGOU AQUI\n");

  while(m != 0)
  {
    scanf("%d", &a);
    scanf("%d", &b);

    insereAresta(&g, a, b); //NÃO PRECISA FAZER -1 PORQUE JÁ VEM COM O NUMERO CERTO

    m--;
  }

  ordenacaoKahn(&g);

  destroiGrafo(&g);

  return(0);
}
