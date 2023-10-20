#include <stdio.h>
#include <string.h>
#include "biblioteca.h"

// utilizado para rodar o menu toda vez que alguma ação for realizada no programa
void menu(){
    printf("\nBanco QuemPoupaTem\n");
    printf("\nEscolha uma das opções abaixo:\n1. Novo Cliente\n2. Apaga Cliente\n3. Listar Clientes\n4. Débito\n5. Depósito\n6. Extrato\n7. Transferência entre contas\n0. Sair\n");
    printf(">>> ");
}

// função que criará a conta de um novo cliente
int NovoCliente(ListaClientes *lt){
    if(lt->qnt<1000){ // só irá cadastrar se o banco tiver menos de 1000 clientes no sistema
        printf("Digite o seu nome: "); // é requisitado os dados de cadastro e cada um é armazenado em uma variável dentro da struct que pertencerá ao cliente
        scanf(" %[^\n]s", lt->cl[lt->qnt].nome);
        clearBuffer();

        printf("Digite o seu cpf: ");
        scanf("%[^\n]s", lt->cl[lt->qnt].cpf);
        clearBuffer();

        printf("Tipo de conta (comum ou plus): ");
        scanf("%[^\n]s", lt->cl[lt->qnt].tipo);
        clearBuffer();

        printf("Digite o valor inicial da conta: ");
        scanf("%f", &lt->cl[lt->qnt].valor0);
        clearBuffer();

        printf("Senha do usuario: ");
        scanf("%[^\n]s", lt->cl[lt->qnt].senha);
        clearBuffer();
    }
    else{ // se houver mais de 1000 clientes
        printf("Maximo de clientes atingidos");
    }
    lt -> qnt++;
    return 0;
}

int DeletarCliente(ListaClientes *lt){ // apaga a conta do cliente
    char clienteEscolhido[11];
    printf("Digite o CPF da conta que deseja deletar: "); // informa o cpf do cliente que será deletado
    scanf("%s", clienteEscolhido);
    clearBuffer();

    int escolhido = ProcurarCPF(lt, clienteEscolhido); // verifica se o cpf é valido

    if (escolhido == -1){ // caso o cpf não exista
        printf("Cliente não encontrado");
    }
    else{ // se existir, a conta dos clientes posteriores a ele serão "copiadas" uma posição atrás
        for (int i = escolhido; i != 999; i++){
        lt->cl[i] = lt->cl[i + 1];
        }
    }

    lt->qnt--;// atualização da quantidade de clientes cadastrados
    return 0;
}

int ListarClientes1(ListaClientes lt){ // lista as informações de todos os clientes
    for (int i = 0; i < lt.qnt; i++){ //loopingg que ira pegar cada informação da struct Cliente e printar no terminal
            printf("Nome: %s\n", lt.cl[i].nome);
            printf("CPF: %s\n", lt.cl[i].cpf);
            printf("Tipo de conta: %s\n", lt.cl[i].tipo);
            printf("Senha: %s\n", lt.cl[i].senha);
            printf("Valor: %.2f\n",  lt.cl[i].valor0);
            printf("\n");
        }
    return 0;
}

int Debitar(ListaClientes *lt){ // realizada o débito
    char senha[50];
    float valor;
    char clienteEscolhido[11];

    printf("Digite o CPF da conta que deseja debitar: "); // informa o cliente a ser debitado
    scanf("%s", clienteEscolhido);
    clearBuffer();
    int escolhido = ProcurarCPF(lt, clienteEscolhido); // acha o cpf do cliente para localizar seus dados

    if(escolhido == -1){ // caso o cpf não seja encontrado
        printf("CPF nao encontrado.");
        printf("\n");
    }
    else{
        printf("Digite a senha: "); // caso ache, pede a senha 
        scanf("%s", senha);
        int senhaCerta = ProcurarSenha(lt, clienteEscolhido, senha); 
        
        if(senhaCerta == 1){ // se a senha estiver certa, realiza o dépito
            printf("Digite o valor a ser debitado: ");
            scanf("%f", &valor);
            
            int retorno = FuncaoDebitar(lt, clienteEscolhido, valor); // função debitar que realiza o debito

            if (retorno == 0){ // indica que o cliente é do tipo comum para calcular a taxa
                float taxa = valor * 0.05;
                AtualizaExtrato(valor, taxa, "Debito:", &lt->cl[escolhido]);
            }
            else if (retorno == 2){ // // indica que o cliente é do tipo plus para calcular a taxa
                float taxa = valor * 0.03;
                AtualizaExtrato(valor, taxa, "Debito:", &lt->cl[escolhido]);
            }
        }
        else{ // se a senha estiver errada, sai da função
            printf("Senha errada\n");
        }
    }
}

int Depositar(ListaClientes *lt){ // realiza o depósito
    char senha[50];
    float valor;
    char clienteEscolhido[11];

    printf("Digite o CPF da conta que deseja depositar: "); // informa o cliente a ser depositado
    scanf("%s", clienteEscolhido);
    clearBuffer();
    int escolhido = ProcurarCPF(lt, clienteEscolhido); // acha o cpf do cliente para localizar seus dados

    if(escolhido == -1){
        printf("CPF nao encontrado.");
        printf("\n");
    }
    else{ // se achou o cpf indicado
        printf("Digite a senha: ");
        scanf("%s", senha);
        int senhaCerta = ProcurarSenha(lt, clienteEscolhido, senha);
        
        if(senhaCerta == 1){ // se a senha estiver correta
            printf("Digite o valor a ser depositado: ");
            scanf("%f", &valor);
            FuncaoDepositar(lt, clienteEscolhido, valor); // realiza o depósito com a FuncaoDepositar
            AtualizaExtrato(valor, 0, "Deposito:", &lt->cl[escolhido]); // atualiza o extrato sobre a ação
        }
        else{// se a senha estiver errada, sai da função
            printf("Senha errada\n");
        }
    }
}

int Extrato(ListaClientes *lt, Operacao *op){ // cria um arquivo txt para o cliente que desejar ver seu extrato

    char senha[50];
    char clienteEscolhido[11];

    printf("Digite o CPF da conta que deseja ver o extrato: "); // informa o cpf do cliente que quer ver o extrato
    scanf("%s", clienteEscolhido);
    clearBuffer();
    int escolhido = ProcurarCPF(lt, clienteEscolhido); // acha o cpf do cliente para localizar seus dados

    if(escolhido == -1){
        printf("CPF nao encontrado.");
        printf("\n");
    }
    else{ // se o cpf estiver correto 
        printf("Digite a senha: ");
        scanf("%s", senha);
        int senhaCerta = ProcurarSenha(lt, clienteEscolhido, senha);

        if (senhaCerta == 1){ // se a senha estiver certa, gera o arquivo Extrato.txt
            EscreverNoExtrato(lt->cl[escolhido]);
        }
        else{
            printf("Senha errada\n");
        }
    }
}
int Transferencia(ListaClientes *lt){ // realiza a transferencia 

    char senha[50];
    float valor;
    char clienteDepositar[11];
    char clienteDebitar[11];

    printf("Digite o seu CPF: "); // informe o cpf de quem vai transferir
    scanf("%s", clienteDebitar);
    clearBuffer();
    int debitado = ProcurarCPF(lt, clienteDebitar); // acha o cpf do cliente para localizar seus dados
    if(debitado == -1){
        printf("CPF nao encontrado.");
        printf("\n");
    }
    else{ // se achar o cpf do que deseja realizar a transferencia, pede sua senha
        printf("Digite a senha: ");
        scanf("%s", senha);
        int senhaCerta = ProcurarSenha(lt, clienteDebitar, senha); 

        if(senhaCerta == 1){ // se a senha estiver certa, pede o cpf do cliente que receberá o dinheiro
            printf("Digite o CPF a ser depositado: ");
            scanf("%s", clienteDepositar);
            int recebido = ProcurarCPF(lt, clienteDepositar);

            if(recebido == -1){
                printf("Cliente não encontrado.");
            }
            else{ // se este cpf for encontrado
                printf("Digite o valor a ser depositado: ");
                scanf("%f", &valor);
                FuncaoDepositar(lt, clienteDepositar, valor); // deposita o dinheiro na conta do cliente que receberá ("recebido")

                int retorno = FuncaoDebitar(lt, clienteDebitar, valor);// debita o dinheiro na conta do cliente que tranferiu ("debitado")

                if (retorno == 0){ // indica que o cliente é do tipo comum
                    float taxa = valor * 0.05;
                    AtualizaExtrato(valor, taxa, "Tranferiu:", &lt->cl[debitado]); // atualiza o extrato do "debitado" com a taxa correspondente
                }
                else if (retorno == 2){ // indica que o cliente é do tipo comum
                    float taxa = valor * 0.03;
                    AtualizaExtrato(valor, taxa, "Transferiu:", &lt->cl[debitado]);// atualiza o extrato do "debitado" com a taxa correspondente
                }

                AtualizaExtrato(valor, 0, "Recebeu:", &lt->cl[recebido]); // atualiza o extrato do "recebido" com a taxa correspondente
            
            }
        }
        else{
            printf("Senha errada\n");
        }
    }
}

//////////////////////////////////////////////////////////////////
int SalvarCliente(ListaClientes *lt, char nome[]){ // Abre o aquivo txt para escrever as informações de todos so clientes
    FILE *f = fopen(nome, "wb");
    if(f == NULL){
        return 1;
    }else{
        fwrite(lt, sizeof(ListaClientes), 1, f);
        fclose(f);
    }
    return 0;
}

int CarregarCliente(ListaClientes *lt, char nome[]){ // Carrega o arquivo Cliente.txt 
    FILE *f = fopen(nome, "rb");
    if(f == NULL){
        return 1;
    }
    else{
        fread(lt,sizeof(ListaClientes), 1, f);
        fclose(f);
    }
}

void clearBuffer(){ //evita erros com a função scanf
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

/////////////////////////////////////////////////////
int ProcurarCPF(ListaClientes *lt, char *cpfProcurado) { //Função de verificar CPF

    // Percorre a lista de clientes
    for (int i = 0; i < lt->qnt; i++) {
        // Compara o CPF atual com o CPF procurado
        if (strcmp(lt->cl[i].cpf, cpfProcurado) == 0) {
            return i;  // Encontrou o CPF, retorna o cliente correspondente
        }
    }

    return -1;  // CPF não encontrado
}

int ProcurarSenha(ListaClientes *lt, char *cpfProcurado, char *senha) { // Função de verificar Senha
    int cpf = ProcurarCPF(lt, cpfProcurado); // Obtém o índice do cliente com o CPF

    // Verifica se o CPF foi encontrado
    if (cpf != -1) {
        // Compara as senhas usando strcmp
        if (strcmp(lt->cl[cpf].senha, senha) == 0) {
            return 1;  // Senha correta
        } else {
            return 0;  // Senha incorreta
        }
    }
}
/////////////////////////////////////////////////////

int FuncaoDebitar(ListaClientes *lt, char *cpfProcurado, float valor){ // Função que realiza o débito
    int cpf = ProcurarCPF(lt, cpfProcurado); // Obtém o índice do cliente com o CPF
    
    // Verifica se o CPF foi encontrado
    if (cpf != -1) {
        if (strcmp(lt->cl[cpf].tipo, "comum") == 0){ // se a conta for do tipo comum 
            float taxa = valor * 0.05;
            float soma = lt->cl[cpf].valor0 - valor - taxa;
            if(soma > -1000){ // estabelece a taxa de desconto e verifica se o saldo é menor do que o permitido
                lt->cl[cpf].valor0 = soma;

            return 0; // se o cliente for do tipo comum, retorna 0
            }else{
                printf("Saldo insuficiente");
                return -1; // se nao tiver credito, retorna -1
            }

        }else if(strcmp(lt->cl[cpf].tipo, "plus") == 0){ // verifica se a conta é plus
            float taxa2 = valor * 0.03;
            float soma2 = lt->cl[cpf].valor0 - valor - taxa2;
            if(soma2 > -5000){// estabelece a taxa de desconto e verifica se o saldo é menor do que o permitido
                lt->cl[cpf].valor0 = soma2;
            }else{
                printf("Saldo insuficiente");
                return -1;
            }

            return 2; // se for plus, retorna 2
        }  
    } 
}

int FuncaoDepositar(ListaClientes *lt, char *cpfProcurado, float valor){ // realiza o deposito 
    int cpf = ProcurarCPF(lt, cpfProcurado);
     // Verifica se o CPF foi encontrado
    if (cpf != -1) {
        lt->cl[cpf].valor0 = lt->cl[cpf].valor0 + valor; // Acrescenta o valor a conta
    } 
    return 0;
} 

int EscreverNoExtrato(Cliente cl){ // Escreve no extrato as informações de todas as operações
    FILE *arq = fopen("Extrato.txt", "w");

    for(int i = 0; i < cl.qnt_op; i++){// le as informações que estão em "op" e escreve no arquivo do cliente especifico
        fprintf(arq,"%s\n" ,cl.op[i].descricao);
        fprintf(arq, "Valor: %.2lf\n",cl.op[i].valor);
        fprintf(arq, "Taxa: %.2lf\n\n",cl.op[i].taxa);
    }
   
    fclose(arq);
    return 0;
}

int AtualizaExtrato(double valor, double taxa, char desc[], Cliente *cl){ // atualiza as informações de cada operação 
  
    if (cl->qnt_op> 99)// Verifica se há menos do que 100 operações
        for (int i = 0; i < cl->qnt_op - 1; i++){ // se chegar a 100, apaga 1 operação
            cl->op[i] = cl->op[i + 1];
        }

    cl->op[cl->qnt_op].valor = valor;/////// atualiza valorezes, taxa e descrição de cada operação
    cl->op[cl->qnt_op].taxa = taxa;
    strcpy(cl->op[cl->qnt_op].descricao, desc);
    cl->qnt_op ++;
}

// NAO ESQUECER DOS COMMITS