#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

// criar aos dados de um cliente
typedef struct {
    char nome[100];
    char cpf[11];
    char tipo[10];
    float valor0;
    char senha[10];
}Cliente;

// lista que será usada para salvar as modificações feitas durante o uso do programa
typedef struct {
    Cliente cl[1000];
    int qnt;
}ListaClientes;

//print menu
void menu();

int NovoCliente(ListaClientes *lt);


#endif 