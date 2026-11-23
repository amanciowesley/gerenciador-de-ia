# AgenteDex

Gerenciador de cadastro e edição de **agentes de IA** feito em C, para rodar no terminal. Cada agente tem ID único, categoria, nome, script e nota, e os dados ficam salvos em arquivo de texto, então não se perdem ao fechar o programa.

> Projeto acadêmico (PIM) desenvolvido sem `struct`: todos os dados são armazenados em vetores e matrizes paralelos, e o acesso é feito pelo mesmo índice.

## Funcionalidades

- **Cadastrar** agente (categoria, nome, script e nota)
- **Listar todos** os agentes, com a média geral das notas
- **Buscar por ID** e, a partir do resultado, **editar** ou **excluir**
- **Buscar por nome** e, a partir do resultado, **editar** ou **excluir**
- **Buscar por categoria**, com a média de notas da categoria
- **Persistência** em arquivo `agentes.txt` (carrega ao abrir, salva a cada alteração)
- **Termo de condições de uso** exibido na primeira execução

## Categorias

| Código | Categoria      |
|:------:|----------------|
| 0      | ADMINISTRACAO  |
| 1      | PRODUCAO       |
| 2      | CLIENTE        |

## Requisitos

- Compilador C (por exemplo, [MinGW/GCC](https://www.mingw-w64.org/))
- **Windows**: o código usa `windows.h` (função `Sleep`)

> Para rodar em Linux/macOS, é preciso trocar `#include <windows.h>` e `Sleep(1000)` por `unistd.h` e `sleep(1)`.

## Como compilar e executar

```bash
gcc pimII.c -o pimII
./pimII        # no Windows: pimII.exe
```

Execute sempre a partir da mesma pasta, pois `agentes.txt` e `termo.txt` são criados no diretório de execução.

## Como usar

Na primeira execução o termo de uso é exibido. Digite `1` para aceitar ou `0` para recusar (o programa encerra). Ao aceitar, é criado o arquivo `termo.txt` e o termo não aparece mais.

Menu principal:

```
========================================
               AgenteDex
========================================
1 - Cadastrar agente
2 - Listar todos os agentes
3 - Buscar pelo ID
4 - Buscar pelo Nome
5 - Buscar por categoria
0 - Sair
```

Ao encontrar um agente nas buscas por ID ou nome, é possível **editar** (categoria, nome, script ou nota), **excluir** ou voltar ao menu.

## Regras e validações

| Campo     | Regra                                                         |
|-----------|---------------------------------------------------------------|
| Nome      | Obrigatório, até **80** caracteres; salvo em MAIÚSCULAS       |
| Script    | Obrigatório, até **1000** caracteres                          |
| Nota      | Número de **0 a 5** (aceita decimais)                         |
| Categoria | 0, 1 ou 2                                                     |
| Limite    | Até **50** agentes cadastrados                                |
| ID        | Sequencial a partir de 1; **não é reaproveitado** após exclusão |

Observações:

- A busca por nome é exata (ignora maiúsculas/minúsculas, mas não espaços nas extremidades).
- A edição de nome e script usa a mesma validação do cadastro.
- Entradas inválidas são rejeitadas e solicitadas novamente.

## Formato do `agentes.txt`

A primeira linha guarda a quantidade de agentes, a segunda o próximo ID disponível, e depois cada agente ocupa 5 linhas (ID, categoria, nome, script, nota):

```
2
3
1
0
ASSISTENTE DE RH
Responde duvidas sobre folha de pagamento e beneficios.
4.5
2
2
ATENDENTE VIRTUAL
Atende clientes no chat e encaminha chamados.
4.0
```

## Estrutura do projeto

```
.
├── pimII.c        # código-fonte completo
├── agentes.txt    # criado automaticamente ao cadastrar
├── termo.txt      # criado ao aceitar o termo de uso
└── README.md
```

## Conceitos praticados

- Vetores e matrizes paralelos no lugar de `struct`
- Passagem de parâmetros por ponteiro (`ultimoID`, `paraMaiusculo`, `receberNomeDaBusca`)
- Leitura e escrita de arquivos de texto (`fopen`, `fprintf`, `fscanf`, `fgets`)
- Validação de entrada com `scanf`, `fgets` e limpeza de buffer
- Modularização em funções

## Autores

- Wesley Alexandre dos Santos Amancio
- Antonio José Araujo
- Rafael Militão

## Licença

Projeto desenvolvido para fins educacionais. Defina aqui a licença desejada (por exemplo, MIT) antes de publicar.
