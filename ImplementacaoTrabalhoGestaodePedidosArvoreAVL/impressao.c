/* 
  Última modificação: 08/01/2023
  Autor: João Victor Félix Guedes - 22050227
*/
#include "impressao.h"
#include "arvore_AVL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cardapio() { // Exibe cardápio
  printf("\nOpções disponíveis:\n");
  printf("1 - Ceia com Peru - R$155.00\n");
  printf("2 - Ceia com Bacalhau - R$230.00\n");
  printf("3 - Ceia com carne suina - R$220.00\n");
  printf("4 - Ceia com chester - R$195.00\n");
  printf("5 - Ceia com Pernil - R$250.00\n");
  printf("0 - Sair\n");
}

void exibe_escolha(){ // Exibe a escolha para as operações
  printf("\nControle de Pedidos\n");
  printf("\n1 - Fazer pedido\n");
  printf("2 - Exibir pedidos em andamento\n");
  printf("3 - Finalizar pedido\n");
  printf("4 - Exibir pedidos finalizados\n");
  printf("0 - Sair\n");
  printf("\nDigite uma das opcoes a serem executadas: ");
}

void menu_zona() { //exibe as regiões
  printf("\nZonas\n");
  printf("\n1 - Norte\n");
  printf("2 - Sul\n");
  printf("3 - Leste\n");
  printf("4 - Oeste\n");
  printf("5 - Centro-oeste\n");
  printf("6 - Centro-sul\n");
  printf("7 - Centro-norte\n");
  printf("8 - Extremo-norte\n");
}

void menu_Entregadores(){ //exibe os entregadores cadastrados
  printf("\nEntregadores cadastrados\n");
  printf("\n1 - Raimundo\n");
  printf("2 - Jocimar\n");
  printf("3 - Adriano\n");
  printf("4 - Pedro\n");
  printf("5 - David\n");
  printf("6 - Paulo\n");
  printf("7 - Diego\n");
  printf("8 - Isaac\n");
  printf("9 - Valdir\n");
  printf("10 - Gilson\n");
  printf("11 - Carlos\n");
  printf("12 - Augusto\n");
  printf("13 - Adrian\n");
  printf("14 - Marcos\n");
  printf("15 - Eduardo\n");
  printf("0 - voltar\n");
}

void dados_do_Pedido_R(Arv *raiz) { // exibe os dados dos pedidos realizados
  printf("\nNumero do pedido: %d\n", raiz->pedido.chave);
  printf("ID Cliente: %d\n", raiz->pedido.id_Cliente);
  printf("Regiao de entrega: %s\n", raiz->pedido.regiao);
  printf("Opcao escolhida: %s\n", raiz->pedido.opcao);
  printf("Preco a pagar: $%.2f\n", raiz->pedido.preco);
  printf("Entregador: %s\n", raiz->pedido.entregador);
}
/*exibe apenas a entrega de uma região, enquanto a raiz nao for nula, a arvore vai ser percorrida e se encontrar a regiao, imprime os dados do pedido */
void procura_entregas_zona(Arv *raiz, char zona[20]) {

  if (raiz != NULL) {
    procura_entregas_zona(raiz->filhoEsq,zona);
    if (strcmp(raiz->pedido.regiao, zona) == 0){ 
      dados_do_Pedido_R(raiz);
    }
    procura_entregas_zona(raiz->filhoDir,zona);
  }
}

void exibir_entregas_R(Arv *raiz,int escolha) { // Exibe as entregas ordenadas por zona e por pedido

if (escolha == 1) {
    printf("\nZona Norte\n");
    procura_entregas_zona(raiz, "Norte");
  } else if (escolha == 2) {
    printf("\nZona Sul\n");
    procura_entregas_zona(raiz, "Sul");
  } else if (escolha == 3) {
    printf("\nZona Leste\n");
    procura_entregas_zona(raiz, "Leste");
  } else if (escolha == 4) {
    printf("\nZona Oeste\n");
    procura_entregas_zona(raiz, "Oeste");
  } else if (escolha == 5) {
    printf("\nZona Centro-oeste\n");
    procura_entregas_zona(raiz, "Centro-oeste");
  } else if (escolha == 6) {
    printf("\nZona Centro-sul\n");
    procura_entregas_zona(raiz, "Centro-sul");
  } else if (escolha == 7) {
    printf("\nZona Centro-norte\n");
    procura_entregas_zona(raiz, "Centro-norte");
  } else if (escolha == 8) {
    printf("\nZona Extremo-norte\n");
    procura_entregas_zona(raiz, "Extremo-norte");
  }
}

void dados_do_Pedido_F(Arv *raiz) { // exibe os dados dos pedidos finalizados

  printf("\nHorario: %.2d:%.2d:%.2d\n", raiz->pedido.horas,
         raiz->pedido.minutos, raiz->pedido.segundos);
  printf("Entregador: %s\n", raiz->pedido.entregador);
  printf("Numero do pedido: %d\n", raiz->pedido.chave);
  printf("ID Cliente: %d\n", raiz->pedido.id_Cliente);
  printf("Regiao de entrega: %s\n", raiz->pedido.regiao);
  printf("Opcao escolhida: %s\n", raiz->pedido.opcao);
  printf("Preco pago: $%.2f\n", raiz->pedido.preco);
}

//*exibe apenas a entrega de um entregador, enquanto a raiz nao for nula, a arvore vai ser percorrida e se encontrar o entregador, imprime os dados do pedido */
void procura_entregas_entregador(Arv *raiz, char entregador[20]) {

  if (raiz != NULL) {
    procura_entregas_entregador(raiz->filhoEsq, entregador);
    if (strcmp(raiz->pedido.entregador, entregador) == 0) {
      dados_do_Pedido_F(raiz);
    }
    procura_entregas_entregador(raiz->filhoDir, entregador);
  }
}
/*exibe as entregas finalizadas ordenadas por entregador e horario*/
void exibir_entregas_F(Arv *raiz, int escolha) {

  if (escolha == 1) {
    printf("\nRaimundo\n");
    procura_entregas_entregador(raiz, "Raimundo");
  } else if (escolha == 2) {
    printf("\nJocimar\n");
    procura_entregas_entregador(raiz, "Jocimar");
  } else if (escolha == 3) {
    printf("\nAdriano\n");
    procura_entregas_entregador(raiz, "Adriano");
  } else if (escolha == 4) {
    printf("\nPedro\n");
    procura_entregas_entregador(raiz, "Pedro");
  } else if (escolha == 5) {
    printf("\nDavid\n");
    procura_entregas_entregador(raiz, "David");
  } else if (escolha == 6) {
    printf("\nPaulo\n");
    procura_entregas_entregador(raiz, "Paulo");
  } else if (escolha == 7) {
    printf("\nDiego\n");
    procura_entregas_entregador(raiz, "Diego");
  } else if (escolha == 8) {
    printf("\nIsaac\n");
    procura_entregas_entregador(raiz, "Isaac");
  } else if (escolha == 9) {
    printf("\nValdir\n");
    procura_entregas_entregador(raiz, "Valdir");
  } else if (escolha == 10) {
    printf("\nGilson\n");
    procura_entregas_entregador(raiz, "Gilson");
  } else if (escolha == 11) {
    printf("\nCarlos\n");
    procura_entregas_entregador(raiz, "Carlos");
  } else if (escolha == 12) {
    printf("\nAugusto\n");
    procura_entregas_entregador(raiz, "Augusto");
  } else if (escolha == 13) {
    printf("\nAdrian\n");
    procura_entregas_entregador(raiz, "Adrian");
  } else if (escolha == 14) {
    printf("\nMarcos\n");
    procura_entregas_entregador(raiz, "Marcos");
  } else if (escolha == 15) {
    printf("\nEduardo\n");
    procura_entregas_entregador(raiz, "Eduardo");
  }
}