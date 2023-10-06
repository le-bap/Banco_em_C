#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

// criar aos dados de um cliente
typedef struct {
    char nome[100];
    char cpf[11];
    char tipo[10];
    float valor0;
    char senha[50];
}Cliente;

// lista que será usada para salvar as modificações feitas durante o uso do programa
typedef struct {
    Cliente cl[1000];
    int qnt;
}ListaClientes;

//print menu
void menu();

int NovoCliente(ListaClientes *lt);
int DeletarCliente(ListaClientes *lt);
int ListarClientes1(ListaClientes lt);
int Debitar(ListaClientes *lt);
int Depositar(ListaClientes *lt);
int Extrato(ListaClientes *lt);

int SalvarCliente(ListaClientes *lt, char nome[]);
int CarregarCliente(ListaClientes *lt, char nome[]);
void clearBuffer();

int ProcurarCPF(ListaClientes *lt, char *cpfProcurado);
int ProcurarSenha(ListaClientes *lt, char *cpfProcurado, char *senha);

#endif 