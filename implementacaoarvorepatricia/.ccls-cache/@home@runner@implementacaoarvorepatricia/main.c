/*  
    Árvore Patrícia
    Última modificação: 10/02/2023
    Autor: João Victor Félix Guedes - 22050227
    Disciplina: Algoritmos e Estrutura de dados II
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct No{
    struct No *filhoEsq;
    struct No *filhoDir;
    int posicao;
    char palavra[20];
    int linha;
};
typedef struct No Arv;

/*Recebe como parâmetro uma string e um numero inteiro que representa a posição do
caractere, logo a função retorna a palavra toda em minusculo.
*/
char *transforma_Minusculo(char *string, int posicao){
    
    if(string[posicao] == '\0'){
      return string;
    }else{
        string[posicao] = tolower(string[posicao]);
        return transforma_Minusculo(string, posicao + 1);
    }
}

/*Recebe como parâmetro duas strings e um numero inteiro inicial, assim retornando a posição dos caracteres que se divergem.
*/
int encontra_Divergencia(char string1[20],char string2[20], int posicao){
  
    if(string1[posicao] == '\0' || string2[posicao] == '\0' || string1[posicao] != string2[posicao]){
        return posicao;
    }else{
      return encontra_Divergencia(string1, string2, posicao + 1);
    }
}

/*Recebe como parâmetro uma string e um numero inteiro inicial, assim retornando verdadeiro se tiver três ou mais caracteres na palavra.
*/
int conta_caractere(char string[20], int posicao){

   if(string[posicao] == '\0'){
       if(posicao >= 3){
           return 1;
       }else{
           return 0;
       }
    }else{
      return conta_caractere(string, posicao+1);
    }
}

// Recebe um parâmetro e cria um nó folha com a informação.
Arv *criaNo_Folha(char nova_Palavra[20], int num_linha){
    
    Arv *novo = (Arv*) malloc(sizeof(Arv));
    
    strcpy(novo->palavra, nova_Palavra);
    novo->filhoEsq = NULL;
    novo->filhoDir = NULL;
    novo->linha = num_linha;
    novo->posicao = 0;
    
    return novo;
    
}

/*Recebe uma raiz, um nó folha novo, a posição divergente e cria um nó intermediário para o lado Esquedo da raiz com a informação.*/
Arv *criaNo_IntermediarioEsq(Arv *raiz,  Arv *novaPalavra, int posicao){

  Arv *novo = (Arv*) malloc(sizeof(Arv));

  novo->filhoDir = NULL;
  novo->filhoEsq = NULL;
  novo->posicao = posicao;
  strcpy(novo->palavra, raiz->palavra);
  
  return novo;
}

/*Recebe uma raiz, um nó folha novo, a posição divergente e cria um nó intermediário para o lado Direito da raiz com a informação.*/
Arv *criaNo_IntermediarioDir(Arv *raiz,  Arv *novaPalavra, int posicao){

  Arv *novo = (Arv*) malloc(sizeof(Arv));
  
  novo->filhoDir = NULL;
  novo->filhoEsq = NULL;
  novo->posicao = posicao;
  strcpy(novo->palavra, novaPalavra->palavra);

  return novo;
  
}

void *criaArvore(){ //funcao cria arvore, onde returna NULL
    return NULL;
}

/*Recebe uma raiz e um novo nó folha e trata os seguintes casos:
- Se a raiz for nula, retorna o novo folha;
- Se a raiz for folha, vai ser encontrado a posicao dos caracteres que as palavras da raiz e o novo nó folha divergem e fazendo-se a diferença da posição. Assim é 
comparado os caracteres para saber quem é o maior ou menor em qual filho da raiz deve-se inserir o novo nó folha. Se for menor, é criado uma nova raiz chamando a função criaNo_IntermediarioEsq e recebendo os filhos a raiz e o novo nó. Se for Maior, é criado uma nova raiz chamando a função criaNo_IntermediarioDir e recebendo os filhos a raiz e o novo nó. 
- Se a raiz não é uma folha, compara a posição na qual as palavras divergem e segue para a subárvore correspondente, recursivamente.
*/
Arv *insere_Arvore_Patricia(Arv *raiz, Arv *novo){

  int posicao=0;
  int diferencaposicao=0;
  Arv *novaRaiz =  NULL;

 if(raiz == NULL){ 
    return novo;
  }else if(raiz->filhoEsq == NULL && raiz->filhoDir == NULL){
    posicao = encontra_Divergencia(raiz->palavra, novo->palavra, posicao);
    diferencaposicao = posicao-raiz->posicao;
    if(novo->palavra[posicao] < raiz->palavra[posicao]){
      novaRaiz = criaNo_IntermediarioEsq(raiz, novo, diferencaposicao);
      novaRaiz->filhoDir = raiz;
      novaRaiz->filhoEsq = novo;
      return novaRaiz;
    }else{
      novaRaiz = criaNo_IntermediarioDir(raiz, novo, diferencaposicao);
      novaRaiz->filhoDir = novo;
      novaRaiz->filhoEsq = raiz;
      return novaRaiz;
    }
  }else{
     posicao = encontra_Divergencia(raiz->palavra, novo->palavra, posicao);
    if(novo->palavra[posicao+raiz->posicao] < raiz->palavra[posicao+raiz->posicao]){
      raiz->filhoEsq = insere_Arvore_Patricia(raiz->filhoEsq, novo);
    }else{
      raiz->filhoDir = insere_Arvore_Patricia(raiz->filhoDir, novo);
    }
   return raiz;
  }
}

/* Verifica se a raiz é nula, se for, a busca é interrompida e retorna 0. Se a raiz for uma folha, compara sua palavra com a string buscada. Se são iguais, retorna-se 1, caso contrário retorna 0. Se a raiz não é uma folha, compara a posição na qual as palavras divergem e segue para a subárvore correspondente, buscando recursivamente.
*/
int busca_Arvore_Patricia(Arv *raiz, char string[20]){
  int posicao = 0;
  if(raiz == NULL){
    return 0;
  }else if(raiz->filhoEsq == NULL && raiz->filhoDir == NULL){
    if(strcmp(raiz->palavra, string) == 0){
      return 1;
    }else{
      return 0;
    }
  }else{
    posicao = encontra_Divergencia(raiz->palavra, string, posicao);
    if(string[posicao+raiz->posicao] < raiz->palavra[posicao+raiz->posicao]){
      return busca_Arvore_Patricia(raiz->filhoEsq, string);
    }else{
      return busca_Arvore_Patricia(raiz->filhoDir, string);
    }
  }
}

//Imprime a Árvore Patricia
void imprimeArvore(Arv *raiz){
  
  if(raiz != NULL){
		imprimeArvore(raiz->filhoEsq);
   if((raiz->filhoEsq == NULL && raiz->filhoDir == NULL) && ((conta_caractere(raiz->palavra,0)) == 1)){
      printf("%s ", raiz->palavra);
      printf("%d\n", raiz->linha);
    }
		imprimeArvore(raiz->filhoDir);
	}
}

int main()
{
  Arv *raiz = criaArvore();
  Arv *novo = (Arv*) malloc(sizeof(Arv));
    
  FILE *arq;
  char string[41];
  char *palavra;
  int linha=0;
  
  arq = fopen("teste_patricia.txt", "r");

  if(arq == NULL){
    printf("Erro ao abrir o arquivo\n");
  }

  while(fgets(string,40, arq) != NULL){

    char *x = strchr(string, '\n'); /* A função strchr procura o caractere '\n' na palavra e substitui por '\0' para indicar o final da string.*/
    if(x != NULL){
      *x = '\0';
    }
    if(*x == '\0'){ 
      linha++;
    }
    // A função strtok é usada para extrair as palavras da linha lida.
    //Cada string extraída é armazenada na variável palavra.
    palavra = strtok(string, ", .");
    while(palavra != NULL){
        novo = criaNo_Folha(transforma_Minusculo(palavra,0), linha);
        raiz = insere_Arvore_Patricia(raiz, novo);
      // A função strtok é chamada novamente para obter a próxima palavra da linha.
      palavra = strtok(NULL, ", .");
    }
  }
  fclose(arq);
  imprimeArvore(raiz);
    return 0;
}
