#include <stdio.h>
#include "biblioteca.h"

// utilizado para rodar o menu toda vez que alguma ação for realizada no programa
void menu(){
    int op;
    printf("\nBanco QuemPoupaTem\n");
    printf("\nEscolha uma das opções abaixo:\n1. Novo Cliente\n2. Apaga Cliente\n3. Listar Clientes\n4. Débito\n5. Depósito\n6. Extrato\n7. Transferência entre contas\n0. Sair\n");
    printf(">>> ");
    scanf("%d", &op);
}

// função que criará o cadastro de um novo cliente
//int NovoCliente(ListaClientes){
//    if (ListaCliente->qtd < 1000){
//        printf("\nNome: ");
//        scanf("%[^\n]", &cliente->nome);
//        printf("\nCPF: ");
//        scanf("%[^\n]", &cliente->cpf);
//        printf()
//    }
//}