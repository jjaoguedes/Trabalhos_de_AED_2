/* 
  Última modificação: 08/01/2023
  Autor: João Victor Félix Guedes - 22050227
*/
#include <stdio.h>
#include <stdlib.h>
#include "arvore_AVL.h"
#include "pedidos.h"

/*recebe uma variável do tipo pedido, aloca o ponteiro novo e o ponteiro vai apontar para os dados do tipo Arv a serem recebidos*/
Arv *criaNo(TPedido novo_Pedido){ // recebe um tipo pedido e retorna um no criado para os dados
    
    Arv *novo = (Arv*) malloc(sizeof(Arv));
    
    novo->pedido = novo_Pedido;
    novo->filhoEsq = NULL; 
    novo->filhoDir = NULL;
    novo->fb = 0;
    
    return novo;
}

void *criaArvore(){ //funcao cria arvore, onde returna NULL
    return NULL;
}

int maior(int num1, int num2){ // funcao que recebe dois parametros e retorna o maior
    if(num1 > num2){
        return num1;
    }else{
        return num2;
    }
}

int altura(Arv *raiz){ // recebe uma raiz e calcula a altura de uma arvore
    
    if(raiz == NULL){ // Eh Vazia
        return 0;
    }else{
      if(raiz->filhoDir == NULL && raiz->filhoEsq == NULL){ //Eh folha
        return 1;
      }else{
        return 1+maior((altura(raiz->filhoDir)), (altura(raiz->filhoEsq)));
      }
    }
      
}

int fator_balanceamento(Arv *raiz){ // recebe a raiz de uma arvore e calcula o fator de balanceamento
    return (altura(raiz->filhoEsq))-(altura(raiz->filhoDir));
}

/* Recebe a raiz e posiciona um ponteiro para a raiz, para o filho da raiz e para o neto da raiz e faz a rotacao simples a esquerda */
Arv* RSE(Arv* raiz) {
    Arv* Ap = raiz;
    Arv* Au = Ap->filhoDir;
    Ap->filhoDir = Au->filhoEsq;
    Au->filhoEsq = Ap;
    Ap = Au;
    return Ap;
}

/* Recebe a raiz e posiciona um ponteiro para a raiz, para o filho da raiz e para o neto da raiz e faz a rotação simples a direita*/
Arv* RSD(Arv* raiz) {
    Arv* Ap = raiz;
    Arv* Au = Ap->filhoEsq;
    Ap->filhoEsq = Au->filhoDir;
    Au->filhoDir = Ap;
    Ap = Au;
    return Ap;
}

/*Recebe a raiz, raiz filho direito recebe a rotacao simples a direita e em seguida a raiz recebe a rotacao simples a esquerda, assim fazendo a rotação dupla a esquerda*/
Arv *RDE(Arv *raiz){
    raiz->filhoDir = RSD(raiz->filhoDir);
    raiz = RSE(raiz);
    return raiz;
}

/*Recebe a raiz, raiz filho esquerdo recebe a rotacao simples a esquerda e em seguida a raiz recebe a rotacao simples a direita, assim fazendo a rotação dupla a direita*/
Arv *RDD(Arv *raiz){
	raiz->filhoEsq = RSE(raiz->filhoEsq);
	raiz = RSD(raiz);
	return raiz;
}

/*recebe a raiz e compara o fator de balanceamento da raiz com o fator de balanceamento do filho direito ou filho esquerdo, se estiver fora dos limites, faz o ajuste adequado para cada caso*/
Arv *balanceamento(Arv *raiz){ // recebe a raiz 
    
    if(fator_balanceamento(raiz) < -1 && fator_balanceamento(raiz->filhoDir) <= 0){
        raiz = RSE(raiz);
    }else if(fator_balanceamento(raiz) > 1 && fator_balanceamento(raiz->filhoEsq) >= 0){
        raiz = RSD(raiz);
    }else if(fator_balanceamento(raiz) > 1 && fator_balanceamento(raiz->filhoEsq) < 0){
        raiz = RDD(raiz);
    }else if(fator_balanceamento(raiz) < -1 && fator_balanceamento(raiz->filhoDir) > 0){
        raiz = RDE(raiz);
    }

    return raiz;
}
/*recebe a raiz e novo no e compara a raiz apontando pro tipo pedido chave e o novo no apontando pro tipo pedido chave, se a raiz for menor que novo, insere no filho esquerdo, se raiz for maior que novo, insere no filho direito, em seguida eh verificado se eh preciso fazer os ajustes de balanceamento na arvore*/
Arv *insereArvore_AVL(Arv *raiz, Arv *novo){
    if(raiz == NULL){
        return novo;
    }else{
      if(raiz->pedido.chave > novo->pedido.chave){
        raiz->filhoEsq = insereArvore_AVL(raiz->filhoEsq, novo);
      }else{
        raiz->filhoDir = insereArvore_AVL(raiz->filhoDir, novo);
      }
    }
    
    raiz->fb = fator_balanceamento(raiz);
    raiz = balanceamento(raiz);
    return raiz;
}
/*recebe a raiz e novo no e compara a raiz apontando pro tipo pedido horario e o novo no apontando pro tipo pedido horario, se a raiz for menor que novo, insere no filho esquerdo, se raiz for maior que novo, insere no filho direito, em seguida eh verificado se eh preciso fazer os ajustes de balanceamento na arvore*/
Arv *insereArvore_AVL2(Arv *raiz, Arv *novo){  
    if(raiz == NULL){
        return novo;
    }else{
      if(raiz->pedido.horario > novo->pedido.horario){
        raiz->filhoEsq = insereArvore_AVL2(raiz->filhoEsq, novo);
      }  else{
        raiz->filhoDir = insereArvore_AVL2(raiz->filhoDir, novo);
      }
    }
    
    raiz->fb = fator_balanceamento(raiz);
    raiz = balanceamento(raiz);
    return raiz;
}

void imprimeArvore(Arv *raiz){
	if(raiz != NULL){
		imprimeArvore(raiz->filhoEsq);
		printf("%d ", raiz->pedido.chave);
		imprimeArvore(raiz->filhoDir);
	}
}
/*recebe uma raiz e chave para remover, logo se a raiz for igual a chave, a remocao sera executada em tres casos, o primeiro quando o filho eh folha, o segundo quando a raiz possuir um unico filho e a terceira quando possuir dois filhos, assim se a raiz nao for igual a chave, arvore eh percorrida recursivamente até encontrar*/
Arv *remove_Arvore_AVL(Arv *raiz, int chave){

  if(raiz == NULL){
    return NULL;
  }else{
    if(raiz->pedido.chave == chave){
      //Caso 1: Se a raiz eh folha
      if(raiz->filhoDir == NULL && raiz->filhoEsq == NULL){
        free(raiz);
        return NULL;
      }else{
          // Caso 2: Se a raiz possuir um unico filho
          Arv *p;
          if(raiz->filhoEsq != NULL){
            p = raiz->filhoEsq;
            free(raiz);
            return p;
          }else if(raiz->filhoDir != NULL){
            p = raiz->filhoDir;
            free(raiz);
            return p;
          }else{
            // Caso 3: Se a raiz possuir dois filhos
            if(raiz->filhoEsq != NULL && raiz->filhoDir != NULL){
            
          }
        }
      } 
    }else{
      if(chave < raiz->pedido.chave){
        raiz->filhoEsq = remove_Arvore_AVL(raiz->filhoEsq, chave);
      }else{
        raiz->filhoDir = remove_Arvore_AVL(raiz->filhoDir, chave);
      }
      return raiz;
    }
  }
  //raiz->fb = fator_balanceamento(raiz);
  //raiz = balanceamento(raiz);
  return raiz;
} 

/*recebe uma variavel do tipo pedido, uma raiz do tipo Arv e novo no do tipo Arv, novo recebe cria no e raiz insere raiz e novo no dos pedidos realizados*/
Arv *insercao_Controle_de_Pedido_R(TPedido num_pedido, Arv *raiz, Arv *novo){
    novo = criaNo(num_pedido);
    raiz = insereArvore_AVL(raiz, novo);
    return raiz;
}

/*recebe uma variavel do tipo pedido, uma raiz do tipo Arv e novo no do tipo Arv, novo recebe cria no e raiz insere raiz e novo no dos pedidos finalizados*/
Arv *insercao_Controle_de_Pedido_F(TPedido num_pedido, Arv *raiz, Arv *novo){
    novo = criaNo(num_pedido);
    raiz = insereArvore_AVL2(raiz, novo);
    return raiz;
}

/*recebe uma raiz e o numero do pedido,logo percorre a arvore até achar o elemento, se nao eh chamado a funcao busca pedido recursivamente até achar*/
Arv *busca_pedido(Arv *raiz, int num_pedido){
    
    if(raiz != NULL){
        if(raiz->pedido.chave == num_pedido){
            return raiz;
        }else if(raiz->chave > num_pedido){
            return busca_pedido(raiz->filhoEsq, num_pedido);
        }else{
            return busca_pedido(raiz->filhoDir, num_pedido);
        }
    }   
    return NULL;
  
}

/*recebe uma raiz e um pedido, assim passando as informações da raiz para o pedido*/
TPedido raiz_R_para_num_pedido(Arv *raiz,TPedido pedido){
    
    pedido = raiz->pedido;
    pedido = gerar_horario(pedido);
    
    return pedido;
}
