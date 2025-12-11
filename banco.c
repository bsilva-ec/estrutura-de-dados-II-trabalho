#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banco.h"

void limpaBuffer() {
    int buffer;
    while ((buffer = getchar()) != '\n' && buffer != EOF) {}
}

int lerInteiro() {
    int valor;
    while (1) {
        if (scanf("%d", &valor) == 1) {
            limpaBuffer();
            return valor;
        } else {
            printf("valor invalido, tente novamente.");
            limpaBuffer();
        }
    }
}

float lerFloat() {
    float valor;
    while (1) {
        if (scanf("%f", &valor) == 1) {
            limpaBuffer();
            return valor;
        } else {
            printf("valor invalido, tente novamente.");
            limpaBuffer();
        }
    }
}

void lerString(char *texto, int tamanho) {
    scanf(" %[^\n]", texto);
    limpaBuffer();
    texto[tamanho - 1] = '\0';
}

void inicializar(Banco *banco) {
    banco->contas = (Conta*) malloc(CAPACIDADE * sizeof(Conta));
    if (banco->contas == NULL) {
        printf("erro ao alocar memoria");
        exit(1);
    }
    banco->total = 0;
    banco->capacidade = CAPACIDADE;
}

void expandirQuantidadeConta(Banco *banco) {
    int novaCapacidade = banco->capacidade * 2;
    Conta *novoEspaco = (Conta*) realloc(banco->contas, novaCapacidade * sizeof(Conta));
    if (novoEspaco == NULL) {
        printf("erro ao expandir espaco, ");
        return;
    }
    banco->contas = novoEspaco;
    banco->capacidade = novaCapacidade;
    printf("nova capacidade de contas: %d\n", novaCapacidade);
}

int buscarConta(const Banco *banco, int numConta) {
    for (int cont = 0; cont < banco->total; cont++) {
        if (banco->contas[cont].numero == numConta) {
            return cont;
        }
    }
    return -1;
}


void liberarMemoria(Banco *banco) {
    if (banco->contas != NULL) {
        free(banco->contas);
        banco->contas = NULL;
        banco->total = 0;
        banco->capacidade = 0;
        printf("Memoria liberada com sucesso!\n");
    }
}

void criarConta(Banco *banco) {
    if (banco->total >= banco->capacidade) {
        expandirQuantidadeConta(banco);
    }

    Conta novaConta;
    int numConta;
    int indiceExistente;

    do {
        printf("insira o numero da conta: ");
        numConta = lerInteiro();
        indiceExistente = buscarConta(banco, numConta);

        if (indiceExistente != -1) {
            printf("numero de conta ja existe! Tente outro.\n");
        } else {
            novaConta.numero = numConta;
            break;
        }
    } while (1);

    printf("insira o nome do titular: ");
    lerString(novaConta.titular, sizeof(novaConta.titular));

    do {
        printf("deposite um valor: ");
        novaConta.saldo = lerFloat();
        if (novaConta.saldo < 0) {
            printf("valor inicial nao pode ser negativo!\n");
        } else {
            break;
        }
    } while (1);

    banco->contas[banco->total] = novaConta;
    banco->total++;

    printf("nova conta cadastrada!! titular: %s, numero: %d, saldo: %.2f\n",
           novaConta.titular, novaConta.numero, novaConta.saldo);
}

void realizarSaque(Banco *banco) {
    if (banco->total == 0) {
        printf("nao foi possivel realizar o saque, nenhuma conta cadastrada no sistema!\n");
        return;
    }

    printf("de qual conta quer realizar o saque? ");
    int numConta = lerInteiro();
    int indice = buscarConta(banco, numConta);
    float valor;

    if (indice == -1) {
        printf("nao foi possivel realizar o saque, conta nao identificada;\n");
        return;
    }

    do {
        printf("digite o valor do saque: ");
        valor = lerFloat();
        if (valor <= 0) {
            printf("valor deve ser positivo!\n");
        } else if (valor > banco->contas[indice].saldo) {
            printf("saldo insuficiente! Saldo atual: %.2f\n", banco->contas[indice].saldo);
        } else {
            break;
        }
    } while (1);

    banco->contas[indice].saldo -= valor;
    printf("saque realizado.\n");
    printf("saldo atual: %.2f\n", banco->contas[indice].saldo);
}

void realizarDeposito(Banco *banco) {
    if (banco->total == 0) {
        printf("nao foi possivel realizar o deposito pois nao tem nenhuma conta cadastrada.\n");
        return;
    }

    printf("de qual conta deseja realizar o deposito? ");
    int numConta = lerInteiro();
    int indice = buscarConta(banco, numConta);
    float valor;

    if (indice == -1) {
        printf("numero da conta incorreto, digite novamente.\n");
        return;
    }

    do {
        printf("digite o valor de deposito: ");
        valor = lerFloat();
        if (valor <= 0) {
            printf("valor deve ser positivo!\n");
        } else {
            break;
        }
    } while (1);

    banco->contas[indice].saldo += valor;
    printf("deposito realizado.\n");
    printf("saldo atual: %.2f\n", banco->contas[indice].saldo);
}

void exibirListaConta(const Banco *banco) {
    if (banco->total == 0) {
        printf("nenhuma conta cadastrada.\n");
        return;
    }

    printf("\nlista de contas cadastradas: \n");
    printf("=================================\n");

    for (int cont = 0; cont < banco->total; cont++) {
        printf("Titular: %s\n", banco->contas[cont].titular);
        printf("Numero da conta: %d\n", banco->contas[cont].numero);
        printf("Saldo: R$ %.2f\n", banco->contas[cont].saldo);
        printf("---------------------------------\n");
    }
}

void procurarConta(const Banco *banco) {
    if (banco->total == 0) {
        printf("Nenhuma conta cadastrada.\n");
        return;
    }

    printf("Digite o numero da conta: ");
    int numConta = lerInteiro();
    int indice = buscarConta(banco, numConta);

    if (indice == -1) {
        printf("Conta nao encontrada!\n");
    } else {
        printf("\n=== Dados da Conta ===\n");
        printf("Titular: %s\n", banco->contas[indice].titular);
        printf("Numero da conta: %d\n", banco->contas[indice].numero);
        printf("Saldo: R$ %.2f\n", banco->contas[indice].saldo);
        printf("======================\n");
    }
}

void salvarContas(const Banco *banco, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar!\n");
        return;
    }

    fprintf(arquivo, "%d\n", banco->total);

    for (int i = 0; i < banco->total; i++){
        fprintf(arquivo, "%d;%s;%.2f\n",
                banco->contas[i].numero,
                banco->contas[i].titular,
                banco->contas[i].saldo);
    }
    fclose(arquivo);
    printf("Contas salvas em '%s'.\n", nomeArquivo);
}

void carregarContas(Banco *banco, const char *nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL){
        printf("Nenhum arquivo encontrado, iniciando banco vazio.\n");
        return;
    }
    banco->total=0;
    int total;
    fscanf(arquivo, "%d\n", &total);
    for (int i = 0; i < total; i++) {
    Conta novaConta;
    fscanf(arquivo, "%d;%99[^;];%f\n",
           &novaConta.numero,
           novaConta.titular,
           &novaConta.saldo);

    if (banco->total >= banco->capacidade) {
        expandirQuantidadeConta(banco);
    }
    banco->contas[banco->total++] = novaConta;
}
    fclose(arquivo);
    printf("Contas carregadas de '%s'.\n", nomeArquivo);
}
