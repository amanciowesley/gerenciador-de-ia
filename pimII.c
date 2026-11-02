/* 
Gerenciador de cadastro e edição de agentes de ia
*/

#include <stdio.h>
#include <stdlib.h> // biblioteca usada para usar a funcao de limpar tela
#include <windows.h> // biblioteca usada para usar a função sleep na linha
#include <ctype.h> // biblioteca usada para usar a função toupper

#define QTD_MAX 50
#define TAM_NOME 80
#define TAM_SCRIPT 1000
#define TAM_CATEGORIA 80

void mostrarMenu();
void limparTela();
void limparBuffer();
int escolhaMenu();
void mostrarSubMenu();
int escolhaSubMenu();
int lerAgente(int id[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], int qtd, int *ultimoID);
void exibirAgentes();
void paraMaiusculo(char *texto);
void mostrarCadastrar();
void terminarLinha(FILE *arquivo);
int carregarAgentes(int id[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], int max, int *ultimoID);
void salvarAgentes(int id[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], int qtd, int *ultimoID);
void exibirID(int id_de_busca);
int buscarID();


int main(){
    int opcao, op;
    int id[QTD_MAX];
    char nome_agente[QTD_MAX][TAM_NOME];
    char script[QTD_MAX][TAM_SCRIPT];
    float nota[QTD_MAX];
    char categoria[QTD_MAX][TAM_CATEGORIA];
    int ultimoID;
    int qtd_adicionada = carregarAgentes(id, nome_agente, script, nota, QTD_MAX, &ultimoID);
    int id_busca;

    do{
        mostrarMenu();
        opcao = escolhaMenu();

        switch (opcao){ 
            case 1:
                /*Cadastrar agente*/
                mostrarCadastrar();
                qtd_adicionada = lerAgente(id, nome_agente, script, nota, qtd_adicionada, &ultimoID);
                
                
                salvarAgentes(id, nome_agente, script, nota, qtd_adicionada, &ultimoID);
                break;
            
            case 2:
                /* Buscar agentes */
                mostrarSubMenu();
                id_busca = buscarID();
                exibirID(id_busca);
                /* exibirAgentes();
                op = escolhaSubMenu();
                switch (op){
                    case 1:
                        printf("Agente ADM IA\n");
                        Sleep(1500);
                        break;
                    case 2:
                        printf("Agente Producao IA\n");
                        Sleep(1500);
                        break;
                    case 3:
                        printf("Agente Cliente IA\n");
                        Sleep(1500);
                        break;
                    case 0:
                        break;
                    
                    default: 
                        printf("Opcao invalida\n");
                        Sleep(1500);
                } */
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
    //limparTela();
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

void mostrarSubMenu(){
    /*
    Menu das Categorias, feito com base no Menu principal
    by: Tony
    */
    limparTela();
    printf("=-=-=-= BUSCAR AGENTES NAS CATEGORIAS =-=-=-=\n");
    printf("1 - Administracao\n");
    printf("2 - Producao\n");
    printf("3 - Cliente\n");
    printf("0 - Voltar\n");
}

int escolhaSubMenu(){
    int opc;
    int resultado;

    do{
        printf("Opcao: ");
        resultado = scanf("%d", &opc);

        if (resultado != 1){
            printf("Opcao invalida\n");
            limparBuffer();
            Sleep(1000);
            mostrarSubMenu();
        }
    } while (resultado != 1);

    limparBuffer();
    return opc;
}

int lerAgente(int id[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], int qtd, int *ultimoID){
    /*
    Responsável por cadastrar um novo agente, lendo seu nome, script e nota diretamente do input do user
    -> O parâmetro qtd representa a quantidade atual de agentes cadastrados e indica a próxima posição disponível nos vetores
    -> O vetor id[] armazena o identificador único de cada agente, no caso o ID
    -> O ponteiro ultimoID permite acessar e incrementar o próximo ID disponível diretamente na variável original do main
    -> O ID é atribuído ao agente antes de incrementar ultimoID, garantindo que cada novo agente receba um identificador sequencial 
    sem reutilizar IDs anteriores quando algum agente é apagado
    -> A função retorna qtd + 1, atualizando a quantidade total de agentes cadastrados

    by: Wesley
*/
    int resultado;

    printf("Nome: ");
    fgets(nome_agente[qtd], TAM_NOME, stdin);
    nome_agente[qtd][strcspn(nome_agente[qtd], "\n")] = '\0';
    paraMaiusculo(nome_agente[qtd]);

    printf("Script: ");
    fgets(script[qtd], TAM_SCRIPT, stdin);
    script[qtd][strcspn(script[qtd], "\n")] = '\0';


    do{
        printf("Nota: ");
        resultado = scanf("%f", &nota[qtd]);

        if(resultado != 1 || nota[qtd] < 0 || nota[qtd] > 5){
            printf("Digite uma nota valida!\n");
            limparBuffer();
        }
    }while(resultado != 1 || nota[qtd] < 0 || nota[qtd] >  5);

    id[qtd] = *ultimoID;
    (*ultimoID)++; //incrementa o valor apontado pelo ponteiro e não o endereço, logica auxiliada por chatgpt
    return qtd + 1;
}   


void salvarAgentes(int id[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], int qtd, int *ultimoID){
    /* 
    -> Resposavel por realizar o salvamento dos dados presentes nos vetores diretamente 
    em um arquivo .TXT
    
    */
    
    //Arquivos abertos como w não necessitam do fgetc entre um scanf e um gets, pois tal recurso é usado apenas na leitura.
    FILE *arquivo = fopen("agentes.txt", "w");

    //Devolve NULL se não conseguir abrir, é checado senão o programa trava ao escrever
    if (arquivo == NULL){
        printf("Erro ao abrir arquivo\n");
        return;
    }

    //Primeira linha: quantos agentes existem
    fprintf(arquivo, "%d\n", qtd);
    fprintf(arquivo, "%d\n", *ultimoID);

    for (int i = 0; i < qtd; i++){
        //fprintf(arquivo, "%d\n", id[i]);
        fprintf(arquivo, "%d\n", id[i]);
        fprintf(arquivo, "%s\n", nome_agente[i]);
        fprintf(arquivo, "%s\n", script[i]);
        fprintf(arquivo, "%.1f\n", nota[i]);
        }

    fclose(arquivo);

}

int carregarAgentes(int id[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], int max, int *ultimoID){
    int qtd = 0; 

    FILE *arquivo = fopen("agentes.txt", "r");

    if (arquivo == NULL){
        printf("Nenhum agente cadastrado!\n");
        *ultimoID = 1;
        return 0;
    }

    //Lê a quantidade de agentes cadastrados (informação presente na primeira linha) 
    //e define no for até onde deve percorrer
    fscanf(arquivo, "%d", &qtd);
    fscanf(arquivo, "%d", ultimoID);
    terminarLinha(arquivo);

    /* fscanf(arquivo, "%d", &ultimoID);
    terminarLinha(arquivo); */

    for (int i = 0; i < qtd; i++){
        fscanf(arquivo, "%d", &id[i]);
        terminarLinha(arquivo);
        
        fgets(nome_agente[i], TAM_NOME, arquivo);
        nome_agente[i][strcspn(nome_agente[i], "\n")] = '\0';

        fgets(script[i], TAM_SCRIPT, arquivo);
        script[i][strcspn(script[i], "\n")] = '\0';

        fscanf(arquivo, "%f", &nota[i]);
        terminarLinha(arquivo);
    }

    fclose(arquivo);
    return qtd;
}

void exibirAgentes(){
    /*
    Vincular no txt
    by: Wesley
    */

    int id;
    char nome_agente[TAM_NOME];
    char script[TAM_SCRIPT];
    float nota;
    int qtd = 0;
    int ultimoID;

    FILE *arquivo = fopen("agentes.txt", "r");

    if (arquivo == NULL){
        printf("Nenhum agente cadastrado");
        return;
    }

    fscanf(arquivo, "%d", &qtd);
    fscanf(arquivo, "%d", &ultimoID);
    terminarLinha(arquivo);

    for (int i = 0; i < qtd; i++){
        fscanf(arquivo, "%d", &id);
        terminarLinha(arquivo);

        fgets(nome_agente, TAM_NOME, arquivo);
        nome_agente[strcspn(nome_agente, "\n")] = '\0';

        fgets(script, TAM_SCRIPT, arquivo);
        script[strcspn(script, "\n")] = '\0';

        fscanf(arquivo, "%f", &nota);
        terminarLinha(arquivo);

        printf("ID: %d\n", id);
        printf("Nome: %s\n", nome_agente);
        printf("Script: %s\n", script);
        printf("Nota: %.2f\n", nota);
        printf("===========================\n");
    }

    fclose(arquivo);

}

int buscarID(){
    int id;
    int resultado;

    do{
        printf("ID de busca: ");
        resultado = scanf("%d", &id);

        if (resultado != 1){
            printf("Digite um ID válido!\n");
            limparBuffer();
        }

    }while(resultado != 1);

    limparBuffer();
    return id;
}

void exibirID(int id_de_busca){
    FILE *arquivo = fopen("agentes.txt", "r");

    int id;
    char nome_agente[TAM_NOME];
    char script[TAM_SCRIPT];
    float nota;
    int qtd = 0;
    int ultimoID;
    int i;

    fscanf(arquivo, "%d", &qtd);
    fscanf(arquivo, "%d", &ultimoID);
    terminarLinha(arquivo);

    for (i = 0; i < qtd; i++){
            fscanf(arquivo, "%d", &id);
            terminarLinha(arquivo);

        if (id == id_de_busca){
            fgets(nome_agente, TAM_NOME, arquivo);
            nome_agente[strcspn(nome_agente, "\n")] = '\0';

            fgets(script, TAM_SCRIPT, arquivo);
            script[strcspn(script, "\n")] = '\0';

            fscanf(arquivo, "%f", &nota);
            terminarLinha(arquivo);

            printf("ID: %d\n", id);
            printf("Nome: %s\n", nome_agente);
            printf("Script: %s\n", script);
            printf("Nota: %.2f\n", nota);
            printf("===========================\n");
            break;
        }else{
            fgets(nome_agente, TAM_NOME, arquivo);
            nome_agente[strcspn(nome_agente, "\n")] = '\0';

            fgets(script, TAM_SCRIPT, arquivo);
            script[strcspn(script, "\n")] = '\0';

            fscanf(arquivo, "%f", &nota);
            terminarLinha(arquivo);
        }
    }
    
    if (i == qtd){
        printf("Agente nao encontrado!\n");
    }

}

void paraMaiusculo(char *texto){
    /* 
    -> Recebe um ponteiro como parâmetro, pois pega o texto digitado (nome) e 
    altera diretamente para maiusculo, sem necessidade de retorno.

    by: Wesley.
    */
    for(int i = 0; texto[i] != '\0'; i++){
        texto[i] = toupper((unsigned char) texto[i]);
    }
}

void mostrarCadastrar(){
    /* 
    -> Titulo de submenu usado na tela de cadastrar agentes

    by: Wesley
    */
    //limparTela();
    printf("=-=-=-=-=-=- CADASTRAR AGENTE =-=-=-=-=-=\n");
}

void terminarLinha(FILE *arquivo){
    int c;
    while((c = fgetc(arquivo)) != '\n' && c != EOF);
}
