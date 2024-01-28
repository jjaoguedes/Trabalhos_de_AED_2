/*  
    Árvore B
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

//Estrutura da Árvore B
struct No{
  int chaveAtual;
  int num_Chaves;
  int chaves[M];
  struct No*ponteiroFilho[M];
};

typedef struct No Arv;

// Estrutura da pilha
struct NoP{
  Arv *raiz;
  struct NoP *topo;
  struct NoP *proximo; 
};

typedef struct NoP Pilha;

// função que recebe uma pilha e uma raiz da arvore e empilha a pilha no topo
void empilha(Pilha *topo, Arv *raiz){
  Pilha *novo = (Pilha *) malloc(sizeof(Pilha));
    novo->raiz = raiz;
    novo->proximo = topo; 
    topo = novo;
}

Arv* desempilha(Pilha *topo) {
    if (topo == NULL) {
        return NULL; // Pilha vazia, não há elementos para desempilhar
    }
    Pilha *temp = topo; // Armazena o topo atual
    Arv *raiz = temp->raiz; // Armazena a raiz do nó a ser desempilhado
    topo = temp->proximo; // Atualiza o topo da pilha para o próximo nó
    free(temp); // Libera a memória do nó desempilhado
    return raiz; // Retorna a raiz do nó desempilhado
}

void destroiPilha(Pilha *topo) {
    Pilha *atual = topo; // recebe o topo da pilha
    while (atual != NULL) {
        Pilha *prox = atual->proximo; // recebe próxima pilha
        free(atual); //libera memoria
        atual = prox; 
    }
}

void *criaArvore(){ //funcao cria arvore, onde returna NULL
    return NULL;
}

int eh_folha(Arv* raiz) {
  // Verifica se a raiz é vazia ou se tem filhos
  if (raiz == NULL || raiz->ponteiroFilho[0] != NULL) {
    return 0; // Não é folha
  }
  return 1; // É folha
}

// Função que inicializa os filhos com NULL
void inicializaFilhos(Arv *novo, int i) {
  if (i > 0) {
    novo->ponteiroFilho[i-1] = NULL;
  }else{
    inicializaFilhos(novo, i-1);
  }
}

/* cria o no folha com o número máximo de chaves recebendo o novo valor e atualizando o número de chaves no nó.
*/
Arv *criaNoFolha(int novoValor){
  Arv *novo = (Arv*) malloc(sizeof(Arv));
  novo->chaveAtual = novoValor; // recebe o novoValor
  novo->num_Chaves = 1; // atualiza o numero de chaves
  novo->chaves[0] = novoValor; // recebe o novo valor no vetor de chaves
  inicializaFilhos(novo, M); // inicializa os filhos com NULL
  return novo;
}

// cria o no folha com o número máximo de chaves e com 0 chaves
Arv* criaNo(){
    Arv* novo = (Arv*) malloc(sizeof(Arv));
    novo->num_Chaves = 0; // inicializa o numero de chaves igual 0
    inicializaFilhos(novo, M); // inicializa os filhos com NULL
    return novo;
}

/* Verifica se a posição atual é maior ou igual ao número de chaves na raiz ou se a chave na posição atual é maior que a chave a ser inserida 
*/
int encontra_posicao(Arv *raiz, int chave, int i) {
  if (i >= raiz->num_Chaves || raiz->chaves[i] > chave){ 
    return i; // retorna a chave que deve ser inserida na posição atual
  } else {
    return encontra_posicao(raiz, chave, i + 1);
  }
}

Arv *insereNoOrdenado(Arv *raiz, Arv *novo) {
    int posicao=0;
    // Encontra a posição em que a chave deve ser inserida
    posicao = encontra_posicao(raiz, novo->chaveAtual, 0);
    // Desloca as chaves maiores para a direita
    int i = raiz->num_Chaves;
    while (i > posicao) {
        raiz->chaves[i] = raiz->chaves[i-1];
        raiz->ponteiroFilho[i] = raiz->ponteiroFilho[i-1];
        i--;
    }
    // Insere a chave na posição correta
    raiz->chaves[posicao] = novo->chaveAtual;
    raiz->ponteiroFilho[posicao] = NULL; // novo nó folha não tem filhos
    raiz->num_Chaves++;

    return raiz;
}

Arv *insereNoOrdenadoMeio(Arv *raiz, int novoValor) {
    int posicao=0;
    // Encontra a posição em que a chave deve ser inserida
    posicao = encontra_posicao(raiz, novoValor, 0);
    // Desloca as chaves maiores para a direita
    int i = raiz->num_Chaves;
    while (i > posicao) {
        raiz->chaves[i] = raiz->chaves[i-1];
        raiz->ponteiroFilho[i] = raiz->ponteiroFilho[i-1];
        i--;
    }
    raiz->chaves[posicao] = novoValor; // Insere a chave na posição correta
    raiz->ponteiroFilho[posicao] = NULL; // novo nó folha não tem filhos
    raiz->num_Chaves++;

    return raiz;
}

void copiaChavesNo(Arv *raiz, Arv *novaFolha, int inicio, int fim) {
    int i = inicio;
    while (i < fim) {
        raiz->chaveAtual = raiz->chaves[i]; /* define a chave atual da árvore original para a chave correspondente ao índice i*/
        insereNoOrdenado(novaFolha, raiz); // insere a chave no novo nó em ordem.
        i++;
    }
}

Arv *achaFolha(Arv *raiz, Pilha *pilha, int valor) {
    int i = 0;
    Arv *atual = raiz;
    /*Empilha o nó atual na pilha, a pilha será usada para rastrear o caminho percorrido até encontrar a folha onde o valor deve ser inserido*/
    empilha(pilha, atual);
    while(!(eh_folha(atual))) {
        i = 0;
        while(i < atual->num_Chaves && valor > atual->chaves[i]) {
            i++;
        }
        //Atualiza o ponteiro atual para apontar para o filho na posição i
        atual = atual->ponteiroFilho[i];
        // Empilha o nó atual na pilha.
        empilha(pilha, atual);
    }
    destroiPilha(pilha); 
    return atual;
}

Arv *insere_Arvore_B(Arv *raiz, Arv *novo, Pilha *pilha){
  if(raiz == NULL){ // Caso 1: raiz é nula
    return novo;
  }else if(eh_folha(raiz) == 1){ // Caso 2: raiz é folha
    if(raiz->num_Chaves < M){
      raiz = insereNoOrdenado(raiz, novo);
      if(raiz->num_Chaves == M){
        Arv *novaRaiz = criaNo();
        Arv *novaFolha = criaNo();
        Arv *novaRaizAntiga = criaNo();
        novaRaiz = insereNoOrdenadoMeio(novaRaiz, raiz->chaves[m]);
        copiaChavesNo(raiz, novaFolha, m+1, M); // copia a raiz para a nova folha
        copiaChavesNo(raiz, novaRaizAntiga, 0, m); /* copia a raiz para a nova raiz antiga dividida*/
        novaRaiz->ponteiroFilho[0] = novaRaizAntiga; /* O ponteiro para a folha antiga é inserido na posição 0*/
        novaRaiz->ponteiroFilho[1] = novaFolha; /*o ponteiro para a nova folha é inserido na posição 1*/
        free(raiz);
        return novaRaiz;
      }
    }
  }else{ // Caso 3: raiz não é folha
    Arv *folha = achaFolha(raiz, pilha, novo->chaveAtual);
    if(raiz->num_Chaves < M){
      folha = insereNoOrdenado(folha, novo);
      if(folha->num_Chaves == M){
        folha = achaFolha(raiz, pilha, novo->chaveAtual); 
        Arv *novaFolha = criaNo();
        Arv *folhaAntiga = criaNo();
        int i  = raiz->num_Chaves;
        copiaChavesNo(folha, novaFolha, m+1, M);
        copiaChavesNo(folha, folhaAntiga, 0, m);
        // desloca as chaves maiores que a nova chave para a direita no nó da raiz
        while (i > 0 && folha->chaves[m] < raiz->chaves[i-1]){
          raiz->chaves[i] = raiz->chaves[i-1];
          raiz->ponteiroFilho[i+1] = raiz->ponteiroFilho[i];
          i--;
        }
        // A variável i guarda a posição correta para inserção
        raiz->chaves[i] = folha->chaves[m]; // inserção da nova chave
        // O ponteiro para a folha antiga é inserido na posição i
        raiz->ponteiroFilho[i] = folhaAntiga; /* o ponteiro para a folha antiga é inserido na posição i*/
        raiz->ponteiroFilho[i+1] = novaFolha; /*o ponteiro para a nova folha é inserido na posição i+1*/
        raiz->num_Chaves++;
        free(folha);
        return raiz;
      }
    }
  }
}

void imprimeRaiz(Arv *raiz, int i){
  if (i < raiz->num_Chaves) {
        printf("%d %d ", raiz->chaves[i], raiz->num_Chaves);
        imprimeRaiz(raiz, i+1);
    }
}

void imprimeArvoreB(Arv* raiz) {
    if (raiz != NULL) {
    printf("\n");
    int i = 0;
    imprimeRaiz(raiz, 0); // imprime os valores da raiz
    printf("\n");
    printf("\n");
    i = 0;
    while (i < M) {
        imprimeArvoreB(raiz->ponteiroFilho[i]); // imprime os valores dos filhos
        i++;
    }
  }
}

Arv *buscaNoRaiz(Arv *raiz, int valor){
  int i = 0;
    while (i < raiz->num_Chaves && valor != raiz->chaves[i]) {
        i++;
    }
    if (i < raiz->num_Chaves && valor == raiz->chaves[i]) {
        raiz->chaveAtual = valor;
        return raiz; // Encontrou o valor na folha
    }else{
      return NULL; // Valor não encontrado na árvore, retorna NULL
    }
}

Arv *buscaNo(Arv *raiz, Arv *folha, int valor) {
    int i = 0;
    while (i < folha->num_Chaves && valor != folha->chaves[i]) {
        i++;
    }
    if (i < folha->num_Chaves && valor == folha->chaves[i]) {
        folha->chaveAtual = valor; // recebe o valor encontrada
        return folha; // retorna o valor na folha
    }else if(i < raiz->num_Chaves && valor == raiz->chaves[i]){
      folha = buscaNoRaiz(raiz, valor);
      return folha; // Encontrou o valor na folha
    }else{
      return NULL; // Valor não encontrado na árvore, retorna NULL
    }
}

Arv *busca_Arvore_B(Arv *raiz, int valor) {
    Pilha *pilha = (Pilha *) malloc(sizeof(Pilha)); 
    pilha = NULL;
    Arv *folha = achaFolha(raiz, pilha, valor); // Encontra a folha onde o valor deve estar
    Arv *raizBuscada = buscaNo(raiz, folha, valor); // Busca o valor na folha encontrada
    destroiPilha(pilha);
    if(raizBuscada == NULL){
      raizBuscada = buscaNoRaiz(raiz, valor);
      return raizBuscada; // retorna raiz com chave Atual na raiz principal
    }else if(raizBuscada != NULL){ 
      return raizBuscada; // retorna raiz com chave Atual
    }else{
      return NULL; // retorna NULL, se a raiz nao foi encontrada
    }
}

void menu(){
  printf("\nArvore B\n");
  printf("1 - Inserir\n");
  printf("2 - Buscar\n");
  printf("3 - Imprimir\n");
}

int main() {

  Arv *raiz = criaArvore();
  Arv *novo = (Arv*) malloc(sizeof(Arv));
  Arv *valor = (Arv*) malloc(sizeof(Arv));
  valor = NULL;
  Pilha *pilha = (Pilha *) malloc(sizeof(Pilha));
  pilha = NULL;
  int op, chave;

  menu();
  printf("\nDigite sua opcao: ");
  scanf("%d", &op);
  while(op != 0){

    if(op == 1){
      printf("\nDigite o valor que sera inserido: ");
      scanf("%d", &chave);
      while(chave != 0){
        novo = criaNoFolha(chave);
        raiz = insere_Arvore_B(raiz, novo, pilha);
        imprimeArvoreB(raiz);
        printf("Numero inserido!\n");
        printf("0 - Voltar\n");
        printf("\nDigite o valor que sera inserido: ");
        scanf("%d", &chave);
      }
    }else if(op == 2){
      Arv *valor = NULL;
      printf("\nDigite a chave que sera buscada: ");
      scanf("%d", &chave);
      while(chave != 0){
        valor = busca_Arvore_B(raiz, chave);
        if(valor != NULL){
          printf("\nA chave %d esta na arvore!", valor->chaveAtual);
          printf("\n0 - Voltar\n");
        }else{
          printf("\nChave nao encontrada! ");
          printf("\n0 - Voltar\n");
        }
        printf("\nDigite a chave que sera buscada: ");
        scanf("%d", &chave);
      }
    }else if(op == 3){
      imprimeArvoreB(raiz);
      printf("Arvore Imprimida!\n");
    }
    menu();
    printf("\nDigite sua opcao: ");
    scanf("%d", &op);
  }
  
  return 0;
}