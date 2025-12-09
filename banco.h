#ifndef BANCO_H
#define BANCO_H
#define CAPACIDADE 2

typedef struct {
    char titular[100];
    int numero;
    float saldo;
} Conta;

typedef struct {
    int total;
    Conta *contas;
    int capacidade;
} Banco;

// Funções utilitárias
void limpaBuffer();
int lerInteiro();
float lerFloat();
void lerString(char *texto, int tamanho);

// Funções do banco
void inicializar(Banco *banco);
void expandirQuantidadeConta(Banco *banco);
int buscarConta(const Banco *banco, int numConta);
int buscarContaPorNome(const Banco *banco, const char *nome);
void liberarMemoria(Banco *banco);

void criarConta(Banco *banco);
void realizarSaque(Banco *banco);
void realizarDeposito(Banco *banco);
void exibirListaConta(const Banco *banco);
void procurarConta(const Banco *banco);

#endif
