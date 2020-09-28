//NOME: MIRIANE CARDOSO STEFANELLI
//RA: 760933

#include <stdio.h>
#include <stdlib.h>

typedef struct _no {
  int dado;
  struct _no *esquerda;
  struct _no *direita;
} no;

typedef struct {
  no *raiz;
} arvore;

//INICIALIZA UMA ÁRVORE COM RAIZ NULL
void inicializar(arvore *a)
{
  a->raiz = NULL;
}

//DESALACANDO ARVORE
void limpar_no(no *n)
{
  if(n)
  {
    limpar_no(n->esquerda);
    limpar_no(n->direita);

    free(n);
  }
}
void limpar(arvore *a)
{
  limpar_no(a->raiz);
  inicializar(a);
}

//INSERINDO
no *inserir_no(no *n, int dado)
{
  if (n)
  {
    if (dado < n->dado)
      n->esquerda = inserir_no(n->esquerda, dado);

    else if (dado > n->dado)
      n->direita = inserir_no(n->direita, dado);
  }

  else
  {
    n = (no*)malloc(sizeof(no));
    n->dado = dado;
    n->esquerda = NULL;
    n->direita = NULL;
  }

  return(n);
}
void inserir(arvore *a, int dado)
{
  a->raiz = inserir_no(a->raiz, dado);
}

//IMPRIMINDO

//EM ORDEM
//BUSCA O ÚLTIMO A ESQUERDA, DEPOIS VOLTA PRO NÓ QUE COMEÇOU, IMPRIMINDO E DEPOIS TROCA E PROCURA TUDO A ESQUERDA DE NOVO E VOLTA IMPRIMINDO
void em_ordem(no *n)
{
  if(n)
  {
    em_ordem(n->esquerda);
    printf(" %d", n->dado);
    em_ordem(n->direita);
  }
}
void imprimir_ordenado(arvore *a)
{
  em_ordem(a->raiz);
  printf("\n");
}

//PRE ORDEM
//COMEÇA PRINTANDO A RAIZ
//VAI PRINTANDO TODOS OS NÓS DA ESQUERDA, QUANDO NÃO ACHA MAIS, VOLTA PRINTA O DA DIRITA E COMEÇA A PROCURAR OS DA ESQUERDA DE NOVO
void pre_ordem(no *n)
{
  if(n)
  {
    printf(" %d", n->dado);
    pre_ordem(n->esquerda);
    pre_ordem(n->direita);
  }
}
void imprimir_pre_ordenado(arvore *a)
{
  pre_ordem(a->raiz);
  printf("\n");
}

//PÓS ORDEM
//PASSA POR TODA A ÁRVORE E DEPOIS VEM FAZENDO OS PRINTS
//BUSCA O ÚLTIMO NÓ DA ESQUERDA, DEPOIS VOLTA PARA O NÓ QUE TEM QUE VOLTAR E VAI PARA A DIREITA E BUSCA O ÚLTIMO DA ESQUERDA DE NOVO, ATÉ VARRER A ÁRVORE INTEIRA E PRINTA TUDO
void pos_ordem(no *n)
{
  if(n)
  {
    pos_ordem(n->esquerda);
    pos_ordem(n->direita);
    printf(" %d", n->dado);
  }
}
void imprimir_pos_ordenado(arvore *a)
{
  pos_ordem(a->raiz);
  printf("\n");
}

//EM NIVEL
//IMPRIMI OS NÓS DE UM NIVEL DE CADA VEZ, COMEÇANDO PELA RAIZ
void em_nivel(no *n, int nivel)
{
  if(n)
  {
    if(nivel == 1)
      printf(" %d", n->dado);
    else
    {
      em_nivel(n->esquerda, nivel - 1);
      em_nivel(n->direita, nivel - 1);
    }
  }
  return;
}
int altura_em_nivel(no *n)
{
  if(n)
  {
    int esquerda_altura, direita_altura;

    esquerda_altura = altura_em_nivel(n->esquerda);
    direita_altura = altura_em_nivel(n->direita);

    if(esquerda_altura > direita_altura)
      return(esquerda_altura + 1);
    else
      return(direita_altura + 1);
  }
  return(0);
}
void imprimir_em_nivel(no *n)
{
  int a, i;

  a = altura_em_nivel(n);

  for(i = 0 ; i < a ; i++)
      em_nivel(n, i + 1);

  printf("\n");
}

int main()
{
  int tamanho, dado;
  arvore arvore, *extra;
  extra = &arvore;

  inicializar(&arvore);

  scanf("%d", &tamanho);

  for (int i = 0 ; i < tamanho ; i++)
  {
    scanf("%d", &dado);
    inserir(&arvore, dado);
  }

  //PRINTAR
  printf("Pr.:");
  imprimir_pre_ordenado(&arvore);

  printf("In.:");
  imprimir_ordenado(&arvore);

  printf("Po.:");
  imprimir_pos_ordenado(&arvore);

  printf("Ni.:");
  imprimir_em_nivel(extra->raiz);

  limpar(&arvore);
  return (0);
}
