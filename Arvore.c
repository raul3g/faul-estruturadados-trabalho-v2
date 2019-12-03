#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

typedef struct no No;

struct arvore
{
  No *raiz;
};

struct no
{
  int info;
  char cor;
  No *pai;
  No *esq;
  No *dir;
};

No *criar_no(int valor)
{
  No *no = malloc(sizeof(No));
  no->info = valor;
  no->cor = 'V';
  no->dir = NULL;
  no->esq = NULL;
  no->pai = NULL;
  return no;
}

Arvore *criar()
{
  Arvore *arv = malloc(sizeof(Arvore));
  arv->raiz = NULL;
  return arv;
}

void desalocar_nos_rec(No *no)
{
  if (no != NULL)
  {
    desalocar_nos_rec(no->esq);
    desalocar_nos_rec(no->dir);
    free(no);
  }
}

void destruir(Arvore *arv)
{
  desalocar_nos_rec(arv->raiz);
  free(arv);
}
void rotacionar_esq(Arvore *arv, No *no)
{
  if (arv->raiz != NULL)
  {
    No *raiz = arv->raiz;
    while (raiz != NULL)
    {
      //Encontrou
      if (no == raiz)
      {
        if (no->dir != NULL)
        {
          if (no == arv->raiz)
          {
            arv->raiz = no->dir;
            no->dir->pai = NULL;
          }
          else if (no->pai->esq != NULL && no->pai->esq == no)
          {
            no->pai->esq = no->dir;
            no->dir->pai = no->pai;
          }
          else
          {
            no->pai->dir = no->dir;
            no->dir->pai = no->pai;
          }
          raiz = no->dir;
          no->pai = raiz;
          no->dir = raiz->esq;
          if (raiz->esq)
          {
            raiz->esq->pai = no;
          }

          raiz->esq = no;
        }
        return;
      }
      else
      {
        raiz = no->info > raiz->info ? raiz->dir : raiz->esq;
      }
    }
  }
}

void rotacionar_dir(Arvore *arv, No *no)
{
  if (arv->raiz != NULL)
  {
    No *raiz = arv->raiz;
    while (raiz != NULL)
    {

      if (no == raiz)
      {
        if (no->esq != NULL)
        {
          if (no == arv->raiz)
          {

            arv->raiz = no->esq;
            no->esq->pai = NULL;
          }
          else if (no->pai->esq != NULL && no->pai->esq == no)
          {
            no->pai->esq = no->esq;
            no->esq->pai = no->pai;
          }
          else
          {
            no->pai->dir = no->esq;
            no->esq->pai = no->pai;
          }

          raiz = no->esq;
          no->pai = no->esq;
          no->esq = raiz->dir;
          if (raiz->dir)
          {
            raiz->dir->pai = no;
          }
          raiz->dir = no;
        }
        return;
      }
      else
      {
        raiz = no->info > raiz->info ? raiz->dir : raiz->esq;
      }
    }
  }
}

void balancear_ins(Arvore *arv, No *no)
{
  No *pai = no->pai;
  if (pai != NULL)
  {
    while (pai != NULL && pai->cor == 'V' && pai->pai != NULL)
    {
      No *avo = pai->pai;

      if (avo->dir != NULL && pai == avo->dir)
      {
        //Irmao vermelho
        if (avo->esq != NULL && avo->esq->cor == 'V')
        {

          if (avo->pai != NULL)
            avo->cor = 'V';
          avo->esq->cor = 'P';
          avo->dir->cor = 'P';
          no = avo;
        }
        //Irmao Preto
        else
        {
          if (no == pai->esq)
            rotacionar_dir(arv, pai);
          avo->cor = 'V';
          avo->dir->cor = 'P';
          rotacionar_esq(arv, avo);
          return;
        }
      }
      //Simetria
      else
      {
        //Irmao Vermelho
        if (avo->dir != NULL && avo->dir->cor == 'V')
        {

          if (avo->pai != NULL)
            avo->cor = 'V';

          avo->esq->cor = 'P';
          avo->dir->cor = 'P';
          no = avo;
        }
        //Irmao Preto
        else
        {
          if (no == pai->dir)
            rotacionar_esq(arv, pai);
          avo->cor = 'V';
          avo->esq->cor = 'P';
          rotacionar_dir(arv, avo);
          return;
        }
      }
      pai = no->pai;
    }
  }
  else
  {
    no->cor = 'P';
  }
}

void inserir(Arvore *arv, int valor)
{
  if (arv->raiz != NULL)
  {
    No *no = arv->raiz;
    while (no != NULL)
    {

      if (no->info == valor)
      {
        return;
      }
      if (valor > no->info && no->dir != NULL)
      {
        no = no->dir;
      }
      else if (valor < no->info && no->esq != NULL)
      {
        no = no->esq;
      }
      else
      {

        No *x = criar_no(valor);
        if (x->info > no->info)
        {
          no->dir = x;
        }
        else
        {
          no->esq = x;
        }
        x->pai = no;

        balancear_ins(arv, x);
        break;
      }
    }
  }
  else
  {
    No *x = criar_no(valor);
    arv->raiz = x;
    balancear_ins(arv, x);
  }
}

void balancear_rem(Arvore *arv, No *no)
{
  while (no != arv->raiz && (no != NULL && no->cor == 'P'))
  {

    No *pai = no->pai;
    if (no == pai->esq)
    {
      No *irmao = pai->dir;
      if (irmao != NULL)
      {
        //Irmao vermelho
        if (irmao->cor == 'V')
        {
          pai->cor = 'V';
          irmao->cor = 'P';
          rotacionar_esq(arv, pai);
        }
        else
        {
          //Irmao preto
          //Sd preto
          if (irmao->dir == NULL || irmao->dir->cor == 'P')
          {

            //Se preto
            if (irmao->esq == NULL || irmao->esq->cor == 'P')
            {

              irmao->cor = 'V';
              no = pai;
            }
            //Ir preto, se preto e sd vermelho
            else
            {
              irmao->cor = 'V';
              if (irmao->dir != NULL)
                irmao->dir->cor = 'P';
              rotacionar_dir(arv, irmao);
            }
          }
          //Irmao preto e sd vermelho
          else
          {
            irmao->cor = pai->cor;
            pai->cor = 'P';
            if (irmao->dir != NULL)
              irmao->dir->cor = 'P';
            rotacionar_esq(arv, pai);
            no = arv->raiz;
          }
        }
      }
      else
      {
        no = pai;
      }
    }
    //Simetria
    else
    {
      No *irmao = pai->esq;
      if (irmao != NULL)
      {
        //Irmao vermelho
        if (irmao->cor == 'V')
        {
          pai->cor = 'V';
          irmao->cor = 'P';
          rotacionar_esq(arv, pai);
        }
        else
        {
          //Irmao preto
          //Se preto
          if (irmao->esq == NULL || irmao->esq->cor == 'P')
          {

            //Sd preto
            if (irmao->dir == NULL || irmao->dir->cor == 'P')
            {
              irmao->cor = 'V';
              no = pai;
            }
            //Ir preto, se preto e sd vermelho
            else
            {
              irmao->cor = 'V';
              if (irmao->dir != NULL)
                irmao->dir->cor = 'P';
              rotacionar_esq(arv, irmao);
            }
          }
          //Irmao preto e se vermelho
          else
          {
            irmao->cor = pai->cor;
            pai->cor = 'P';
            if (irmao->esq != NULL)
              irmao->esq->cor = 'P';
            rotacionar_dir(arv, pai);
            no = arv->raiz;
          }
        }
      }
      else
      {
        no = pai;
      }
    }
  }
  no->cor = 'P';
}

void remover(Arvore *arv, int valor)
{
  if (arv->raiz != NULL)
  {
    No *no = arv->raiz;
    while (no != NULL)
    {

      if (no->info == valor)
      {
        No *sucessor = no;

        if (no->dir != NULL)
        {
          sucessor = no->dir;
          while (sucessor->esq != NULL)
          {
            sucessor = sucessor->esq;
          }
        }
        int x = sucessor->info;

        //Exclui o sucessor
        if (sucessor->pai != NULL)
        {

          if (sucessor->dir == NULL)
          {
            if (sucessor->pai->dir == sucessor)
            {
              sucessor->pai->dir = NULL;
            }
            else
            {
              sucessor->pai->esq = NULL;
            }
          }
          else
          {
            if (sucessor->pai->info > sucessor->dir->info)
            {
              sucessor->pai->esq = sucessor->dir;
              sucessor->dir->pai = sucessor->pai;
            }
            else
            {
              sucessor->pai->dir = sucessor->dir;
              sucessor->esq->pai = sucessor->pai;
            }
          }
          no->info = x;
          balancear_rem(arv, sucessor);
        }
        else
        {
          //RAIZ
          arv->raiz = sucessor->esq;
        }

        free(sucessor);
      }

      no = valor > no->info ? no->dir : no->esq;
    }
  }
}

int getCountNo_rec(No *no)
{
  if (no != NULL)
  {
    return 1 + getCountNo_rec(no->esq) + getCountNo_rec(no->dir);
  }
  return 0;
}

int getCountNo(Arvore *arv)
{
  return getCountNo_rec(arv->raiz);
}

int getMemory_rec(No *no)
{
  if (no != NULL)
  {
    return sizeof(no) + getMemory_rec(no->esq) + getMemory_rec(no->dir);
  }
  return 0;
}

int getMemory(Arvore *arv)
{
  return sizeof(arv) + getMemory_rec(arv->raiz);
}

void save_rec(No *raiz, FILE *file)
{
  if (raiz != NULL)
  {
    save_rec(raiz->esq, file);
    int x = 1;
    fprintf(file, "%d", raiz->info);
    fputc('\n', file);
    save_rec(raiz->dir, file);
  }
}

void save(Arvore *arv)
{
  FILE *file = fopen("arquivo.txt", "w");
  if (file != NULL)
  {
    save_rec(arv->raiz, file);
  }
  fclose(file);
}

void imprimir(Arvore *arv)
{
  printf("\n");
  imp_pre(arv->raiz);
  printf("\n");
}

void imp_in(No *raiz)
{
  if (raiz != NULL)
  {
    imp_in(raiz->esq);
    printf("[ %d %c ", raiz->info, raiz->cor);
    if (raiz->pai != NULL)
    {
      printf(" pai %d ", raiz->pai->info);
    }
    printf('] ');
    imp_in(raiz->dir);
  }
}
void imp_pre(No *raiz)
{
  if (raiz != NULL)
  {
    printf("[ %d %c ", raiz->info, raiz->cor);
    if (raiz->pai != NULL)
    {
      printf(" pai %d ", raiz->pai->info);
    }
    printf("] ");
    imp_pre(raiz->esq);
    imp_pre(raiz->dir);
  }
}
