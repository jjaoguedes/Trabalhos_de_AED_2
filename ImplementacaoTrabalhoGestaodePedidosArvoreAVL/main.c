/* 
  Gestão de pedidos
  Última modificação: 08/01/2023
  Autor: João Victor Félix Guedes - 22050227
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "pedidos.h"
#include "utils.h"
#include "arvore_AVL.h"
#include "impressao.h"

int main()
{
    TPedido pedido; // para pedidos realizados
    int op; // opção
    int escolha; 
    TPedido num_pedido; // para pedidos finalizados
    int i = 1; // variavel de controle do pedido
    int j = 3042; // variavel id do cliente
    Arv *raiz_R = criaArvore(); // Arvore para pedidos realizados
    Arv *novo_R = (Arv *) malloc(sizeof(Arv));
    Arv *raiz_F = criaArvore(); // Arvore para pedidos finalizados
    Arv *novo_F = (Arv *) malloc(sizeof(Arv));
    Arv *p = NULL; // apontador para a raiz
  
    exibe_escolha();
    scanf("%d", &escolha);
    while(escolha != 0){  
        
        if(escolha == 1){ //Fazer Pedido
          
            cardapio();
            printf("\nDigite o numero da opcao desejada: ");
            op = 1;
            while(op != 0){
                pedido = ler_Pedido(pedido, op, i,j);
                i++;
                j++;
                // Inserção na arvore 
                raiz_R = insercao_Controle_de_Pedido_R(pedido,raiz_R,novo_R);
                //Encerrar controle de pedido digitando 0
                if(i <= 120){
                  cardapio();
                  printf("\nDigite o numero da opcao desejada: ");
                  op = 1;
                }else{
                  op= 0;
                }
            }
        }
        if(escolha == 2){ // Exibe as entregas em andamento
            if(raiz_R == NULL){
                printf("\nNao ha pedidos em andamento!\n");
            }else{
                menu_zona();
                printf("0 - voltar\n");
                printf("Digite qual zona deve ser exibida: ");
                scanf("%d", &escolha);
                while(escolha != 0){
                    printf("\nPedidos em andamento\n");
                    exibir_entregas_R(raiz_R,escolha); // Exibe entregas em andamento
                  
                    menu_zona();
                    printf("0 - voltar\n");
                    printf("Digite qual zona deve ser exibida: ");
                    scanf("%d", &escolha);
                }    
            }
        }
        if(escolha == 3){ // Finalizar Pedido
            
            printf("\nDigite o número do pedido: ");
            scanf("%d", &num_pedido.chave);
            p = busca_pedido(raiz_R, num_pedido.chave);
            num_pedido = raiz_R_para_num_pedido(p,num_pedido);
            // Inserção na arvore
            raiz_F = insercao_Controle_de_Pedido_F(num_pedido,raiz_F,novo_F);
            raiz_R = remove_Arvore_AVL(raiz_R, num_pedido.chave);
            i--;
            printf("\nPedido finalizado com sucesso!\n");
        }
        if(escolha == 4){ // Exibe as entregas finalizadas
            if(raiz_F == NULL){
                printf("\nNao ha pedidos em finalizados!\n");
            }else{
                printf("\nPedidos finalizados\n");
                menu_Entregadores();
                printf("Digite qual entrega deve ser exibida:\n");
                scanf("%d", &escolha);
                while(escolha != 0){
                    printf("\nPedidos em finalizados\n");
                    exibir_entregas_F(raiz_F,escolha); // Exibe entregas finalizadas
                    menu_Entregadores();
                    printf("Digite qual entrega deve ser exibida:\n");
                    scanf("%d", &escolha);
                }    
            }
        }
        exibe_escolha();
        scanf("%d", &escolha);
    }
    return 0;
}