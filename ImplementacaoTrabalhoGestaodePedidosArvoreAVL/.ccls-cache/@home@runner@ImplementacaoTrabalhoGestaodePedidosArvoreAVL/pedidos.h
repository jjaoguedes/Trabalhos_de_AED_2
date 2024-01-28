#ifndef PEDIDOS_H_INCLUDED
#define PEDIDOS_H_INCLUDED
#include <stdio.h>

struct pedido{
    char opcao[30];
    float preco;
    int id_Cliente;
    char regiao[20];
    char entregador[20];
    int horario;
    int horas;
    int minutos;
    int segundos;
    int chave;
};
typedef struct pedido TPedido;

TPedido gerar_horario(TPedido pedido);
TPedido ler_opcao(TPedido pedido, int op, int i);
TPedido escolhe_zona(TPedido pedido, int op, int i);
TPedido ler_regiao(FILE *file,TPedido pedido, int i);
TPedido controle_de_entregador(TPedido pedido, int i);
TPedido ler_Pedido(TPedido pedido, int op, int i, int j);
#endif