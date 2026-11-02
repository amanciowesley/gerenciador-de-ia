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
void mostrarMenuListar();
void enterParaContinuar();
void mostrarMenuListarID();
void mostrarMenuListarNome();
void buscarNome(char *nome_busca);
void exibirNome(char *nome);


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
    char nome_busca[TAM_NOME];

    do{
        mostrarMenu();
        opcao = escolhaMenu();

        switch (opcao){ 
            case 1:
                /*Cadastrar agente*/
                mostrarCadastrar();
                qtd_adicionada = lerAgente(id, nome_agente, script, nota, qtd_adicionada, &ultimoID);
                salvarAgentes(id, nome_agente, script, nota, qtd_adicionada, &ultimoID);
                enterParaContinuar();
                break;
            
            case 2:
                /* Listar todos os agentes*/
                mostrarMenuListar();
                exibirAgentes();
                enterParaContinuar();
                break;


                //mostrarSubMenu();
            
                //id_busca = buscarID();
                //exibirID(id_busca);
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
                
            case 3:
                /* Buscar pelo ID */
                mostrarCadastrar();
                id_busca = buscarID();
                exibirID(id_busca);
                enterParaContinuar();
                break;

            case 4:
                /* Buscar pelo nome */
                mostrarMenuListarNome();
                buscarNome(nome_busca); //altera a varial nome_busca através de um ponteiro
                exibirNome(nome_busca);
                enterParaContinuar();
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

    printf("Nome (evite espacos antes ou depois do nome): ");
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
    
    limparBuffer();
    id[qtd] = *ultimoID;
    (*ultimoID)++; //incrementa o valor apontado pelo ponteiro e não o endereço, logica auxiliada por chatgpt
    
    printf(">>>>> Agente cadastrado ID #%d <<<<<\n", id[qtd]);
    return qtd + 1;
}   

void salvarAgentes(int id[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], int qtd, int *ultimoID){
    /* 
    -> Resposavel por realizar o salvamento dos dados presentes nos vetores diretamente 
    em um arquivo .TXT
    -> fprintf(arquivo, "%d\n", qtd) e fprintf(arquivo, "%d\n", *ultimoID
    gravam as duas primeiras linhas do arquivo. Elas armazenam a quantidade de agentes
    cadastrados e o valor do ultimoID disponível que será atribuido a um agente mediante 
    um novo cadastro.
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
        //printf("Nenhum agente cadastrado!\n");
        *ultimoID = 1; //ID dos agentes inicia em 1
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
        printf("Nenhum agente cadastrado!\n");
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

        printf("ID: #%d\n", id);
        printf("Nome: %s\n", nome_agente);
        printf("Script: %s\n", script);
        printf("Nota: %.2f\n", nota);
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-==-=-=-=\n");
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
            printf("Digite um ID valido!\n");
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
    int i; //variavel de controle do laço for 

    //foi usado uma variavel i separado, pois há a necessidade acessar seu valor
    //na verificação if (i == qtd) que esta fora do escopo do for, caso o a gente não seja encontrado


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
            
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
            printf("ID: #%d\n", id);
            printf("Nome: %s\n", nome_agente);
            printf("Script: %s\n", script);
            printf("Nota: %.2f\n", nota);
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
            break;
        }else{
            //Mesmo quando não encontrado o resto dos dados do arquivo devem ser lidos
            fgets(nome_agente, TAM_NOME, arquivo);
            nome_agente[strcspn(nome_agente, "\n")] = '\0';

            fgets(script, TAM_SCRIPT, arquivo);
            script[strcspn(script, "\n")] = '\0';

            fscanf(arquivo, "%f", &nota);
            terminarLinha(arquivo);
        }
    }
    
    if (i == qtd){
        /*
        ->Somente se torna verdadeira, quando o i é incrementado até se igualar a
        quantidade cadastrada, isso indica que o laço não foi quebrado quando id 
        foi encontrado 
        */
        printf("Agente nao encontrado!\n");
    }
    fclose(arquivo);
}

void buscarNome(char *nome){
    /* 
    Ponteiro usado, pois não é possivel retornar uma string.
    */
    printf("Digite o nome do agente: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    paraMaiusculo(nome);
}

void exibirNome(char *nome){
    int id;
    char nome_agente[TAM_NOME];
    char script[TAM_SCRIPT];
    float nota;
    int qtd = 0;
    int ultimoID;

    FILE *arquivo = fopen("agentes.txt", "r");

    fscanf(arquivo, "%d", &qtd);
    fscanf(arquivo, "%d", &ultimoID);
    terminarLinha(arquivo);

    for (int i = 0; i < qtd; i++){
        fscanf(arquivo, "%d", &id);
        terminarLinha(arquivo);

        fgets(nome_agente, TAM_NOME, arquivo);
        nome_agente[strcspn(nome_agente, "\n")] = '\0';

        if (strcmp(nome_agente, nome) == 0){
            fgets(script, TAM_SCRIPT, arquivo);
            script[strcspn(script, "\n")] = '\0';

            fscanf(arquivo, "%f", &nota);
            terminarLinha(arquivo);
            
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
            printf("ID: #%d\n", id);
            printf("Nome: %s\n", nome_agente);
            printf("Script: %s\n", script);
            printf("Nota: %.2f\n", nota);
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
            break;
        }else{
            //Mesmo quando não encontrado o resto dos dados do arquivo devem ser lidos
            fgets(script, TAM_SCRIPT, arquivo);
            script[strcspn(script, "\n")] = '\0';

            fscanf(arquivo, "%f", &nota);
            terminarLinha(arquivo);
        }
    }

    if (strcmp(nome_agente, nome) != 0){
        printf("\nAgente nao encontrado!\n");
        printf("Talvez tenha cadastrado com espaco nas extremidades!\n");
    }

    fclose(arquivo);
}

// Apresentação e interação dos MENUs
void mostrarCadastrar(){
    /* 
    -> Titulo de submenu usado na tela de cadastrar agentes

    by: Wesley
    */
    limparTela();
    printf("=-=-=-=-=-=- CADASTRAR AGENTE =-=-=-=-=-=\n");
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

void mostrarMenu(){
    /* 
    -> Apresenta o menu principal

    by: wesley
    */
    //limparTela();
    printf("=-=-=-=-=-=-=-=-=-=-= AGENTEDEX -=-==-=-=-=-=-=-=\n");
    printf("1 - Cadastrar agente\n");
    printf("2 - Listar todos os agentes\n");
    printf("3 - Buscar pelo ID\n");
    printf("4 - Buscar pelo Nome\n");
    printf("0 - Sair\n");
}

void mostrarMenuListar(){
    limparTela();
    printf("=-=-=-=-=-=-= LISTAR TODOS OS AGENTES =-=-=-=-=-=\n");
}

void mostrarMenuListarID(){
    limparTela();
    printf("=-=-=-=-=-=-=-=-=- BUSCAR PELO ID -=-==-=-=-=-=-=\n");
}

void mostrarMenuListarNome(){
    limparTela();
    printf("=-=-=-=-=-=-=-=-= BUSCAR PELO NOME =-==-=-=-=-=-=\n");
}

// Funções de auxilio
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

void terminarLinha(FILE *arquivo){
    int c;
    while((c = fgetc(arquivo)) != '\n' && c != EOF);
}

void enterParaContinuar(){
    /* 
    -> Ao pressionar a teclar ENTER a tela é limpa e retornar o menu principal
    
    OBS: código do retirado do stackoverflow
    */
    printf("Pressione enter para continuar...\n");
    char enter = 0;
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
    limparTela();
}
