#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

// struct que armazenará os dados de uma ação (Débito, Depósito e Transferência)
typedef struct{
    double valor;
    double taxa;
    char descricao[20];
}Operacao;

// criar aos dados de um cliente
typedef struct {
    char nome[100];
    char cpf[11];
    char tipo[10];
    float valor0;
    char senha[50];
    Operacao op[100];
    int operacoes; // contar quantas operações foram feitas (não pode ultrapassar 100)
}Cliente;

// lista que será usada para salvar as modificações feitas durante o uso do programa
typedef struct {
    Cliente cl[10];
    int qnt;
}ListaClientes;

//print menu
void menu();

// funções principais do programa
int NovoCliente(ListaClientes *lt);
int DeletarCliente(ListaClientes *lt);
int ListarClientes1(ListaClientes lt);
int Debitar(ListaClientes *lt);
int Depositar(ListaClientes *lt);
int Extrato(ListaClientes *lt, Operacao *op);
int Transferencia(ListaClientes *lt);

// funções usadas para salvar os dados e carregá-los toda vez que o programa é utilizado
int SalvarCliente(ListaClientes *lt, char nome[]);
int CarregarCliente(ListaClientes *lt, char nome[]);

// funções que facilitaram o desenvolvimento do código
void clearBuffer();

int ProcurarCPF(ListaClientes *lt, char *cpfProcurado);
int ProcurarSenha(ListaClientes *lt, char *cpfProcurado, char *senha);

int FuncaoDebitar(ListaClientes *lt, char *cpfProcurado, float valor);
int FuncaoDepositar(ListaClientes *lt, char *cpfProcurado, float valor);

int EscreverNoExtrato(Cliente cl);
int AtualizaExtrato(double valor, double taxa, char desc[], Cliente *cl);

#endif 