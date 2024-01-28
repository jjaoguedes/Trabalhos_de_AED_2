#ifndef IMPRESSAO_H_INCLUDED
#define IMPRESSAO_H_INCLUDED
#include "arvore_AVL.h"

void cardapio();
void exibe_escolha();
void menu_zona();
void menu_Entregadores();
void dados_do_Pedido_R(Arv *raiz);
void procura_entregas_zona(Arv *raiz, char zona[20]);
void exibir_entregas_R(Arv *raiz,int escolha);
void dados_do_Pedido_F(Arv *raiz);
void procura_entregas_entregador(Arv *raiz, char entregador[20]);
void exibir_entregas_F(Arv *raiz, int escolha);

#endif