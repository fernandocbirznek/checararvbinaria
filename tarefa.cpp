#include <stdio.h>
#include <stdlib.h>


/*
Implemente uma função que verifica se uma dada árvore é ou não uma árvore binária de busca.

int arv_bin_check(Arvore * a);

*/

typedef struct arvore {
  int info;
  struct arvore *esq;
  struct arvore *dir;
} Arvore;

int buscar (Arvore *a, int v) {
  if (a == NULL) { return 0; } /*Nao achou*/
  else if (v < a->info) {
    return buscar (a->esq, v);
  }
  else if (v > a->info) {
    return buscar (a->dir, v);
  }
  else { return 1; } /*Achou*/
}

Arvore* inserir (Arvore *a, int v) {
  if (a == NULL) {
    a = (Arvore*)malloc(sizeof(Arvore));
    a->info = v;
    a->esq = a->dir = NULL;
  }
  else if (v < a->info) {
    a->esq = inserir (a->esq, v);
  }
  else { a->dir = inserir (a->dir, v); }
  return a;
}

void in_order(Arvore *a){
  if(!a)
    return;
  in_order(a->esq);
  printf("%d ",a->info);
  in_order(a->dir);
}

Arvore* remover(Arvore *a, int x){
  Arvore * aux, * pai_aux;
  int filhos = 0,tmp;

  if(!a)
    return(NULL);

  if(a->info < x)
    a->dir = remover(a->dir,x);
  else if(a->info > x)
    a->esq = remover(a->esq,x);
  else{
    if(a->esq)
      filhos++;
    if(a->dir)
      filhos++;

    if(filhos == 0){
      free(a);
      return(NULL);
    }
    else if(filhos == 1){
      aux = a->esq ? a->esq : a->dir;
      free(a);
      return(aux);
    }
    else{
      aux = a->esq;
      pai_aux = a;
      while(aux->dir){ pai_aux = aux; aux = aux->dir; }
      tmp = a->info;
      a->info = aux->info;
      aux->info = tmp;
      pai_aux->dir = remover(aux,tmp);
      return(a);
    }
  }

  return(a);
}

int arv_bin_check(Arvore * a) {
	int arvBin = 0;
	if (a->esq != NULL) {
		if (a->info > a->esq->info)
			arvBin += arv_bin_check(a->esq);
		else
			return 0;
	}
	if(a->dir != NULL) {
		if (a->info < a->dir->info)
			arvBin += arv_bin_check(a->dir);
		else
			return 0;
	}
	if(a->dir == NULL || a->esq == NULL)
		return arvBin+1;
	return arvBin-1;
}

void print(Arvore * a,int spaces){
  int i;
  for(i=0;i<spaces;i++) printf(" ");
  if(!a){
    printf("//\n");
    return;
  }

  printf("%d\n", a->info);
  print(a->esq,spaces+2);
  print(a->dir,spaces+2);
}

Arvore* arv_constroi (int c, Arvore* e, Arvore* d) {
  Arvore* a = (Arvore*)malloc(sizeof(Arvore));
  a->info = c;
  a->esq = e;
  a->dir = d;
  return a;
}

Arvore* cria_arv_vazia (void) {
   return NULL;
}

int main(){
	Arvore * a;
	
	
	Arvore *b, *b1, *b2, *b3, *b4, *b5, *b6;
	b2  = arv_constroi(30, cria_arv_vazia(),cria_arv_vazia());
	b3  = arv_constroi(15, cria_arv_vazia(),cria_arv_vazia());       // arvore NAO binaria
	//b3  = arv_constroi(90, cria_arv_vazia(),cria_arv_vazia());     // arvore binaria
	b  = arv_constroi(50,b2,b3);
	printf("\nA arvore B:");
	arv_bin_check(b) ? printf("\neh uma arvore binaria") : printf("\nNAO eh uma arvore binaria");
	
	a = inserir(NULL,50);  //                               50
	a = inserir(a,30);     //                 30                           90
	a = inserir(a,90);     //        20              40               //       95
	a = inserir(a,20);     //    10      //   35           45
	a = inserir(a,40);     //              //    37
	a = inserir(a,95);
	a = inserir(a,10);
	a = inserir(a,35);
	a = inserir(a,45);
	a = inserir(a,37);

	arv_bin_check(a) ? printf("\neh uma arvore binaria") : printf("\nNAO eh uma arvore binaria");
	
	printf("\n");
	print(a,0);
	printf("\n");
	
	a = remover(a,45);
	a = remover(a,50);
	a = remover(a,90);
	
	printf("\n");
	print(a,0);
	printf("\n");
}
