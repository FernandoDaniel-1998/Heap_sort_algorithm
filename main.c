/* Está incompleto */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// DECLARANDO AS FUNÇÕES UTILIZADAS
char ** alocar_dinamicamente(char **palavras, int total_palavras);
void libera(char **palavras, int total_palavras);
void max_heapify(char *palavras, int total_palavras);
void build_heap_max(char *palavras);
char heap_extract_max(char *palavras);
char **heap_sort(char **palavras, int total_palavras);

int main(void) {

  int total_palavras,quant_palavras;
  char **palavras, **palavras_ord;

  scanf("%d",&total_palavras);

  palavras = alocar_dinamicamente(palavras,total_palavras);

  scanf("%d",&quant_palavras);
  
  int posicao[quant_palavras];
  for(int i = 0; i < quant_palavras ; i++){
    scanf("%d",&posicao[i]);
  }

  //  PARTE DE VERIFICAÇÃO DE ERRO
  for(int i = 0; i < total_palavras; i++){
    
    for(int j = 0; j < 20;j++){
      
      if(palavras[i][j] > 122 || palavras[i][j] < 97){
        printf("a palavra %s eh invalida",palavras[i]);
        libera(palavras,total_palavras);
        return 0;
        
      }
    }
  }

  //  PARTE DA SAÍDA "build_heap"
  printf("build_heap: ");
  
  for(int i = 0; i < quant_palavras; i++){
    printf("%s ",*(palavras+(posicao[i])));
  }

  printf("\n");

  //  ALOCANDO DINAMICAMENTE AS PALAVRAS SELECIONADAS NUMA OUTRA MATRIZ PARA ORDENÁ-LAS

  palavras_ord = (char**) malloc(quant_palavras * sizeof(char*));

  for(int i = 0; i < quant_palavras; i++){
    *(palavras_ord+i) = (char*) malloc(strlen(*(palavras+(posicao[i]))) * sizeof(char));
  }

  for(int i = 0; i < quant_palavras; i++){
    strcpy(*(palavras_ord+i),(*(palavras+(posicao[i]))));
  }

  // palavras_ord = heap_sort(palavras,);

  libera(palavras,total_palavras);
  libera(palavras_ord,quant_palavras);
  
  return 0;
}

void libera(char **palavras, int total_palavras){ // FUNÇÃO CRIADA PARA LIBERAÇÃO DE MATRIZ DE STRINGS
  
  for(int i = 0; i < total_palavras; i++){ // NESSE LAÇO FOR, SERÃO LIBERADOS TODAS AS LINHAS DA MATRIZ
    free(*(palavras+i));
  }
  
  free(palavras); // SIMPLEMENTE LIBERARÁ O PONTEIRO PARA A MATRIZ

}

char ** alocar_dinamicamente(char **palavras, int total_palavras){
  
  palavras = (char**) malloc(total_palavras * sizeof(char*)); // NESTE PASSO UM ARRAY DE PONTEIROS PARA STRINGS É ALOCADO DINAMICAMENTE

  for(int i = 0; i < total_palavras; i++){ // NESTE LAÇO, ESTÁ SENDO ALOCADO CADA CONTEUDO DE LINHA (COLUNAS)
    *(palavras+i) = (char*) malloc(20 * sizeof(char));
  }

  for(int i = 0; i < total_palavras; i++){ // ESTE LAÇO SIMPLESMENTE LERÁ O CONTEUDO DE CADA LINHA DA MATRIZ
    scanf("%s",*(palavras+i));
  }
  
  return palavras;
}

void swap(char *char1, char *char2){ // FUNÇÃO QUE FAZ A TROCA DOS ELEMENTOS NUMA STRING
  
  char aux;
  aux = *char1; // "aux" APENAS ARMAZENA O VALOR DO PRIMEIRO ELEMENTO
  *char1 = *char2;
  *char2 = aux;
  
}

void max_heapify(char *palavras, int indice){
  
  int l = 2*indice;  //2*i
  int r = 2*(indice+1); //2*i+1
  int max;
  if (l <= strlen(palavras) && (palavras[l]>palavras[indice])){
    max = l;
    }
  else max = indice;
  
  if ((r <= strlen(palavras)) && (palavras[r]>palavras[max]))
    max = r;
  
  if (max != indice) {
    swap(&palavras[indice],&palavras[max]);
    max_heapify(palavras, max);
  }

}

void build_heap_max(char *palavras){
  int n = strlen(palavras);
  
  for (int i = n/2; i >=0 ; i--){
    max_heapify(palavras, i);
  }

}

char heap_extract_max(char *palavras){
  if (strlen(palavras) < 1){
    return -1; // ELEMENTO VAZIO
    }
  
  char max = palavras[1];
  char last = strlen(palavras);
  
  palavras[1] = palavras[last];
  palavras[last] = '\0';
  max_heapify(palavras,1);
  
  return max;

}

char **heap_sort(char **palavras, int total_palavras){

  build_heap_max(*palavras);
  
  int n = strlen(*palavras);
  char string[n];

  while(n > 0){
    
    string[n] = heap_extract_max(*palavras);
    n--;
    
  }
  
  return palavras;
}