#include <stdio.h>
#include "biblioteca.h"

// utilizado para rodar o menu toda vez que alguma ação for realizada no programa
void menu(){
    printf("\nBanco QuemPoupaTem\n");
    printf("\nEscolha uma das opções abaixo:\n1. Novo Cliente\n2. Apaga Cliente\n3. Listar Clientes\n4. Débito\n5. Depósito\n6. Extrato\n7. Transferência entre contas\n0. Sair\n");
    printf(">>> ");
}

int NovoCliente(ListaClientes *lt){
    if(lt->qnt<100){
        printf("Digite o seu nome: ");
        scanf(" %[^\n]", &lt->cl[lt->qnt].nome);

        printf("Digite o seu cpf (11): ");
        scanf(" %[^\n]", &lt->cl[lt->qnt].cpf);

        printf("O tipo de conta: ");
        scanf(" %[^\n]", &lt->cl[lt->qnt].tipo);

        printf("Digite o valor inicial da conta: ");
        scanf(" %[^\n]", &lt->cl[lt->qnt].valor0);

        printf("Senha do usuario: ");
        scanf(" %[^\n]", &lt->cl[lt->qnt].senha);
    }
    else{
        printf("Maximo de clientes atingidos");
    }
    lt -> qnt++;
    return 0;
}

// NAO ESQUECER DOS COMMITS