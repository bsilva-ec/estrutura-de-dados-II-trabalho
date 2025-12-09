#include <stdio.h>
#include "banco.h"

int main() {
    Banco meuBanco;
    inicializar(&meuBanco);
    int opcao;

    do {
        printf("\n\n=== BEM VINDO AO BANCO ===\n");
        printf("1. Criar conta\n");
        printf("2. Realizar deposito\n");
        printf("3. Realizar saque\n");
        printf("4. Listar contas cadastradas\n");
        printf("5. Procurar Conta\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

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

    // Liberando memória antes de sair
    liberarMemoria(&meuBanco);

    return 0
}
