/* 
Gerenciador de cadastro e edição de agentes de ia
*/

#include <stdio.h>
#include <stdlib.h> // biblioteca usada para usar a funcao de limpar tela
#include <windows.h> // biblioteca usada para usar a função sleep na linha
#include <ctype.h> // biblioteca usada para usar a função toupper
#include <string.h> // biblioteca usada para usar a função strcpy (string copy)

#define QTD_MAX 50
#define TAM_NOME 80
#define TAM_SCRIPT 1000

void mostrarMenu();
void limparTela();
void limparBuffer();
int escolhaMenu();
void mostrarExibirCategoria();
int escolhaSubMenu();
int lerAgente(int id[], char categorias[3][20], int categoria_agente[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], int qtd, int *ultimoID);
void exibirAgentes(int id[], int categoria_agente[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], char categorias[3][20], int qtd);
void paraMaiusculo(char *texto);
void mostrarCadastrar();
void terminarLinha(FILE *arquivo);
int carregarAgentes(int id[], int categoria_agente[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], int max, int *ultimoID);
void salvarAgentes(int id[], int categoria_agente[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], int qtd, int *ultimoID);
int exibirID(int id_de_busca, int id[], int categoria_agente[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], char categorias[3][20], int qtd);
int ehNumero();
void mostrarMenuListar();
void enterParaContinuar();
void mostrarMenuListarID();
void mostrarMenuListarNome();
void receberNomeDaBusca(char *nome_busca);
int exibirNome(char *nome, int id[], int categoria_agente[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], char categorias[3][20], int qtd);
int mostrarMenuEdicao();
void editarAgente(int id_busca, int categoria_agente[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], char categorias[3][20]);
int excluirAgente(int indice_agente, int id[], int categoria_agente[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], int qtd);
int escolherCategoria(char categoria[3][20]);
void exibirPorCategoria(int id[], int categoria_agente[], char nome_agente[][TAM_NOME], char script [][TAM_SCRIPT], float nota[], char categorias[3][20], int qtd);

void exibirTermo();
int verificarTermo();
int aceitarTermo();


int main(){
    int opcao_menu, opcao_edicao;
    char categorias[3][20] = {"ADMINISTRACAO", "PRODUCAO", "CLIENTE"};
    int id[QTD_MAX];
    int categoria_agente[QTD_MAX];
    char nome_agente[QTD_MAX][TAM_NOME];
    char script[QTD_MAX][TAM_SCRIPT];
    float nota[QTD_MAX];
    int ultimoID;
    int numeroDaBusca;
    int indice_agente;
    char nome_busca[TAM_NOME];
    int qtd_adicionada = carregarAgentes(id, categoria_agente, nome_agente, script, nota, QTD_MAX, &ultimoID);


    if (verificarTermo() == 0){
        printf("Termos nao aceitos!\n");
        printf("Encerrando...");
        return 0;
    }
    
    do{

        mostrarMenu();
        opcao_menu = escolhaMenu();

        switch (opcao_menu){ 
            case 1:
                /*Cadastrar agente*/
                mostrarCadastrar();
                qtd_adicionada = lerAgente(id, categorias, categoria_agente, nome_agente, script, nota, qtd_adicionada, &ultimoID);
                salvarAgentes(id, categoria_agente, nome_agente, script, nota, qtd_adicionada, &ultimoID);
                enterParaContinuar();
                break;
            
            case 2:
                /* Listar todos os agentes*/
                mostrarMenuListar();
                exibirAgentes(id, categoria_agente, nome_agente, script, nota, categorias, qtd_adicionada);
                enterParaContinuar();
                break;

            case 3:
                /* Buscar pelo ID */
                mostrarMenuListarID();
                numeroDaBusca = ehNumero();

                //variavel debaixo corresponde ao retorno do indice do vetor do agente buscado (alterar nome)
                indice_agente = exibirID(numeroDaBusca, id, categoria_agente, nome_agente, script, nota, categorias, qtd_adicionada); //variavel numeroDaBusca guarda o valor do id retornado de exibirID

                if (indice_agente != -1){
                    opcao_edicao = mostrarMenuEdicao();

                    if (opcao_edicao == 1){
                    editarAgente(indice_agente, categoria_agente, nome_agente, script, nota, categorias);
                    salvarAgentes(id, categoria_agente, nome_agente, script, nota, qtd_adicionada, &ultimoID);
                    printf("Alteracoes salvas!\n");
                    enterParaContinuar();

                    }else if(opcao_edicao == 2){
                        /* Excluir agente */
                        qtd_adicionada = excluirAgente(indice_agente, id, categoria_agente, nome_agente, script, nota, qtd_adicionada);
                        salvarAgentes(id, categoria_agente, nome_agente, script, nota, qtd_adicionada, &ultimoID);
                        printf("\n");
                        printf("Agente excluido com sucesso!\nAlteracoes salvas\n");
                        enterParaContinuar();
                    }else{
                        enterParaContinuar();
                    }
                }
                break;

            case 4:
                /* Buscar pelo nome */
                mostrarMenuListarNome();
                receberNomeDaBusca(nome_busca); //altera a variavel nome_busca através de um ponteiro
                indice_agente = exibirNome(nome_busca, id, categoria_agente, nome_agente, script, nota, categorias, qtd_adicionada); //variavel indice_agente guarda o valor do id retornado de exibirNome

                if (indice_agente != -1){
                    opcao_edicao = mostrarMenuEdicao();

                    if (opcao_edicao == 1){
                    editarAgente(indice_agente, categoria_agente, nome_agente, script, nota, categorias);
                    salvarAgentes(id, categoria_agente, nome_agente, script, nota, qtd_adicionada, &ultimoID);
                    printf("Alteracoes salvas!\n");
                    enterParaContinuar();

                    }else if(opcao_edicao == 2){
                        /* Excluir agente */
                        excluirAgente(indice_agente, id, categoria_agente, nome_agente, script, nota, qtd_adicionada);
                        salvarAgentes(id, categoria_agente, nome_agente, script, nota, qtd_adicionada, &ultimoID);
                        printf("\n");
                        printf("Agente excluido com sucesso!\nAlteracoes salvas\n");
                        enterParaContinuar();

                    }else{
                        enterParaContinuar();
                    }
                }

                break;

            case 5:
                mostrarExibirCategoria();
                exibirPorCategoria(id, categoria_agente, nome_agente, script, nota, categorias, qtd_adicionada);
                enterParaContinuar();
                break;
            
            case 0:
                printf("Encerrando...");
                limparBuffer();
                break;

            default:
                continue;
            }
    }while (opcao_menu != 0);

    return 0;
}


//Controle de agentes
int lerAgente(int id[], char categorias[3][20], int categoria_agente[], 
    char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], int qtd, int *ultimoID){
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
    
    printf("Escolha a categoria do seu agente\n");
    categoria_agente[qtd] = escolherCategoria(categorias);

    if (categoria_agente[qtd] == 3){
        return qtd;
    }


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

int escolherCategoria(char categoria[3][20]){
    /* 
    Reponsável por retornar a categoria escolhida pelo usuario.
    O parametro é uma matriz que contem as categorias ADMINISTRACAO (indice 0), PRODUCAO (indice 1) e CLIENTE (indice 2)
    A escolha é feita a partir dos números dps indices e não do conteudo char de cada posição do vetor, por isso um valor inteiro é retornado
    */
    int opcao;
    int resultado;

    printf("Categorias: \n");
    for (int i = 0; i < 3; i++){
        printf("%d - %s\n", i, categoria[i]);
    }
    printf("3 - Voltar ao menu\n");

    do {
        printf("Opcao: ");
        resultado = scanf("%d", &opcao);

        if (resultado != 1){
            printf("Digite um numero!\n");
            limparBuffer();
        }
        else if (opcao < 0 || opcao > 3){
            printf("Opcao invalida! Escolha entre 0 e 3.\n");
        }

    } while (resultado != 1 || opcao < 0 || opcao > 3);

    printf("\n");
    limparBuffer();
    return opcao;
}

void salvarAgentes(int id[], int categoria_agente[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], int qtd, int *ultimoID){
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
        printf("Agente não cadastrado\n");
        return;
    }

    //Primeira linha: quantos agentes existem
    fprintf(arquivo, "%d\n", qtd);
    fprintf(arquivo, "%d\n", *ultimoID);

    for (int i = 0; i < qtd; i++){
        fprintf(arquivo, "%d\n", id[i]);
        fprintf(arquivo, "%d\n", categoria_agente[i]);
        fprintf(arquivo, "%s\n", nome_agente[i]);
        fprintf(arquivo, "%s\n", script[i]);
        fprintf(arquivo, "%.1f\n", nota[i]);
        }

    fclose(arquivo);
}

int carregarAgentes(int id[], int categoria_agente[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], int max, int *ultimoID){
    /* 
    Responsável por carregar os agentes salvos no arquivo agente.txt ao inicar o programa novamente garantindo a recuperação dos dados
    */
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

    for (int i = 0; i < qtd; i++){
        fscanf(arquivo, "%d", &id[i]);

        fscanf(arquivo, "%d", &categoria_agente[i]);
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

void exibirAgentes(int id[], int categoria_agente[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], char categorias[3][20], int qtd){
    /*
    Função vinculada ao case 2: do menu principal. 
    Sua responsábilidade é apresentar os dados de TODOS os agentes cadastrados e apresentar a média de nota no final.
    Porém, a exibição só ocorre se a quantidade de agentes for diferente de 0, no caso se haver agentes cadastrados.
    */
    float soma;

    if (qtd != 0){
        for (int i = 0; i < qtd; i++){
            printf("ID: #%d\n", id[i]);
            printf("Categoria: %s\n", categorias[categoria_agente[i]]);
            printf("Nome: %s\n", nome_agente[i]);
            printf("Script: %s\n", script[i]);
            printf("Nota: %.2f\n", nota[i]);
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-==-=-=-=\n");
            soma += nota[i];
        }

    printf("Media de nota dos agentes: %.2f\n", soma / qtd);
    }else{
        printf("Nenhum agente cadastrado!\n");
        return;
    }
}

int ehNumero(){
    /* 
    Responsavel por retornar um número inteiro que será utilizado para que o usuario possa buscar os agentes por ID.
    Seu nome é ehNumero, pois ao receber a entrada do usuário ela verificar se o mesmo é um número inteiro.
    Enquanto não for a entrada é solicitada
    */
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

int exibirID(int id_de_busca, int id[], int categoria_agente[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], char categorias[3][20], int qtd){
    /* 
    Busca e apresenta as informações do agente desejado através do id
    */

    for (int i = 0; i < qtd; i++){

        if (id[i] == id_de_busca){

            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
            printf("ID: #%d\n", id[i]);
            printf("Categoria: %s\n", categorias[categoria_agente[i]]);
            printf("Nome: %s\n", nome_agente[i]);
            printf("Script: %s\n", script[i]);
            printf("Nota: %.2f\n", nota[i]);
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
            
            return i;
        }
    }
    printf("Agente nao encontrado!\n");
    return -1; // retorno de -1, pois este valor não correspondo a nenhuma posição dos vetores;
}

void receberNomeDaBusca(char *nome){
    /* 
    Entrada e tratamento (deixar todos os caracteres em letra maiuscula) do nome do agente que o usuario deseja buscar
    A função do ponteiro é acessar o endereço da variavel nome_busca na função main que é passado como parâmetro na função exibirNome.
    */
    printf("Digite o nome do agente: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';
    paraMaiusculo(nome);
}

int exibirNome(char *nome, int id[], int categoria_agente[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], char categorias[3][20], int qtd){
    /* 
    Busca e apresenta as informações do agente desejado através do Nome buscado pelo usuario
    Para que seja possivel a apresentação dos dados do agente pesquisado há a necessidade de fazer a comparação entre o nome pesquisado e o nome de cada agente
    cadastrado
    */

    for (int i = 0; i < qtd; i++){

        if (strcmp(nome, nome_agente[i]) == 0){
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
            printf("ID: #%d\n", id[i]);
            printf("Categoria: %s\n", categorias[categoria_agente[i]]);
            printf("Nome: %s\n", nome_agente[i]);
            printf("Script: %s\n", script[i]);
            printf("Nota: %.2f\n", nota[i]);
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
            return i; //retorna a o id caso o agente é encontrado

        }
    }   

    printf("\nAgente nao encontrado!\n");
    printf("Talvez tenha cadastrado com espaco nas extremidades!\n");

    return -1;
}

void editarAgente(int indice_agente, int categoria_agente[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], char categorias[3][20]){
    /* 
    Responsável por mostrar um menu de opção que permite editar e excluir o agente ou retornar ao menu principal.
    O agente que sofrerá alterações é acessado a partir do seu indice que é retornado pelas funções exibirNome e exibirID
    */
    int opcao;
    int resultado;
    

    printf("\n");
    printf("Deseja editar:\n");
    printf("1 - Categoria\n2 - Nome\n3 - Script\n4 - Nota\n");
    
    do{
        printf("Opcao: ");
        resultado = scanf("%d", &opcao);

        if (resultado != 1 || opcao < 1 || opcao > 4){
            printf("Digite uma opcao valida!\n");
            limparBuffer();
        }
    } while (resultado != 1 || opcao < 1 || opcao > 4);
    limparBuffer();

    switch (opcao){

        case 1: 
            printf("\n");
            printf("Escolha a nova categoria do seu agente\n");
            categoria_agente[indice_agente] = escolherCategoria(categorias);
            break;

        case 2:
            printf("Novo nome (evite espacos antes ou depois do nome): ");
            fgets(nome_agente[indice_agente], TAM_NOME, stdin);
            nome_agente[indice_agente][strcspn(nome_agente[indice_agente], "\n")] = '\0';
            paraMaiusculo(nome_agente[indice_agente]);
            break;
        
        case 3:
            printf("Novo Script: ");
            fgets(script[indice_agente], TAM_SCRIPT, stdin);
            script[indice_agente][strcspn(script[indice_agente], "\n")] = '\0';
            break;
        
        case 4:
            do{
                printf("Nova nota: ");
                resultado = scanf("%f", &nota[indice_agente]);

                if(resultado != 1 || nota[indice_agente] < 0 || nota[indice_agente] > 5){
                    printf("Digite uma nota valida!\n");
                    limparBuffer();
                }
            }while(resultado != 1 || nota[indice_agente] < 0 || nota[indice_agente] >  5);
            break;

        default:
            break;
    }
}

void exibirPorCategoria(int id[], int categoria_agente[], char nome_agente[][TAM_NOME], char script [][TAM_SCRIPT], float nota[], char categorias[3][20], int qtd){
    int opc;
    
    opc = escolherCategoria(categorias);

    for (int i = 0; i < qtd; i++){
        
        if (categoria_agente[i] == opc){
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-==-=-=-=\n");
            printf("ID: #%d\n", id[i]);
            printf("Categoria: %s\n", categorias[categoria_agente[i]]);
            printf("Nome: %s\n", nome_agente[i]);
            printf("Script: %s\n", script[i]);
            printf("Nota: %.2f\n", nota[i]);
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-==-=-=-=\n");
        }
    }
}

int excluirAgente(int indice_agente, int id[], int categoria_agente[], char nome_agente[][TAM_NOME], char script[][TAM_SCRIPT], float nota[], int qtd){
    /* 
    Na verdade não exclui, apenas desloca (sobrescreve) os dados uma posição para a esquerda.
    */

    for (int i = indice_agente; i < qtd - 1; i++ ){
        id[i] = id[i + 1];
        categoria_agente[i] = categoria_agente[i + 1];
        strcpy(nome_agente[i], nome_agente[i + 1]);
        strcpy(script[i], script[i + 1]);
        nota[i] = nota[i + 1];
    }   

    qtd--;
    return qtd;   
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

void mostrarExibirCategoria(){
    /*
    Menu das Categorias, feito com base no Menu principal
    by: Tony
    */
    limparTela();
    printf("=-=-=-=-= BUSCAR AGENTES NAS CATEGORIAS =-=-=-=-=\n");
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
    printf("5 - Buscar por categoria\n");
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

int mostrarMenuEdicao(){
    int opcao;
    int resultado;
    printf("Deseja:\n");
    printf("1 - Editar\n2 - Excluir\n0 - Retornar ao menu\n");

    do{
        printf("Opcao: ");
        resultado = scanf("%d", &opcao);

        if (resultado != 1 || opcao < 0 || opcao > 2){
            printf("Digite uma opcao valida!\n");
            limparBuffer();
        }
    } while (resultado != 1 || opcao < 0 || opcao > 2);
    
    limparBuffer();
    return opcao;
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

void exibirTermo(){
    printf("==================================================\n");
    printf("            TERMO DE CONDICOES DE USO\n");
    printf("==================================================\n\n");

    printf("1. OBJETO\n");
    printf("Este software permite cadastrar, consultar e gerenciar\n");
    printf("agentes de inteligencia artificial, informando nome,\n");
    printf("script e nota.\n\n");

    printf("2. RESPONSABILIDADE PELO CONTEUDO\n");
    printf("O usuario e o unico responsavel por todo conteudo que\n");
    printf("inserir no software (nome, script e nota).\n\n");

    printf("3. CONDUTAS PROIBIDAS\n");
    printf("E proibido cadastrar agentes cujo nome ou script:\n");
    printf("- tenham finalidade ilegal ou incentivem crimes;\n");
    printf("- violem direitos humanos, promovendo discriminacao,\n");
    printf("  odio, perseguicao ou violencia contra pessoas ou grupos;\n");
    printf("- promovam assedio, ameaca, difamacao ou fraude;\n");
    printf("- envolvam exploracao ou abuso de criancas e adolescentes;\n");
    printf("- violem direitos de terceiros, como privacidade e\n");
    printf("  propriedade intelectual.\n\n");

    printf("4. DECLARACAO DE CIENCIA\n");
    printf("Ao utilizar este software, o usuario declara que leu e\n");
    printf("compreendeu estas condicoes, esta ciente de que inserir\n");
    printf("conteudo ilegal ou que viole direitos humanos e proibido\n");
    printf("e assume as consequencias do conteudo que cadastrar,\n");
    printf("incluindo responsabilizacao civil, administrativa e\n");
    printf("penal, conforme a legislacao aplicavel.\n\n");

    printf("5. CONSEQUENCIAS\n");
    printf("Em caso de violacao, o conteudo infrator podera ser\n");
    printf("removido e as autoridades competentes poderao ser\n");
    printf("acionadas quando houver obrigacao legal.\n\n");

    printf("6. LIMITACAO DE RESPONSABILIDADE\n");
    printf("O software e oferecido \"como esta\". Os desenvolvedores\n");
    printf("nao respondem por danos decorrentes do conteudo inserido\n");
    printf("pelos usuarios.\n");
    printf("\n");
    printf("Digite\n[1] ACEITAR\n[0] RECUSAR\n");
    printf("==================================================\n");
    
}

int verificarTermo(){
/* --- Verifica se ja existe o arquivo agentes.txt, se ele ja existe quer dizer q o cliente ja aceitou o termo de uso.
*/  
    int opcao;
    FILE *arquivo = fopen("termo.txt", "r");

    if (arquivo != NULL){
        fclose(arquivo);
        return 1;
        }

    limparTela();
    exibirTermo();
    opcao = aceitarTermo();

    if (opcao == 1){
        arquivo = fopen("termo.txt", "w");
        fprintf(arquivo, "TERMO DE CONDICOES DE USO ACEITO.\n");
        fclose(arquivo);
        limparTela();
        return 1;
        }
    return 0;
}

int aceitarTermo(){

    int opcao;
    int resultado;

    do{
    printf("Opcao >>> ");
    resultado = scanf("%d", &opcao);
    limparBuffer();

    if (resultado != 1 || opcao < 0 || opcao > 1){
        printf("Opcao invalida\n");
    }

    } while (resultado != 1 || opcao < 0 || opcao > 1);

    return opcao;
}
