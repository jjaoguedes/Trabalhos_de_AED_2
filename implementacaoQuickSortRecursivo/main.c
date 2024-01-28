#include <stdio.h>

// mostra o vetor ordenado
void ImprimeVetor(int vet[], int inicio, int fim) {
  if (inicio <= fim) { 
  	printf("%d ", vet[inicio]);
    ImprimeVetor (vet, inicio+1, fim);  
  }
}

// função que realiza a troca entre dois elementos
void Troca(int vet[], int ind1, int ind2) {
	int aux = vet[ind1];
	vet[ind1] = vet[ind2];
	vet[ind2] = aux;
}

int CalculaPivo (int valor1, int valor2){
    return (int) (valor1+valor2)/2; 
}

int VaiAtePivo(int vet[], int pivo, int inicio, int fim, int atual){
  if (vet[atual] > pivo) 
    return atual; 
  if (atual <= fim) 
    return VaiAtePivo(vet,pivo,inicio,fim,atual+1);
}  

int VoltaAtePivo(int vet[], int pivo, int inicio, int fim, int atual){
  if (vet[atual] <= pivo)
     return atual; 
  if (atual >= inicio) 
    return VoltaAtePivo(vet,pivo,inicio,fim,atual-1);
}

void Quick(int vetor[], int inicio, int fim, int PosEsq, int PosDir){
  int pivo, n;
  pivo = CalculaPivo(vetor[inicio], vetor[fim]);     
  PosEsq = VaiAtePivo(vetor,pivo,PosEsq,PosDir,PosEsq);
  PosDir = VoltaAtePivo(vetor,pivo,PosEsq,PosDir,PosDir);
  if ((PosEsq <= fim) && (PosDir >= inicio)){
    if (PosEsq < PosDir){
      Troca(vetor, PosDir, PosEsq);
      Quick(vetor, inicio, fim, PosEsq, PosDir);
     }
    else { 
      Quick(vetor,inicio,PosEsq-1,inicio, PosEsq-1);
      Quick(vetor,PosEsq, fim, PosEsq, fim);
    }
  }
}

int main() {
	// vetor que será ordenado
	int vet[] = {
    220,240,2155,250,2165,260,2125,210,2135,2105,
    230,2145,280,275,290,295,270,285,2140,235,
    2100,215,2130,265,2120,255,2160,245,2150,25,
    20,40,155,50,165,60,125,10,135,105,
    30,145,80,75,90,95,70,85,140,35,
    100,15,130,65,120,55,160,45,150,25,
    120,140,1155,150,1165,160,1125,110,1135,1105,
    130,1145,180,175,190,195,170,185,1140,135,
    1100,115,1130,165,1120,155,1160,145,1150,125};
	//int vet[] = {61,23,63, 94,51,89,98,100,70,63,44};
	int tam = (sizeof(vet) / sizeof(int))-1;
  //int pivomain = CalculaPivo(vet[0], vet[tam]);

  printf (" \n VETOR ORIGINAL \n");
  ImprimeVetor(vet,0,tam);
	Quick(vet, 0, tam, 0, tam);
  printf (" \n VETOR FINAL \n");
	ImprimeVetor(vet,0,tam);
	return 0; 
}