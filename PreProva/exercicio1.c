#include <stdio.h>

void in_order(node *n, lista *l)
{
  if(n)
  {
    in_order(n->esq, l);
    l->inserir(n->data);
    in_order(n->dir, l);
  }
}

int verif(abb *arvore)
{
  lista l;
  in_order(arvore->raiz, &l);
}
