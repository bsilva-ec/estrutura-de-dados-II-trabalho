#include <stdio.h>
#include "banco.h"

<<<<<<< Updated upstream
int main() {
    Banco meuBanco;
    inicializar(&meuBanco);
    int opcao;

    carregarContas(&meuBanco, "contas.txt");

    do {
        printf("\n\n=== BEM VINDO AO BBC-Bank ===\n");
        printf("1. Criar conta\n");
        printf("2. Realizar deposito\n");
        printf("3. Realizar saque\n");
        printf("4. Listar contas cadastradas\n");
        printf("5. Procurar Conta\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
=======
typedef struct{
    char titular[100];
    int numero;
    float saldo;
}Conta;
//ffsfsdfds
typedef struct{
    int total;
    Conta *contas;
    int capacidade;

}Banco;
>>>>>>> Stashed changes

        opcao = lerInteiro();

        switch (opcao) {
            case 1:
                criarConta(&meuBanco);
                break;
            case 2:
                realizarDeposito(&meuBanco);
                break;
            case 3:
                realizarSaque(&meuBanco);
                break;
            case 4:
                exibirListaConta(&meuBanco);
                break;
            case 5:
                procurarConta(&meuBanco);
                break;
            case 0:
                printf("Encerrando o banco...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    //Criando o .txt
    salvarContas(&meuBanco, "contas.txt");
    // Liberando memória antes de sair
    liberarMemoria(&meuBanco);

    return 0;
}
<<<<<<< Updated upstream
=======

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

























>>>>>>> Stashed changes
