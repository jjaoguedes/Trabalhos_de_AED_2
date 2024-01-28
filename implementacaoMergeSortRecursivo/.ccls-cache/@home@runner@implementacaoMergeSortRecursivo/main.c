#include <stdio.h>
int vet_aux[] = {};
// copia o vetor
void CopiaVetor(int vetOrig[], int vetDest[], int inicio, int fim) {
  if (inicio <= fim) { 
  	vetDest[inicio] = vetOrig[inicio];
    CopiaVetor (vetOrig, vetDest, inicio+1, fim);  
  }
}

// mostra o vetor ordenado
void ImprimeVetor(int vet[], int inicio, int fim) {
  if (inicio <= fim) { 
  	printf("%d ", vet[inicio]);
    ImprimeVetor (vet, inicio+1, fim);  
  }
}

// função que verifica o menor elemento
int QualMenor(int esq, int dir) {
	if (esq <= dir){
    return 0;} 
  return 1;
}

// função que realiza a troca entre dois elementos
void VerificaTroca(int vet[], int ind1, int ind2) {
  int aux;
	if (vet[ind1] > vet[ind2]){
    aux = vet[ind1]; 
	  vet[ind1] = vet[ind2];
	  vet[ind2] = aux;
  }    
}

// função para concatenar dois vetores ordenados
void Concatena (int vet_aux[], int vetor[], int inicio, int meio,
                int fim, int ind_aux, int ind_esq, int ind_dir){
  int resp;

  if (ind_aux <= fim) { 
    if (ind_esq < meio){ // tem esquerdo
      if (ind_dir <= fim){ // tem direito
        resp = QualMenor(vetor[ind_esq],vetor[ind_dir]);
        if (resp == 0){ // menor é o esquerda
          vet_aux[ind_aux] = vetor[ind_esq];
          ind_esq+=1;
        } // (resp == 0)
        else { // menor é o direita
          vet_aux[ind_aux] = vetor[ind_dir];
          ind_dir+=1;
        } //(resp != 0)
      } //(ind_dir <= fim)
      else { // acabou o direito
        vet_aux[ind_aux] = vetor[ind_esq];  
        ind_esq+=1;
      } //(ind_dir < fim)
    }  // (ind_esq < meio)
    else { // acabou o esquerdo
      vet_aux[ind_aux] = vetor[ind_dir];
      ind_dir+=1;
    } // (ind_esq >= meio)
    ind_aux+=1;
    Concatena(vet_aux,vetor, inicio, meio, fim, ind_aux, ind_esq, ind_dir);
  } //(ind_aux <= fim)
  CopiaVetor(vet_aux, vetor,inicio, fim);
}

// função de ordenação usando MergeSort
void MergeSort(int vetor[], int inicio, int fim){
  int tamanho, meio;
  tamanho = fim-inicio+1;
  meio = (fim+inicio) / 2;
  if (tamanho == 1) { }// não precisa fazer nada
  if (tamanho == 2) { // compara os dois
    VerificaTroca (vetor, inicio, fim);
  } 
  if (tamanho > 2){ // quebra e ordena
     MergeSort(vetor, inicio, meio-1);
     MergeSort(vetor, meio, fim);
     Concatena (vet_aux, vetor, inicio, meio, fim, inicio, inicio, meio);
  }
}

int main() {
	// vetor que será ordenado
	int vet[] = {
    130, 120, 220,240,2155,250,2165,260,2125,210,2135,2105,
    230,2145,280,275,290,295,270,285,2140,235,
    2100,215,2130,265,2120,255,2160,245,2150,25,
    20,40,155,50,165,60,125,10,135,105,854,659,
    30,145,80,75,90,95,70,85,140,35,1022,210,589,
    100,15,130,65,120,55,160,45,150,25,4032,549,
    120,140,1155,150,1165,160,1125,110,1135,1105,
    130,1145,180,175,190,195,170,185,1140,135,
    1100,115,1130,165,1120,155,1160,723,856,888,145, 1150, 125};
	
	int tam = (sizeof(vet) / sizeof(int))-1;
  //int pivomain = CalculaPivo(vet[0], vet[tam]);
  printf (" \n VETOR ORIGINAL \n");
  ImprimeVetor(vet,0,tam);
	MergeSort(vet, 0, tam);
  printf (" \n VETOR FINAL \n");
	ImprimeVetor(vet,0,tam);
	return 0; 
}