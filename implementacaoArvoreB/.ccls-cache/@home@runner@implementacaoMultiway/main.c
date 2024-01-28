/*  
    Árvore Multiway
    Última modificação: 26/02/2023
    Autor: João Victor Félix Guedes - 22050227
    Disciplina: Algoritmos e Estrutura de dados II
*/

#include <stdio.h>
#include <stdlib.h>
// Número máximo de Chaves
#define M 5
// Número mínimo de Chaves
#define m 2

//
struct No{
  int chaveAtual;
  int num_Chaves;
  int chaves[M];
  struct No*ponteiroFilho[M];
};

typedef struct No Arv;

//
struct NoP{
  Arv *raiz;
  struct NoP *proximo; 
};

typedef struct NoP Pilha;

void empilha(Pilha *topo, Arv *raiz){
  Pilha *novo = (Pilha *) malloc(sizeof(Pilha));
    novo->raiz = raiz;
    novo->proximo = topo;
    topo = novo;
}

void *criaArvore(){ //funcao cria arvore, onde returna NULL
    return NULL;
}

int eh_folha(Arv* raiz) {
  // Verifica se o nó é vazio ou se tem filhos
  if (raiz == NULL || raiz->ponteiroFilho[0] != NULL) {
    return 0; // Não é folha
  }
  return 1; // É folha
}

Arv *criaNoFolha(int novoValor){
  int i=0;
  Arv *novo = (Arv*) malloc(sizeof(Arv));
  novo->chaveAtual = novoValor;
  novo->num_Chaves = 1;
  novo->chaves[0] = novoValor;
  while(i < M){
    novo->ponteiroFilho[i] = NULL;
    i++;
  }
  return novo;
}

Arv* criaNo(){
  
    Arv* novo = (Arv*) malloc(sizeof(Arv));
    novo->num_Chaves = 0;
    for (int i = 0; i < M; i++) {
        novo->ponteiroFilho[i] = NULL;
    }
    return novo;
}

int encontra_posicao(Arv *raiz, int chave, int i) {
  if (i >= raiz->num_Chaves || raiz->chaves[i] > chave) {
    return i;
  } else {
    return encontra_posicao(raiz, chave, i + 1);
  }
}

Arv *insereNoOrdenado(Arv *raiz, Arv *novo) {
    int i=0, posicao=0;
    // Encontra a posição em que a chave deve ser inserida
    posicao = encontra_posicao(raiz, novo->chaveAtual, 0);
    // Desloca as chaves maiores para a direita
    for (i = raiz->num_Chaves; i > posicao; i--) {
        raiz->chaves[i] = raiz->chaves[i-1];
        raiz->ponteiroFilho[i] = raiz->ponteiroFilho[i-1];
    }
    // Insere a chave na posição correta
    raiz->chaves[posicao] = novo->chaveAtual;
    raiz->ponteiroFilho[posicao] = NULL; // novo nó folha não tem filhos
    raiz->num_Chaves++;

    return raiz;
}

Arv *insereNoOrdenadoMeio(Arv *raiz, int novoValor) {
    int i=0, posicao=0;
    // Encontra a posição em que a chave deve ser inserida
    posicao = encontra_posicao(raiz, novoValor, 0);

    // Desloca as chaves maiores para a direita
    for (i = raiz->num_Chaves; i > posicao; i--) {
        raiz->chaves[i] = raiz->chaves[i-1];
        raiz->ponteiroFilho[i] = raiz->ponteiroFilho[i-1];
    }
  
    // Insere a chave na posição correta
    raiz->chaves[posicao] = novoValor;
    raiz->ponteiroFilho[posicao] = NULL; // novo nó folha não tem filhos
    raiz->num_Chaves++;

    return raiz;
}

void copiaChavesNo(Arv *noOrigem, Arv *noDestino, int inicio,int fim) {
    for(int i = inicio; i < fim; i++) {
        noOrigem->chaveAtual = noOrigem->chaves[i];
        insereNoOrdenado(noDestino, noOrigem);
    }
}

Arv *achaFolha(Arv *raiz, Pilha *pilha, int valor) {
    int i = 0;
    Arv *atual = raiz;
    empilha(pilha, atual);
    while(!(eh_folha(atual))) {
        i = 0;
        while(i < atual->num_Chaves && valor > atual->chaves[i]) {
            i++;
        }
        atual = atual->ponteiroFilho[i];
        empilha(pilha, atual);
    }
    return atual;
}


Arv *insere(Arv *raiz, int valor) {
    // Se a raiz for nula, crie um novo nó e retorne
    if (raiz == NULL) {
        raiz = criaNoFolha(valor);
        return raiz;
    }else if(raiz->num_Chaves < M){
      raiz = insereNoOrdenadoMeio(raiz, valor);
      if(raiz->num_Chaves == M){
        Arv *novaRaiz = criaNo();
        Arv *novaFolha = criaNo();
        Arv *novaRaizAntiga = criaNo();
        novaRaiz = insereNoOrdenadoMeio(novaRaiz, raiz->chaves[m]);
        copiaChavesNo(raiz, novaFolha, m+1, M);
        copiaChavesNo(raiz, novaRaizAntiga, 0, m);
        novaRaiz->ponteiroFilho[0] = novaRaizAntiga;
        novaRaiz->ponteiroFilho[1] = novaFolha;
        raiz = novaRaiz;
      }
    }
    return raiz;
}


Arv *insere_Arvore_B(Arv *raiz, Arv *novo, Pilha *pilha){
  if(raiz == NULL){ 
    return novo;
  }else if(eh_folha(raiz) == 1){ // raiz é folha
    if(raiz->num_Chaves < M){
      raiz = insereNoOrdenado(raiz, novo);
      if(raiz->num_Chaves == M){
        Arv *novaRaiz = criaNo();
        Arv *novaFolha = criaNo();
        Arv *novaRaizAntiga = criaNo();
        novaRaiz = insereNoOrdenadoMeio(novaRaiz, raiz->chaves[m]);
        copiaChavesNo(raiz, novaFolha, m+1, M);
        copiaChavesNo(raiz, novaRaizAntiga, 0, m);
        novaRaiz->ponteiroFilho[0] = novaRaizAntiga;
        novaRaiz->ponteiroFilho[1] = novaFolha;
        raiz = novaRaiz;
        return raiz;
      }
    }
  }else{ // raiz não é folha
    Arv *folha = achaFolha(raiz, pilha, novo->chaveAtual);
    if(raiz->num_Chaves < M){
      folha = insereNoOrdenado(folha, novo);
      if(folha->num_Chaves == M){
        Arv *folha = achaFolha(raiz, pilha, novo->chaveAtual);
        Arv *novaFolha = criaNo();
        Arv *folhaAntiga = criaNo();
        copiaChavesNo(folha, novaFolha, m+1, M);
        copiaChavesNo(folha, folhaAntiga, 0, m);
        int i;
        for (i = raiz->num_Chaves; i > 0 && folha->chaves[m] < raiz->chaves[i-1]; i--) {
          raiz->chaves[i] = raiz->chaves[i-1];
          raiz->ponteiroFilho[i+1] = raiz->ponteiroFilho[i];
        }
        raiz->chaves[i] = folha->chaves[m];
        raiz->ponteiroFilho[i] = folhaAntiga;
        raiz->ponteiroFilho[i+1] = novaFolha;
        raiz->num_Chaves++;
        return raiz;
      }
    }
  }
}

void print_tree(Arv* root) {
    if (root == NULL) {
        return;
    }
    
    printf("+---------------+\n");
    printf("| ");
    for (int i = 0; i < root->num_Chaves; i++) {
        printf("%d %d ", root->chaves[i], root->num_Chaves);
    }
    printf("|\n");
    printf("+---+---+---+---+\n");
    for (int i = 0; i < 5; i++) {
        print_tree(root->ponteiroFilho[i]);
    }
  }

int main(void) {

  Arv *raiz = criaArvore();
  Arv *novo = (Arv*) malloc(sizeof(Arv));
  Pilha *pilha = NULL;
  novo = criaNoFolha(60);
  raiz = insere_Arvore_B(raiz, novo, pilha);
  novo = criaNoFolha(17);
  raiz = insere_Arvore_B(raiz, novo, pilha);
  novo = criaNoFolha(28);
  raiz = insere_Arvore_B(raiz, novo, pilha);
  novo = criaNoFolha(43);
  raiz = insere_Arvore_B(raiz, novo, pilha);
  novo = criaNoFolha(90);
  raiz = insere_Arvore_B(raiz, novo, pilha);
  novo = criaNoFolha(85);
  raiz = insere_Arvore_B(raiz, novo, pilha);
  novo = criaNoFolha(74);
  raiz = insere_Arvore_B(raiz, novo, pilha);
  novo = criaNoFolha(32);
  raiz = insere_Arvore_B(raiz, novo,pilha);
  novo = criaNoFolha(57);
  raiz = insere_Arvore_B(raiz, novo,pilha);
  novo = criaNoFolha(10);
  raiz = insere_Arvore_B(raiz, novo,pilha);
  novo = criaNoFolha(8);
  raiz = insere_Arvore_B(raiz, novo,pilha);
novo = criaNoFolha(19);
  raiz = insere_Arvore_B(raiz, novo,pilha);
  novo = criaNoFolha(92);
  raiz = insere_Arvore_B(raiz, novo,pilha);
 /* Pilha *pilhe = NULL;
 Arv *folha = achaFolha(raiz, pilhe, novo->chaveAtual);
Arv *novaFolha = criaNo();
Arv *folhaAntiga = criaNo();
copiaChavesNo(folha, novaFolha, m+1, M);
copiaChavesNo(folha, folhaAntiga, 0, m);
int i;
for (i = raiz->num_Chaves; i > 0 && folha->chaves[m] < raiz->chaves[i-1]; i--) {
    raiz->chaves[i] = raiz->chaves[i-1];
    raiz->ponteiroFilho[i+1] = raiz->ponteiroFilho[i];
}
raiz->chaves[i] = folha->chaves[m];
raiz->ponteiroFilho[i] = folhaAntiga;
raiz->ponteiroFilho[i+1] = novaFolha;
raiz->num_Chaves++;*/
 Pilha *pilhe = NULL;
 Arv *folha = achaFolha(raiz, pilhe, novo->chaveAtual);
  print_tree(raiz);
  
  return 0;
}