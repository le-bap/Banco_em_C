#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

// lista que será usada para salvar as modificações feitas durante o uso do programa
typedef struct {
    Cliente cl[1000];
    int qnt;
}ListaClientes;


void menu();


// criar aos dados de um cliente
typedef struct {
    char *nome;
    char *cpf;
    char *tipo;
    float valor0;
    char *senha;
}Cliente;


int NovoCliente(Cliente cliente);


#endif 