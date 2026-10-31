#include <stdio.h>
#include <string.h>

#define TAM_TITULO 81
#define N_FILMES 20

int carregarFilmes(int cod[], int anos[], char nome[][TAM_TITULO], int max);
int salvarFilmes(int cod[], int anos[], char nome[][TAM_TITULO], int q); 
int cadastrarFilme(int cod[], int anos[], char nome[][TAM_TITULO], int q);
void listarFilmes(int cod[], int anos[], char nome[][TAM_TITULO], int q);
void exibirMenu();

void terminarLinha(FILE *arq);
void limparBuffer();


int main(){
	int codigos[N_FILMES], anosFilmes[N_FILMES];
	int qtd = 0, opt, c;
	char titulos[N_FILMES][TAM_TITULO];
	
	qtd = carregarFilmes(codigos, anosFilmes, titulos, N_FILMES);	
	
	do{
		exibirMenu();
		if (scanf("%d", &opt) != 1){
			limparBuffer();
			opt = 0;
		}
		
		switch (opt){
		
		case 1:
			if (qtd < N_FILMES){
				if (cadastrarFilme(codigos, anosFilmes, titulos, qtd) == 1){
					qtd++;
					printf("Cadastro Realizado!\n");
				} else {
					printf("Inconsistencia verificada. Cadastro nao realizado!\n");
				}
			} else {
				printf("Maximo de %d filmes atingido!\n", qtd);
			}
			break;
		case 2:
			if (qtd > 0){
				listarFilmes(codigos, anosFilmes, titulos, qtd);
			}
			else{
				printf("Nenhum filme cadastrado!\n");
			}
			break;
		case 3:
			if (salvarFilmes(codigos, anosFilmes, titulos, qtd) == 1){
				printf("Dados salvos!\n");
			} else {
				printf("Erro ao salvar os dados!\n");
			}
			break;
		case 4:
			printf("Saindo...");
			break;
		default:
			printf("Opcao invalida\n");
		
		}
		
	} while (opt != 4);
	return 0;	
}

void exibirMenu(){
	printf("\n===== CADASTRO DE FILMES =====\n");
	printf("1 - Cadastrar filme\n");
	printf("2 - Listar filmes\n");
	printf("3 - Salvar filmes\n");
	printf("4 - Sair\n");
	printf("Escolha uma opcao: ");
}

int carregarFilmes(int cod[], int anos[], char nome[][TAM_TITULO], int max){
	
	int q = 0;
	FILE *arquivo = fopen("filmes.txt", "r");
	if (arquivo == NULL) return 0; //arquivo nao existe (sem nenhum filme cadastrado)
	
	while(q<max && fscanf(arquivo, "%d", &cod[q]) == 1){
		terminarLinha(arquivo);
		if (fgets(nome[q], TAM_TITULO, arquivo) == NULL)
            break;
		nome[q][strcspn(nome[q], "\n")] = '\0';
		if (fscanf(arquivo, "%d", &anos[q]) != 1)
            break;
        terminarLinha(arquivo);
                
        q++;
	}
	fclose(arquivo);
	return q;
}

int cadastrarFilme(int cod[], int anos[], char nome[][TAM_TITULO], int q){
	
	printf("\nDigite o codigo do filme: ");
	if (scanf("%d", &cod[q]) != 1){
		limparBuffer();
		return 0;
	}
	limparBuffer();
	
	printf("Digite o titulo do filme: ");
	if (fgets(nome[q],TAM_TITULO,stdin) == NULL)
		return 0;
	
	printf("Digite o ano de lancamento: ");
	nome[q][strcspn(nome[q], "\n")] = '\0';
	if (scanf("%d", &anos[q]) != 1){
		limparBuffer();
		return 0;
	}	
	limparBuffer();
	return 1;		
}

void listarFilmes(int cod[], int anos[], char nome[][TAM_TITULO], int q){	
	for(int i = 0; i < q; i++){
		printf("\n-----------------------------------------------------------------\n");
		printf("Codigo: %d\nTitulo: %s\nAno de Lancamento: %d\n", cod[i], nome[i], anos[i]);
		printf("-----------------------------------------------------------------\n");
	}	
	
}

int salvarFilmes(int cod[], int anos[], char nome[][TAM_TITULO], int q){
	FILE *arquivo = fopen("filmes.txt", "w");
	if (arquivo == NULL) return 0; 
	
	for(int i = 0; i < q; i++){
		fprintf(arquivo, "%d\n%s\n%d\n", cod[i], nome[i], anos[i]);
	}
	fclose(arquivo);
	return 1;
}

void terminarLinha(FILE *arq) {
    int ch;
    while ((ch = fgetc(arq)) != '\n' && ch != EOF);
}

void limparBuffer(){
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
