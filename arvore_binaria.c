//ARVORE BINÁRIA

#include <stdio.h>
#include <stdlib.h>

typedef int T;

typedef struct _no {
  T dado;
  struct _no *esquerda
  struct _no *direita;
} no;

//typedef struct _no no;

typedef  struct {
  no *raiz;
  int nElementos;
} abb;

//INICIALIZA UMA ARVORE COM NENHUM ELEMENTO
void inicializar(abb *a)
{
  a->raiz = NULL; //RAIZ É UM PONTEIRO
  a->nElementos = 0;
}

//FUNÇÃO PARA VERIFICAR SE A ARVORE TEM RAIZ VAZIA. RETORNAR 1 SE SIM
int vazia(abb *a)
{
  return(a->raiz == NULL);
}

//UMA FUNÇÃO PARA LIMPAR OS NOS, RECURSIVA;
//COMEÇA A PROCURAR PELOS FILHOS E VAI PROCURANDO ELES, QUANDO ACHAR, APAGA TUDO
void limpar_no(no *n)
{
  if (n)
  {
    limpar_no(n->esquerda); //COMEÇA VIERIFICANDO PRIMEIRO OS DA ESQUERDA, DEPOIS PASSA PARA OS DA DIREITA
    limpar_no(n->direita);

    free(n); //SÓ LIBERA O N QUANDO VERIFICA SE TEM FILHOS, SE NÃO TIVER, LIMPA
  }
}

//FUNÇÃO PARA LIMPAR TUDO, SÓ QUE COMEÇA PELA RAIZ;
void limpar(abb *a)
{
  limpar_no(a->raiz);

  inicializar(a);
}

no *buscar_no(no *n, T dado)
{
  if(n)
  {
    if(dado < n->dado)
      return(buscar_no(n->esquerda, dado));

    else if (dado > n->dado)
      return(buscar_no(n->direita, dado));
  }
  return(n);
}

int buscar(abb *a, T dado)
{
  return(buscar_no(a->raiz, dado) != NULL);
}

no *inserir_no(no *n, T dado)
{
  //SE O NÓ NÃO FOR NULO ELE VAI PROCURAR NOS FILHOS
  if(!n) //SE O NÓ FOR NULO, DAI VAI COLOCAR O DADO NELE E DEFINIR OS ESQUERDA E DIREITA DELE COMO NULL
  {
    n = (no*)malloc(sizeof(no));
    n->dado = dado;
    n->esquerda = NULL;
    n->direita = NULL;

    return(n);
  }
  else
  {
    if(dado < n->dado)
      n->esquerda = inserir_no(n->esquerda, dado);

    else if (dado > n->dado)
      n->direita = inserir_no(n->direita, dado);
  }

  return(n); //VAI RETORNAR AO LADO DE QUEM VAI COLOCAR O NÓ NOVO
             //PRIMEIRAMENTE, VAI RETONAR O DE CIMA DO NÓ NOVO QUE A GENTE QUER COLOCAR, DEPOIS, VAI RETORNANDO OS DE CIMA RESPECTIVAMENTE
             //NO FINAL DA RECURSÃO, VAI RETORNAR A RAIZ REAL OFICIAL
}

void inserir(abb *a, T dado)
{
  a->raiz = inserir_no(a->raiz, dado);


}

void em_ordem(no *n)
{
  if (n)
  {
    em_ordem(n->esquerda);
    printf("%d ", n->dado);
    em_ordem(n->direita);
  }
}

void imprimir_ordenado(abb *a)
{
  em_ordem(a->raiz);
  printf("\n");
}

void pre_ordem(no *n) //RECURSIVO
{
  if (n)
  {
    printf("%d ", n->dado);
    pre_ordem(n->esquerda);
    pre_ordem(n->direita);
  }
}

void imprimir_pre_ordenado(abb *a)
{
  pre_ordem(a->raiz);
  printf("\n");
}

// void pre_ordem_iterativo(no *n) //ITERATIVO USANDO UMA PILHA
// {
//   if(!n)
//     return;
//
//   pilha p;
//
//   inicializar(&p);
//   push(&p, n);
//
//   while(!empty(&s))
//   {
//     no *e = pop(&s);
//     printf("%d ", e->dado);
//
//     if(e->direita)
//       push(&p, e->direita);
//     if(e->esquerda)
//       push(&p, e->esquerda);
//   }
//   destruir(&p);
// }

// void em_nivel_iterativo(no *n) //ORDENAÇÃO EM NÍVEL USANDO FILA
// {
//   if(!n)
//     return;
//
//   fila f;
//
//   inicializar(&f);
//   push(&f, n);
//
//   while(!empty(&f))
//   {
//     no *e = pop(&f);
//     printf("%d ", e->dado);
//
//     if(e->direita)
//       push(&f, e->direita);
//     if(e->esquerda)
//       push(&f, e->esquerda);
//   }
//   destruir(&f);
// }


int main()
{
  abb numeros;

  inicializar(&numeros);

  inserir(&numeros, 10);
  inserir(&numeros, 15);
  inserir(&numeros, 9);
  inserir(&numeros, 11);

  imprimir_ordenado(&numeros);

  limpar(&numeros);

  return (0);
}
