#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#define MAX_NOME 50
#define MIN_IDADE 18
#define MAX_CLIENTES 50
#define MAX_CPF 14


struct clientes
{
    char nome[MAX_NOME];
    int idade;
    char CPF[MAX_CPF]; 
    int conta_corrente;
    int conta_poupanca;
    int saldo;
    int id_cliente;
    bool status;
    
};typedef struct clientes clientes;

enum
{
    SAIR,
    CADASTRAR,
    LISTAR,
    DEPOSITAR,
    SACAR,
    FECHAR_CONTA,
    EMPRESTAR
};
enum{

    CONTA_CORRENTE = 1,
    CONTA_POUPANCA = 2
};


clientes pegaCadastro(int num_clientes)
{
    clientes cliente;
 
        cliente.saldo = 0;
        while (1)
        {
            printf("Insira seu nome completo, max(%i): ", MAX_NOME);
             int c; while ((c = getchar()) != '\n' && c != EOF);

            scanf(" %50[^\n]s", cliente.nome);
            if (strlen(cliente.nome) >= 50)
            {
                printf("Nome incorreto, max(%i)\n", MAX_NOME);
            }
            else
            {
                break;
            }
        }
        
            printf("Digite a sua idade, min(%i): ", MIN_IDADE);
            int c; while ((c = getchar()) != '\n' && c != EOF);
            scanf("%i", &cliente.idade); 

        while (1)
        {
            printf("Digite seu CPF, contendo sinais(pontos, traço): ");
            int c; while ((c = getchar()) != '\n' && c != EOF);
            
            scanf(" %14[^\n]s", cliente.CPF);
            if (strlen(cliente.CPF) < 14)
            {
                printf("Digite o CPF corretamente: max(%i)\n", MAX_CPF);
                
            }
            else
            {
                break;
            }
        }
        
        
        
   return cliente;
}

clientes segundoMenu(clientes cliente, int num_cliente)
{
   unsigned opcao;
   bool sair = false;
        while(!sair)
        {
        printf("Qual tipo de conta deseja abrir?\n");
        printf("1 - Conta corrente\n");
        printf("2 - Conta poupança\n");

        scanf("%u", &opcao);
                switch (opcao)
                {
                    case CONTA_CORRENTE:
                    cliente.conta_corrente = 1;
                    cliente.conta_poupanca = 0;
                    cliente.id_cliente = num_cliente + 1;
                    cliente.status = true;
                    sair = true;
                        break;
                    case CONTA_POUPANCA:
                    cliente.conta_poupanca = 1;
                    cliente.conta_corrente = 0;
                    cliente.id_cliente = num_cliente + 1;
                    cliente.status = true;
                    sair = true;
                        break;
                            
                    default:
                    printf("opção invalida!\n"); 
                
                        break;
                }
        
        }
        return cliente;   
}

void listarClientes(clientes cliente[], int num_clientes)
{
    for (int i = 0; i < num_clientes; i++)
    {
    
        if (cliente[i].conta_corrente == 1 && cliente[i].conta_poupanca == 0 && cliente[i].status == true)
        {
            printf("[%i] Nome: %s, CPF: %s, Idade:%i, Status: aberta, Tipo:Corrente, Saldo: %i\n", 
            cliente[i].id_cliente,cliente[i].nome, cliente[i].CPF, cliente[i].idade,cliente[i].saldo);
            
        }
        if (cliente[i].conta_corrente == 0 && cliente[i].conta_poupanca == 1 && cliente[i].status == true)
        {
           printf("[%i] Nome: %s, CPF: %s, Idade:%i, Status: aberta, Tipo:Poupanca, Saldo: %i\n", 
            cliente[i].id_cliente,cliente[i].nome, cliente[i].CPF, cliente[i].idade,cliente[i].saldo);

           
        }
        if (cliente[i].conta_corrente == 1 && cliente[i].conta_poupanca == 0 && cliente[i].status == false
        || cliente[i].conta_corrente == 0 && cliente[i].conta_poupanca == 1
        && cliente[i].status == false)
        {
            printf("[%i] Nome: %s, CPF: %s, Idade:%i, Status: Fechada, Saldo: %i\n",
            cliente[i].id_cliente,cliente[i].nome, cliente[i].CPF, cliente[i].idade,cliente[i].saldo);
        }
        
    
     
    }
          
}

bool pegaNumConta(clientes cliente[], int num_conta, int num_cliente)
{
    for (int i = 0; i < num_cliente; i++)
    {
        if(cliente[i].id_cliente == num_conta)
        {
            return true;
        }
    }
    return false;

}   

void alteraStatus(clientes cliente[], int num_conta, int num_cliente)
{  
    cliente[num_conta].status = false;
    printf("Conta fechada com sucesso!\n");
}

bool validaCpf(clientes cliente[], int num_clientes)
{
     for (int i = 0; i < num_clientes; i++)
    {
        for (int z = i + 1; z < num_clientes; z++)
        {
            if (strcmp(cliente[i].CPF, cliente[z].CPF) == 0)
            {
                printf("Cliente já cadastrado\n");
                return false;
            }
        }
    }
    return true;
}

int main()
{
    SetConsoleOutputCP(65001);
    clientes clientes[MAX_CLIENTES];
    int num_clientes = 0;
    bool sair = false;
    int num_conta;
    int deposito = 0;
    int emprestimo = 0;
    int soma_saldo = 0;
    int quantEmprestimo = 0;
    printf("Bem vindo ao Sistema de Gestão de Contas correntes\n");
    
    while(!sair)
    {
        system(CLEAR);
        unsigned opcao;
        printf("Selecione uma das opções abaixo!\n");
        printf("1 - Para Abrir Sua Conta!\n");
        printf("2 - Para Listar Clientes!\n");
        printf("3 - Para Fazer Depósito!\n");
        printf("4 - Para Fazer Saque!\n");
        printf("5 - Para Fechar Conta!\n");
        printf("6 - Para Fazer Empréstimo!\n");
        printf("0 - Para Sair!\n");
        
        scanf("%i", &opcao); 
            switch (opcao)
            {
            case SAIR:
            sair = true;
                break;
            case CADASTRAR:
           //Cadastrar
            if (num_clientes >= MAX_CLIENTES)
            {
                printf("Base ja esta cheia\n");
            }
            else
            { 
                clientes[num_clientes] = segundoMenu(pegaCadastro(num_clientes) , num_clientes);
                num_clientes++;

                if(clientes[num_clientes - 1].idade < 18)
                {
                    printf("Cliente precisa ser maior de idade\n");
                    num_clientes--;
                }
              bool validaCPF = validaCpf(clientes, num_clientes);
                if (validaCPF == false)
                {
                    num_clientes--;
                }
                
            }
            
                break;
            case LISTAR:
            //listar
             if(num_clientes == 0)
            {
                printf("Não a clientes cadastrados\n");
                break;
            }
            listarClientes(clientes, num_clientes);
                break;
            case DEPOSITAR:
            //fazer deposito 
            if(num_clientes == 0)
            {
                printf("Não a clientes cadastrados\n");
                break;
            }

            printf("Informe o numero da conta: \n");
            scanf("%i", &num_conta);
            bool y;
            y = pegaNumConta(clientes, num_conta, num_clientes);
            if(y == true && clientes[num_conta - 1].status == true)
            {
                
                printf("Informe o valor a ser inserido: \n");
                scanf("%i", &deposito);
                if(deposito > 0)
                {               
                clientes[num_conta - 1].saldo += deposito;
                soma_saldo += clientes[num_conta - 1].saldo;
                printf("Saldo alterado com sucesso!\n");
                }
                else
                {
                    printf("Insira um valor valido\n");
                }
            }
            if(y == false)
            {
                printf("Conta não encontrada\n");
            }
            if(y == true && clientes[num_conta - 1].status == false)
            {
                printf("Conta esta fechada\n");
            }
               break;
            case SACAR:
            //fazer saque
            if(num_clientes == 0)
            {
                printf("Não a clientes cadastrados\n");
                break;
            }

            printf("Informe o numero da conta: \n");
            scanf("%i", &num_conta);
            
            y = pegaNumConta(clientes, num_conta, num_clientes);
            if(y == true && clientes[num_conta - 1].status == true)
            {
                printf("Informe o valor a ser retirado: \n");
                scanf("%i", &deposito);  
                if(deposito > 0)
                {
                if(clientes[num_conta - 1].saldo < deposito)
                {
                    printf("Saldo insuficiente\n");
                }
                else{
                clientes[num_conta - 1].saldo -= deposito;
                soma_saldo -= clientes[num_conta - 1].saldo;
                printf("Saldo alterado com sucesso!\n");
                }
                }
                else
                {
                    printf("Insira um valor valido\n");
                }
            }
            if(y == false)
            {
                printf("Conta não encontrada\n");
            }
            if(y == true && clientes[num_conta - 1].status == false)
            {
                printf("Conta esta fechada\n");
            }

                break;
            case FECHAR_CONTA:
            //fechar conta

             if(num_clientes == 0)
            {
                printf("Não a clientes cadastrados\n");
                break;
            }

            printf("Informe o numero da conta: \n");
            scanf("%i", &num_conta);
            
            y = pegaNumConta(clientes, num_conta, num_clientes);
            if(y == true)
            {
              if(clientes[num_conta - 1].saldo == 0)
              {
                alteraStatus(clientes, num_conta - 1, num_clientes);
              }
              else
              {
                printf("É necessário esvaziar a conta antes de fecha-la!\n");
              }
            }
            if(y == false)
            {
                printf("Conta não encontrada\n");
            }

                break;
            case EMPRESTAR:
            //fazer emprestimo
             if(num_clientes == 0)
            {
                printf("Não a clientes cadastrados\n");
                break;
            }

            printf("Informe o numero da conta: \n");
            scanf("%i", &num_conta);
            
            y = pegaNumConta(clientes, num_conta, num_clientes);
            if(y == false)
            {
                printf("Conta não encontrada\n");
            }
            if(y == true)
            {   
                if (clientes[num_conta - 1].saldo == 0)
                {
                    printf("Você precisa ter saldo para pedir um empréstimo!\n");
                }
               else
               { 
                    while(1)
                    {
                        printf("Informe o valor desejado: \n");
                        scanf("%i", &emprestimo);   
                        if (emprestimo >= clientes[num_conta - 1].saldo * 2)
                        {
                            printf("Valor maior que o seu limite!\n");
                            
                        }
                        if (emprestimo > soma_saldo * 0.2)
                        {
                            printf("Valor maior que o crédito disponível nesta agência\n");
                            break;
                        }                        
                        else if (emprestimo < clientes[num_conta - 1].saldo * 2)
                        {
                            clientes[num_conta - 1].saldo += emprestimo;
                            printf("Empréstimo efetuado!\n");
                            quantEmprestimo++;
                            break;
                        }
                        
                    }
                    printf("Empréstimos efetuados: %i\n", quantEmprestimo);
                }
            }
        
                break;
            default:
                printf("Opção invalida\n");
                break;
            }
     if(opcao != 0)
        {
            printf("Pressione ENTER para continuar...\n");
            fflush(stdin);
            char tecla;
            scanf("%c", &tecla);
            fflush(stdin);
        }

    }

return 0;
}