#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "utils.h"

//gera um numero aleatorio
int gerar_numero_aleatorio(){ // função que gera um número aleatório
    
    srand(time(NULL));
    int numero = rand() % 5;

    return numero;

}

