//MIRIANE CARDOSO STEFANELLI
//RA 760933

//ATIVIDADE 2
//EXERCÍCIO POÇÃO
//IMPLEMENTANDO DUAS ÁRVORES E PROCURANDO OS VALORES MAIOR OU IGUAL PARA EMBALAGEM E MENOR OU IGUAL PARA LÍQUIDO
//USANDO FUNÇÃO DE CEILING E FLOOR RECURSIVAS

#include <stdio.h>
#include <stdlib.h>

typedef struct _no{
  struct _no *direita;
  struct _no *esquerda;
  int dado;
  // int bal; //ALTURA DIREITA - ALTURA ESQUERDA
} no;

typedef struct{
  no *raiz;
} arvore;

//INICIALIZANDO A ARVORE COM RAIZ NULA
void inicializar(arvore *a)
{
  a->raiz = NULL;
}

//VERIFICANDO SE A ARVORE ESTA VAZIA
int vazia(arvore *a) //RETORNA 1 SE ESTIVER VAZIA
{
  return(a->raiz == NULL);
}

//DESALOCANDO A ARVORE
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

//PROCURAR LIQUIDO MENOR OU IGUAL AO TAMANHO DA GARRAFA
int procurarLiquido_no(no *n, int valor)
{
  int menorIgual;

  if(n != NULL)
  {
    if(n->dado == valor) //SE FOR IGUAL, ACHAMOS O VALOR MÁXIMO
      return(n->dado);

    if(n->dado > valor) //SE FOR MAIOR, SÓ PODE ESTAR NA ESQUERDA
      return procurarLiquido_no(n->esquerda, valor);

    menorIgual = procurarLiquido_no(n->direita, valor); //PROCURANDO NA ARVORE DA DIREITA

    if(menorIgual <= valor)
      return(menorIgual);
    else
      return(n->dado);
  }
  return(100001);
}
int procurarLiquido(arvore *a, int valor)
{
  return(procurarLiquido_no(a->raiz, valor));
}

//PROCURAR EMBALAGEM MAIOR OU IGUAL AO DA GARRAFA
int procurarEmbalagem_no(no *n, int valor)
{
  int maiorIgual;

  if(n != NULL)
  {
    if(n->dado == valor) //SE FOR IGUAL, ACHAMOS O VALOR MÁXIMO
      return(n->dado);

    if(n->dado < valor) //SE FOR MENOR, SÓ PODE ESTAR NA DIREITA
      return(procurarEmbalagem_no(n->direita, valor));

    maiorIgual = procurarEmbalagem_no(n->esquerda, valor); //PROCURANDO NA ARVORE DA ESQUERDA

    if(maiorIgual >= valor)
      return(maiorIgual);
    else
      return(n->dado);
  }
  return(-1);
}
int procurarEmbalagem(arvore *a, int valor)
{
  return(procurarEmbalagem_no(a->raiz, valor));
}

// void em_ordem(no *n)
// {
//   if(n)
//   {
//     em_ordem(n->esquerda);
//     printf(" %d", n->dado);
//     em_ordem(n->direita);
//   }
// }
//
// void imprimir_ordenado(arvore *a)
// {
//   em_ordem(a->raiz);
//   printf("\n");
// }


// int maiorIgual_no(no *n, int valor)
// {
//   int extra, maiorIgual;
//   if (n)
//   {
//     extra = maiorIgual_no(n->esquerda, valor);
//     if(extra >= valor)
//       maiorIgual = extra;
//     extra = maiorIgual_no(n->direita, valor);
//     return(maiorIgual);
//   }
//   return(-1);
// }
//
// int maiorIgual(arvore *a, int valor)
// {
//   return(maiorIgual_no(a->raiz, valor));
// }

int main()
{
  int quantidade, dado, valor;
  arvore arvoreLiquido, arvoreEmbalagem;

  inicializar(&arvoreLiquido);
  inicializar(&arvoreEmbalagem);

  //VERIFICANDO QUANTO LIQUIDO
  scanf("%d", &quantidade);

  for(int i = 0 ; i < quantidade ; i++)
  {
    scanf("%d", &dado);
    inserir(&arvoreLiquido, dado);
  }

  //VERIFICANDO QUANTAS EMBALAGENS
  scanf("%d", &quantidade);

  for(int i = 0 ; i < quantidade ; i++)
  {
    scanf("%d", &dado);
    inserir(&arvoreEmbalagem, dado);
  }

  //VERIFICANDO NUMERO DE GARRAFA
  scanf("%d", &quantidade);

  for(int i = 0 ; i < quantidade ; i++)
  {
    scanf("%d", &valor);

    int liquido = procurarLiquido(&arvoreLiquido, valor);
    int embalagem = procurarEmbalagem(&arvoreEmbalagem, valor);

    if(liquido <= valor && embalagem >= valor)
      printf("%d %d\n", liquido, embalagem);

    else
      printf("descartar\n");
  }

  //DESALOCANDO ARVORE
  limpar(&arvoreEmbalagem);
  limpar(&arvoreLiquido);

  return(0);
}
