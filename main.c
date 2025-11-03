#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAPACIDADE 2

typedef struct{
    char titular[100];
    int numero;
    float saldo;
}Conta;

typedef struct{
    int total;
    Conta *contas;
    int capacidade;
    
}Banco;

void limpaBuffer(){
    int buffer;
    while ((buffer=getchar()) != '\n'){}
}

int lerInteiro(){
    int valor;
    while(1){
        if(scanf("%d", &valor) == 1){
        limpaBuffer();
        return valor;
        }else{
        printf("valor invalido, tente novamente.");
        limpaBuffer();
        }
    }
}

float lerFloat(){
    float valor;
    while(1){
        if(scanf("%f", &valor) == 1){
            limpaBuffer();
            return valor;
        }else{
            printf("valor invalido, tente novamente.");
            limpaBuffer();
        }
    }
}

void lerString(char *texto, int tamanho){
    scanf(" %[^\n]", texto);
    limpaBuffer();
    texto[tamanho - 1] = '\0';
}

void inicializar(Banco *banco){
    (*banco).contas = (Conta*) malloc ( CAPACIDADE * sizeof(Conta));
    
    if((*banco).contas == NULL){
        printf("erro ao alocar memoria");
    }
    
    (*banco).total = 0;
    (*banco).capacidade = CAPACIDADE;
    
}

int main()
{
   
    
    return 0;
}

























