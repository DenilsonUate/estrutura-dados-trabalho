/*
 * SISTEMA DE REGISTO DE ESTUDANTES COM TABELA HASH
 * Elaborado por Denilson - Commit 1
 * Acrescentado por Ludovina - Commit 2 (Validacoes e Interface)
 * Acrescentado por Frederico - Commit 3 (Insercao no Menu)
 * Acrescentado por Denilson - Commit 4 (Insercao Encadeamento)
 * Acrescentado por Ludovina - Commit 5 (Insercao Linear)
 * Acrescentado por Frederico - Commit 6 (Exibicao das Tabelas)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 10          // Tamanho das tabelas hash
#define MAX_NOME 50     // Tamanho maximo para nome
#define MAX_CURSO 50    // Tamanho maximo para curso
#define MAX_STR 10      // Tamanho para strings de entrada

// ------------------------
// Estrutura do estudante
// ------------------------
// Elaborado por Denilson
typedef struct Estudante {
    int numero;                 // Numero do estudante (matricula)
    char nome[MAX_NOME];        // Nome completo
    char curso[MAX_CURSO];      // Curso
    struct Estudante* prox;     // Ponteiro para proximo (encadeamento)
} Estudante;

// ------------------------
// Tabelas Hash
// ------------------------
// Elaborado por Denilson
Estudante* tabelaEncadeamento[TAM];     // Tabela para encadeamento (lista ligada)
Estudante tabelaLinear[TAM];             // Tabela para sondagem linear (vetor)

// ------------------------
// Prototipos das funcoes
// ------------------------
// Elaborado por Denilson
void inicializarTabelas();
int funcaoHash(int numero);
void exibirMenuPrincipal();
void limparBuffer();
void pausar();

// ------------------------
// Prototipos adicionados por Ludovina
// ------------------------
// Acrescentado por Ludovina
int validarApenasDigitos(char str[]);
int validarApenasLetras(char str[]);
int validarCampoVazio(char str[]);
void lerString(char destino[], int tamanho, char mensagem[]);
void exibirSubMenu(char titulo[]);

// ------------------------
// Prototipos adicionados por Frederico
// ------------------------
// Acrescentado por Frederico
void inserirEstudante();
void lerDadosEstudante(int *numero, char nome[], char curso[]);

// ------------------------
// Prototipos adicionados por Denilson
// ------------------------
// Acrescentado por Denilson
void inserirEncadeamento(int numero, char nome[], char curso[]);
void exibirMensagemColisaoEncadeamento(int indice);

// ------------------------
// Prototipos adicionados por Ludovina (Commit 5)
// ------------------------
// Acrescentado por Ludovina
void inserirLinear(int numero, char nome[], char curso[]);
void exibirMensagemColisaoLinear(int indiceOcupado, int proximoIndice);

// ------------------------
// Prototipos adicionados por Frederico (Commit 6)
// ------------------------
// Acrescentado por Frederico
void exibirTabelaEncadeamento();
void exibirTabelaLinear();
void exibirTodasTabelas();
void desenharLinha(int tamanho);

// ------------------------
// Funcao main - Menu principal
// ------------------------
// Elaborado por Denilson
int main() {
    int opcao;
    
    // Inicializar as tabelas
    inicializarTabelas();
    
    printf("\n============================================\n");
    printf("   SISTEMA DE REGISTO DE ESTUDANTES\n");
    printf("   Com Tabela Hash (Encadeamento e Linear)\n");
    printf("============================================\n");
    printf("   Elaborado por Denilson (Commit 1)\n");
    printf("   Acrescentado por Ludovina (Commit 2)\n");
    printf("   Acrescentado por Frederico (Commit 3)\n");
    printf("   Acrescentado por Denilson (Commit 4)\n");
    printf("   Acrescentado por Ludovina (Commit 5)\n");
    printf("   Acrescentado por Frederico (Commit 6)\n");
    printf("============================================\n\n");
    
    do {
        exibirMenuPrincipal();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                printf("\n--- INSERIR ESTUDANTE ---\n");
                inserirEstudante();
                break;
                
            case 2:
                printf("\n--- PROCURAR ESTUDANTE ---\n");
                printf("Funcionalidade em desenvolvimento...\n");
                pausar();
                break;
                
            case 3:
                printf("\n--- REMOVER ESTUDANTE ---\n");
                printf("Funcionalidade em desenvolvimento...\n");
                pausar();
                break;
                
            case 0:
                printf("\nSaindo do sistema...\n");
                printf("Obrigado por utilizar!\n");
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                pausar();
        }
        
    } while(opcao != 0);
    
    return 0;
}

// ------------------------
// Inserir estudante (sem escolha de metodo)
// ------------------------
// Acrescentado por Frederico (modificado por Ludovina)
void inserirEstudante() {
    int numero;
    char nome[MAX_NOME];
    char curso[MAX_CURSO];
    
    // Ler dados do estudante
    lerDadosEstudante(&numero, nome, curso);
    
    // Inserir automaticamente nas duas tabelas
    printf("\n--- Inserindo nas tabelas ---\n");
    inserirEncadeamento(numero, nome, curso);
    inserirLinear(numero, nome, curso);
    
    // Mostrar como ficaram as tabelas apos insercao
    printf("\n--- Estado atual das tabelas ---\n");
    exibirTodasTabelas();
    
    pausar();
}

// ------------------------
// Inserir estudante na tabela de encadeamento
// ------------------------
// Acrescentado por Denilson
void inserirEncadeamento(int numero, char nome[], char curso[]) {
    int indice = funcaoHash(numero);
    Estudante* novo = (Estudante*)malloc(sizeof(Estudante));
    
    // Preencher dados do novo estudante
    novo->numero = numero;
    strcpy(novo->nome, nome);
    strcpy(novo->curso, curso);
    novo->prox = NULL;
    
    printf("\n[ENCADEAMENTO] Numero: %d\n", numero);
    printf("Indice calculado: %d\n", indice);
    
    // Verificar se o indice esta vazio
    if(tabelaEncadeamento[indice] == NULL) {
        // Indice vazio - insercao direta
        tabelaEncadeamento[indice] = novo;
        printf("Indice %d: vazio - inserido com sucesso!\n", indice);
    } else {
        // Indice ocupado - tratar colisao com lista locada
        exibirMensagemColisaoEncadeamento(indice);
        
        Estudante* temp = tabelaEncadeamento[indice];
        while(temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novo;
        
        printf("Estudante alocado no final da lista do indice %d.\n", indice);
    }
}

// ------------------------
// Exibir mensagem de colisao para encadeamento
// ------------------------
// Acrescentado por Denilson
void exibirMensagemColisaoEncadeamento(int indice) {
    printf("\n!!! COLISAO DETECTADA !!!\n");
    printf("Indice %d ja esta ocupado.\n", indice);
    printf("Como e uma tabela com encadeamento (lista locada),\n");
    printf("o estudante sera alocado no final da lista existente.\n");
    printf("----------------------------------------\n");
}

// ------------------------
// Inserir estudante na tabela de sondagem linear
// ------------------------
// Acrescentado por Ludovina
void inserirLinear(int numero, char nome[], char curso[]) {
    int indiceOriginal = funcaoHash(numero);
    int indice = indiceOriginal;
    int tentativas = 0;
    
    printf("\n[LINEAR] Numero: %d\n", numero);
    printf("Indice calculado: %d\n", indiceOriginal);
    
    // Procurar posicao vazia (sondagem linear)
    while(tabelaLinear[indice].numero != -1 && tentativas < TAM) {
        tentativas++;
        exibirMensagemColisaoLinear(indice, (indice + 1) % TAM);
        indice = (indice + 1) % TAM;
        
        if(indice == indiceOriginal) {
            printf("\n!!! TABELA CHEIA !!!\n");
            printf("Nao foi possivel inserir o estudante na tabela linear.\n");
            return;
        }
    }
    
    // Inserir na posicao encontrada
    tabelaLinear[indice].numero = numero;
    strcpy(tabelaLinear[indice].nome, nome);
    strcpy(tabelaLinear[indice].curso, curso);
    tabelaLinear[indice].prox = NULL;
    
    if(indice == indiceOriginal) {
        printf("Indice %d: vazio - inserido com sucesso!\n", indice);
    } else {
        printf("Estudante inserido no indice %d (apos sondagem).\n", indice);
    }
}

// ------------------------
// Exibir mensagem de colisao para sondagem linear
// ------------------------
// Acrescentado por Ludovina
void exibirMensagemColisaoLinear(int indiceOcupado, int proximoIndice) {
    printf("\n!!! COLISAO DETECTADA !!!\n");
    printf("Indice %d ocupado, apliquei no indice %d (sondagem linear).\n", 
           indiceOcupado, proximoIndice);
    printf("----------------------------------------\n");
}

// ------------------------
// Exibir tabela de encadeamento
// ------------------------
// Acrescentado por Frederico
void exibirTabelaEncadeamento() {
    printf("\n=== TABELA HASH - ENCADEAMENTO ===\n");
    printf("Indice | Status | Alunos\n");
    desenharLinha(40);
    
    for(int i = 0; i < TAM; i++) {
        printf("%3d    | ", i);
        
        if(tabelaEncadeamento[i] == NULL) {
            printf("Vazio   | (nenhum aluno)\n");
        } else {
            printf("Ocupado | ");
            Estudante* temp = tabelaEncadeamento[i];
            int cont = 1;
            
            while(temp != NULL) {
                if(cont > 1) printf("         |         ");
                printf("%d: %s (%s)\n", temp->numero, temp->nome, temp->curso);
                temp = temp->prox;
                cont++;
            }
        }
        desenharLinha(40);
    }
}

// ------------------------
// Exibir tabela de sondagem linear
// ------------------------
// Acrescentado por Frederico
void exibirTabelaLinear() {
    printf("\n=== TABELA HASH - SONDAGEM LINEAR ===\n");
    printf("Indice | Status   | Aluno\n");
    desenharLinha(40);
    
    for(int i = 0; i < TAM; i++) {
        printf("%3d    | ", i);
        
        if(tabelaLinear[i].numero == -1) {
            printf("Vazio     | (nenhum aluno)\n");
        } else {
            printf("Ocupado   | %d: %s (%s)\n", 
                   tabelaLinear[i].numero, 
                   tabelaLinear[i].nome, 
                   tabelaLinear[i].curso);
        }
        desenharLinha(40);
    }
}

// ------------------------
// Exibir todas as tabelas
// ------------------------
// Acrescentado por Frederico
void exibirTodasTabelas() {
    exibirTabelaEncadeamento();
    exibirTabelaLinear();
}

// ------------------------
// Desenhar linha separadora
// ------------------------
// Acrescentado por Frederico
void desenharLinha(int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        printf("-");
    }
    printf("\n");
}

// ------------------------
// Ler dados do estudante com validacoes
// ------------------------
// Acrescentado por Frederico
void lerDadosEstudante(int *numero, char nome[], char curso[]) {
    char numStr[MAX_STR];
    int valido;
    
    printf("\n--- Dados do Estudante ---\n");
    
    // Ler numero (apenas digitos)
    do {
        lerString(numStr, MAX_STR, "Numero do estudante (apenas digitos): ");
        valido = 1;
        
        if(validarCampoVazio(numStr)) {
            printf("Erro: Campo vazio! Digite novamente.\n");
            valido = 0;
        }
        else if(!validarApenasDigitos(numStr)) {
            printf("Erro: Apenas numeros sao permitidos!\n");
            valido = 0;
        }
        
    } while(!valido);
    
    *numero = atoi(numStr);
    
    // Ler nome (apenas letras e espacos)
    do {
        lerString(nome, MAX_NOME, "Nome do estudante (apenas letras): ");
        valido = 1;
        
        if(validarCampoVazio(nome)) {
            printf("Erro: Campo vazio! Digite novamente.\n");
            valido = 0;
        }
        else if(!validarApenasLetras(nome)) {
            printf("Erro: Apenas letras e espacos sao permitidos!\n");
            valido = 0;
        }
        
    } while(!valido);
    
    // Ler curso (apenas letras e espacos)
    do {
        lerString(curso, MAX_CURSO, "Curso do estudante (apenas letras): ");
        valido = 1;
        
        if(validarCampoVazio(curso)) {
            printf("Erro: Campo vazio! Digite novamente.\n");
            valido = 0;
        }
        else if(!validarApenasLetras(curso)) {
            printf("Erro: Apenas letras e espacos sao permitidos!\n");
            valido = 0;
        }
        
    } while(!valido);
    
    printf("\nDados validados com sucesso!\n");
}

// ------------------------
// Inicializar as tabelas hash
// ------------------------
// Elaborado por Denilson
void inicializarTabelas() {
    // Inicializar tabela de encadeamento (todos ponteiros NULL)
    for(int i = 0; i < TAM; i++) {
        tabelaEncadeamento[i] = NULL;
    }
    
    // Inicializar tabela de sondagem linear (numero = -1 indica vazio)
    for(int i = 0; i < TAM; i++) {
        tabelaLinear[i].numero = -1;
        strcpy(tabelaLinear[i].nome, "");
        strcpy(tabelaLinear[i].curso, "");
        tabelaLinear[i].prox = NULL;
    }
    
    printf("Tabelas hash inicializadas com sucesso!\n");
}

// ------------------------
// Funcao hash (resto da divisao)
// ------------------------
// Elaborado por Denilson
int funcaoHash(int numero) {
    return numero % TAM;
}

// ------------------------
// Exibir menu principal
// ------------------------
// Elaborado por Denilson
void exibirMenuPrincipal() {
    printf("\n--------------------------------------------\n");
    printf("MENU PRINCIPAL\n");
    printf("--------------------------------------------\n");
    printf("1 - Inserir Estudante\n");
    printf("2 - Procurar Estudante\n");
    printf("3 - Remover Estudante\n");
    printf("0 - Sair\n");
    printf("--------------------------------------------\n");
}

// ------------------------
// Exibir submenu (adicionado por Ludovina)
// ------------------------
// Acrescentado por Ludovina
void exibirSubMenu(char titulo[]) {
    printf("\n--------------------------------------------\n");
    printf("%s\n", titulo);
    printf("--------------------------------------------\n");
    printf("1 - Encadeamento (Lista Locada)\n");
    printf("2 - Sondagem Linear\n");
    printf("0 - Voltar\n");
    printf("--------------------------------------------\n");
    printf("Escolha: ");
}

// ------------------------
// Validar se string contem apenas digitos
// ------------------------
// Acrescentado por Ludovina
int validarApenasDigitos(char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(!isdigit(str[i])) {
            return 0;  // Nao e digito
        }
    }
    return 1;  // Sao apenas digitos
}

// ------------------------
// Validar se string contem apenas letras e espacos
// ------------------------
// Acrescentado por Ludovina
int validarApenasLetras(char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(!isalpha(str[i]) && str[i] != ' ') {
            return 0;  // Nao e letra nem espaco
        }
    }
    return 1;  // Sao apenas letras e espacos
}

// ------------------------
// Validar se campo nao esta vazio
// ------------------------
// Acrescentado por Ludovina
int validarCampoVazio(char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] != ' ' && str[i] != '\n' && str[i] != '\t') {
            return 0;  // Tem caracteres nao vazios
        }
    }
    return 1;  // Esta vazio
}

// ------------------------
// Ler string com validacao simples
// ------------------------
// Acrescentado por Ludovina
void lerString(char destino[], int tamanho, char mensagem[]) {
    printf("%s", mensagem);
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = 0;  // Remover o \n
}

// ------------------------
// Limpar buffer do teclado
// ------------------------
// Elaborado por Denilson
void limparBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// ------------------------
// Pausar execucao
// ------------------------
// Elaborado por Denilson
void pausar() {
    printf("\nPressione Enter para continuar...");
    limparBuffer();
    getchar();
}
