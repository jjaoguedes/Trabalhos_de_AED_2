#ifndef ARVORE_AVL_H_INCLUDED
#define ARVORE_AVL_H_INCLUDED
#include <stdio.h>
#include "pedidos.h"

struct No{
    TPedido pedido;
    int chave;
    struct No *filhoEsq; // filho Esquerdo
    struct No *filhoDir; // filho Direito
    int fb;
};
typedef struct No Arv; 

Arv *criaNo(TPedido novo_Pedido);
void *criaArvore();
int maior(int num1, int num2);
int altura(Arv *raiz);
int fator_balanceamento(Arv *raiz);
Arv *RSE(Arv *raiz);
Arv *RSD(Arv *raiz);
Arv *RDE(Arv *raiz);
Arv *RDD(Arv *raiz);
Arv *balanceamento(Arv *raiz);
Arv *insereArvore_AVL(Arv *raiz, Arv *novo);
Arv *insereArvore_AVL2(Arv *raiz, Arv *novo);
void imprimeArvore(Arv *raiz);
Arv * remove_Arvore_AVL(Arv *raiz, int chave);
Arv *insercao_Controle_de_Pedido_R(TPedido num_pedido, Arv *raiz, Arv *novo);
Arv *insercao_Controle_de_Pedido_F(TPedido num_pedido, Arv *raiz, Arv *novo);
Arv *busca_pedido(Arv *raiz, int num_pedido);
TPedido raiz_R_para_num_pedido(Arv *raiz,TPedido pedido);

#endif