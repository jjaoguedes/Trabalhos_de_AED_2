/* 
  Última modificação: 08/01/2023
  Autor: João Victor Félix Guedes - 22050227
*/
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string.h>
#include "pedidos.h"
#include "utils.h"
#include "arvore_AVL.h"
#include "impressao.h"

/*recebe um tipo pedido e gera um numero aleatorio entre 86400(segundos) e faz a conversao para o pedido receber em horas, minutos e segundos*/
TPedido gerar_horario(TPedido pedido){

    srand(time(NULL));
    pedido.horario = rand() % 86400;
    int h,m,s,r;
    int segundos = pedido.horario;
    h = segundos/3600;
    pedido.horas = h;
    r = segundos%3600;
    m = r/60;
    pedido.minutos = m;
    s = r%60;
    pedido.segundos = s;
    
    return pedido;
}

/*recebe um pedido e uma variavel, cada entregador pode ter apenas 8 pedidos, a variavel i faz o controle disso a cada novo pedido, logo se passar de 8, passa para o proximo entregador*/
TPedido controle_de_entregador(TPedido pedido, int i){
    
    if(i <= 8){
        strcpy(pedido.entregador, "Raimundo");
    }else if(i > 8 && i <= 16){
        strcpy(pedido.entregador, "Jocimar");
    }else if(i > 16 && i <= 24){
        strcpy(pedido.entregador, "Adriano");
    }else if(i > 24 && i <= 32){
        strcpy(pedido.entregador, "Pedro");
    }else if(i > 32 && i <= 40){
        strcpy(pedido.entregador, "David");
    }else if(i > 40 && i <= 48){
        strcpy(pedido.entregador, "Paulo");
    }else if(i > 48 && i <= 56){
        strcpy(pedido.entregador, "Diego");
    }else if(i > 56 && i <= 64){
        strcpy(pedido.entregador, "Isaac");
    }else if(i > 64 && i <= 72){
        strcpy(pedido.entregador, "Valdir");
    }else if(i > 72 && i <= 80){
        strcpy(pedido.entregador, "Gilson");
    }else if(i > 80 && i <= 88){
        strcpy(pedido.entregador, "Carlos");
    }else if(i > 88 && i <= 96){
        strcpy(pedido.entregador, "Augusto");
    }else if(i > 96 && i <= 104){
        strcpy(pedido.entregador, "Adrian");
    }else if(i > 104 && i <= 112){
        strcpy(pedido.entregador, "Marcos");
    }else if(i > 112 && i <= 120){
        strcpy(pedido.entregador, "Eduardo");
    }

    return pedido;
}

/*recebe um pedido e uma variavel de opcao e a variavel de controle, a cada 15 pedidos recebe a string com o nome da regiao*/
TPedido escolhe_zona(TPedido pedido, int op, int i){

  if(i <= 15){
    strcpy(pedido.regiao, "Norte");
  }else if(i > 15 && i <=30){
    strcpy(pedido.regiao, "Sul");
  }else if(i > 30 && i <=45){
    strcpy(pedido.regiao, "Leste");
  }else if(i > 45 && i <=60){
    strcpy(pedido.regiao, "Oeste");
  }else if(i > 60 && i <=75){
    strcpy(pedido.regiao, "Centro-oeste");
  }else if(i > 75 && i <=90){
    strcpy(pedido.regiao, "Centro-sul");
  }else if(i > 90 && i <=105){
    strcpy(pedido.regiao, "Centro-norte");
  }else if(i > 105 && i <=120){
    strcpy(pedido.regiao, "Extremo-norte");
  }

  return pedido;
}

/*recebe um pedido e uma variavel de opcao e a variavel de controle, a cada 24 pedidos recebe a opcao do cardapio e o preco*/
TPedido ler_opcao(TPedido pedido, int op, int i){
  
  if(i <= 24 ){
        strcpy(pedido.opcao, "Ceia com Peru");
        pedido.preco = 155;
    }else if(i > 24 && i <= 48){
        strcpy(pedido.opcao, "Ceia com Bacalhau");
        pedido.preco = 230;
    }else if(i > 48 && i <= 72){
        strcpy(pedido.opcao, "Ceia com carne suína");
        pedido.preco = 210;
    }else if(i > 72 && i <= 96){
        strcpy(pedido.opcao, "Ceia com chester");
        pedido.preco = 185;
    }else if(i > 96 && i <= 120){
        strcpy(pedido.opcao, "Ceia com Pernil");
        pedido.preco = 250;
    }
  
  return pedido;
}

/*recebe um pedido, variavel pra escolha do pedido e uma variavel de controle e variavel do id do cliente, fazendo assim a escolha e concluir com os dados do cliente, ao final eh confirmado e gerado um numero para o pedido*/
TPedido ler_Pedido(TPedido pedido, int op, int i, int j){
    // Escolha de opcao do Cardapio
    pedido = ler_opcao(pedido, op, i);
    // Dados do Cliente

    pedido.id_Cliente = j;

    menu_zona();
    printf("\nDigite a opcao para escolher sua regiao: ");
    pedido = escolhe_zona(pedido, op, i);
    
    // Confirmacao de pedido
    
    printf("\n0 - Confirme seu pedido\n");
    op = 0;
    if(op == 0){
        printf("\nPedido confirmado com sucesso!\n");
    }
    pedido.chave = i;
    pedido = controle_de_entregador(pedido,i);
    

    return pedido;
}
