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
        scanf(" %[^\n]s", lt->cl[lt->qnt].nome);
        clearBuffer();

        printf("Digite o seu cpf: ");
        scanf("%[^\n]s", lt->cl[lt->qnt].cpf);
        clearBuffer();

        printf("O tipo de conta: ");
        scanf("%[^\n]s", lt->cl[lt->qnt].tipo);
        clearBuffer();

        printf("Digite o valor inicial da conta: ");
        scanf("%f", &lt->cl[lt->qnt].valor0);
        clearBuffer();

        printf("Senha do usuario: ");
        scanf("%[^\n]s", lt->cl[lt->qnt].senha);
        clearBuffer();
    }
    else{
        printf("Maximo de clientes atingidos");
    }
    lt -> qnt++;
    return 0;
}

int SalvarCliente(ListaClientes *lt, char nome[]){
    FILE *f = fopen(nome, "wb");
    if(f == NULL){
        return 1;
    }else{
        fwrite(lt, sizeof(ListaClientes), 1, f);
        fclose(f);
    }
    return 0;
}

int CarregarCliente(ListaClientes *lt, char nome[]){
    FILE *f = fopen(nome, "rb");
    if(f == NULL){
        return 1;
    }
    else{
        fread(lt,sizeof(ListaClientes), 1, f);
        fclose(f);
    }
}

void clearBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// NAO ESQUECER DOS COMMITS