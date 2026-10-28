/* 
Gerenciador de cadastro e edição de agentes de ia
*/

#include <stdio.h>
#include <stdlib.h> // biblioteca usada para usar a funcao de limpar tela
#include <windows.h> // biblioteca usada para usar a função sleep na linha

#define QTD_MAX 50
#define TAM_NOME 80
#define TAM_SCRIPT 1000
#define TAM_CATEGORIA 80
#define QTD_NOTAS 1 

void mostrarMenu();
void limparTela();
void limparBuffer();
int escolhaMenu();

int main(){
    int opcao;
    char nome_agente[QTD_MAX][TAM_NOME];
    char script[QTD_MAX][TAM_SCRIPT];
    float nota[QTD_MAX][QTD_NOTAS];
    char categoria[QTD_MAX][TAM_CATEGORIA];

    do{
        mostrarMenu();
        opcao = escolhaMenu();
        
        switch (opcao){ 
            case 1:
                /*Cadastrar agente*/
                printf("Opcao 1\n");
                break;
            
            case 2:
                /* Buscar agentes */
                printf("Opcao 2\n");
                break;
                
            case 3:
                /* Cadastrar categoria */
                printf("Opcao 3\n");
                break;

            case 4:
                /* Listar categorias */
                printf("Opcao 4\n");
                break;
            
            case 0:
                printf("Encerrando...");
                limparBuffer();
                break;

            default:
                continue;
            }
    }while (opcao != 0);

    return 0;
}

void cadastrarAgentes(char nome[][TAM_NOME], char instrucao[][TAM_SCRIPT], 
    float nota[][QTD_NOTAS], int qtd){
    
    
}

int escolhaMenu(){
    /* 
    -> Recebe o input do usuario no menu principal
    -> Caso o dado digitado seja diferente inteiro, uma nova solicitação ocorre
    -> É retornado no fim da função a opção digitada pelo usuario.

    by: Wesley
    */
    int opc;
    int resultado;
    
    do{
        printf("Opcao: ");
        resultado = scanf("%d", &opc);

        if (resultado != 1){
            printf("Opcao invalida\n");
            limparBuffer();
            Sleep(1000);
            limparTela();
            mostrarMenu();
        }else{}

    }while(resultado != 1);

    limparBuffer();
    return opc;
}

// Funções sem retorno
void mostrarMenu(){
    /* 
    -> Apresenta o menu principal

    by: wesley
    */
    limparTela();
    printf("=-=-=-=-=-=-= AGENTEDEX =-=-=-=-=-=-=\n");
    printf("1 - Cadastrar agente\n");
    printf("2 - Buscar agentes\n");
    printf("3 - Cadastrar categoria\n");
    printf("4 - Listar categorias\n");
    printf("0 - Sair\n");
}

void limparTela(){
    /* 
    -> Limpa o terminal
    -> O clear||cls permite que tal comando funcione tanto em windows quanto
    em OSs diferentes.

    by: wesley
    */
    system("clear||cls");
}

void limparBuffer(){
    /* 
    -> Limpa o buffer após entrada de dados

    by: wesley
    */
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}