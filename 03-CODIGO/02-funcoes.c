/*
 * SISTEMA DE REGISTO DE ESTUDANTES COM TABELA HASH
 * Elaborado por Denilson - Commit 1
 * Acrescentado por Ludovina - Commit 2 (Validacoes e Interface)
 * Acrescentado por Frederico - Commit 3 (Insercao no Menu)
 * Acrescentado por Denilson - Commit 4 (Insercao Encadeamento)
 * Acrescentado por Ludovina - Commit 5 (Insercao Linear)
 * Acrescentado por Frederico - Commit 6 (Exibicao das Tabelas)
 * Acrescentado por Denilson - Commit 7 (Busca Interativa)
 * Acrescentado por Ludovina - Commit 8 (Persistencia em Arquivo)
 * Acrescentado por Frederico - Commit 9 (Remocao Interativa)
 * Acrescentado por Denilson - Commit 10 (Remocao Sincronizada)
 * Acrescentado por Denilson - Commit 11 (Normalizacao de Texto)
 * Acrescentado por Ludovina - Commit 12 (Validacao de Espacos)
 * Acrescentado por Denilson - Commit 13 (Correcao Buffer e Zero)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 10          // Tamanho das tabelas hash
#define MAX_NOME 50     // Tamanho maximo para nome
#define MAX_CURSO 50    // Tamanho maximo para curso
#define MAX_STR 20      // Tamanho para strings de entrada (AUMENTADO para numeros grandes)

// Nomes dos arquivos para persistencia
#define ARQ_ENCADEAMENTO "estudantes_encadeamento.txt"
#define ARQ_LINEAR "estudantes_linear.txt"

// ------------------------
// Estrutura do estudante (MODIFICADA para Commit 13)
// ------------------------
// Elaborado por Denilson (Modificado por Frederico - Commit 13)
typedef struct Estudante {
    char numeroStr[MAX_STR];    // NOVO: Numero como string (preserva zeros)
    int numero;                  // Numero do estudante (matricula) para hash
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
// Prototipos adicionados por Ludovina (Commit 2)
// ------------------------
// Acrescentado por Ludovina
int validarApenasDigitos(char str[]);
int validarApenasLetras(char str[]);
int validarCampoVazio(char str[]);
void lerString(char destino[], int tamanho, char mensagem[]);
void exibirSubMenu(char titulo[]);

// ------------------------
// Prototipos adicionados por Frederico (Commit 3) - MODIFICADO Commit 13
// ------------------------
// Acrescentado por Frederico (Modificado Commit 13)
void inserirEstudante();
void lerDadosEstudante(char numeroStr[], char nome[], char curso[]); // MODIFICADO

// ------------------------
// Prototipos adicionados por Denilson (Commit 4) - MODIFICADO Commit 13
// ------------------------
// Acrescentado por Denilson (Modificado Commit 13)
void inserirEncadeamento(char numeroStr[], int numero, char nome[], char curso[]);
void exibirMensagemColisaoEncadeamento(int indice);

// ------------------------
// Prototipos adicionados por Ludovina (Commit 5) - MODIFICADO Commit 13
// ------------------------
// Acrescentado por Ludovina (Modificado Commit 13)
void inserirLinear(char numeroStr[], int numero, char nome[], char curso[]);
void exibirMensagemColisaoLinear(int indiceOcupado, int proximoIndice);

// ------------------------
// Prototipos adicionados por Frederico (Commit 6) - MODIFICADO Commit 13
// ------------------------
// Acrescentado por Frederico (Modificado Commit 13)
void exibirTabelaEncadeamento();
void exibirTabelaLinear();
void exibirTodasTabelas();          // <-- PROTOTIPO
void desenharLinha(int tamanho);

// ------------------------
// Prototipos adicionados por Denilson (Commit 7) - MODIFICADO Commit 13
// ------------------------
// Acrescentado por Denilson (Modificado Commit 13)
void menuProcurar();
void procurarEncadeamento();
void procurarLinear();
void listarAlunosIndiceEncadeamento(int indice);
void mostrarAlunoIndiceLinear(int indice);

// ------------------------
// Prototipos adicionados por Denilson (Commit 8) - MODIFICADO Commit 13
// ------------------------
// Acrescentado por Denilson (Modificado Commit 13)
void salvarEncadeamento();
void salvarLinear();
void salvarTodasTabelas();          // <-- PROTOTIPO
void carregarEncadeamento();
void carregarLinear();
void carregarTodasTabelas();        // <-- PROTOTIPO

// ------------------------
// Prototipos adicionados por Frederico (Commit 9) - MODIFICADO Commit 13
// ------------------------
// Acrescentado por Frederico (Modificado Commit 13)
void menuRemover();
void removerEncadeamento();
void removerLinear();
int escolherAlunoIndiceEncadeamento(int indice);
void removerAlunoEncadeamento(int indice, int posicao);

// ------------------------
// Prototipos adicionados por Denilson (Commit 10) - MODIFICADO Commit 13
// ------------------------
// Acrescentado por Denilson (Modificado Commit 13)
void removerDeAmbasTabelas(char numeroStr[]);
void removerDaTabelaEncadeamento(char numeroStr[]);
void removerDaTabelaLinear(char numeroStr[]);
int encontrarIndiceLinearPorNumero(int numero);
int encontrarIndiceLinearPorNumeroStr(char numeroStr[]); // NOVO

// ------------------------
// Prototipos adicionados por Denilson (Commit 11)
// ------------------------
// Acrescentado por Denilson
void converterParaMinusculas(char str[]);
int verificarEstudanteDuplicado(int numero, char nome[], char curso[]);
int compararNomesIgnorandoMaiusculas(char str1[], char str2[]);
int compararCursosIgnorandoMaiusculas(char str1[], char str2[]);

// ------------------------
// Prototipos adicionados por Ludovina (Commit 12)
// ------------------------
// Acrescentado por Ludovina
int validarEspacos(char str[]);
int validarNomeCompleto(char str[]);
int validarCurso(char str[]);

// ------------------------
// NOVOS PROTOTIPOS - Commit 13 (Frederico)
// ------------------------
// Acrescentado por Frederico (Commit 13)
void limparBufferCompleto();
void converterParaInteiro(char numeroStr[], int *numero);
void exibirNumeroCompleto(char numeroStr[]);
int validarEntradaNumerica(char numeroStr[]);

// ------------------------
// Funcao main - Menu principal
// ------------------------
// Elaborado por Denilson
int main() {
    int opcao;
    
    // Inicializar as tabelas
    inicializarTabelas();
    
    // Carregar dados dos arquivos
    carregarTodasTabelas();          // <-- AGORA ENCONTRA
    
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
    printf("   Acrescentado por Denilson (Commit 7)\n");
    printf("   Acrescentado por Denilson (Commit 8)\n");
    printf("   Acrescentado por Frederico (Commit 9)\n");
    printf("   Acrescentado por Denilson (Commit 10)\n");
    printf("   Acrescentado por Denilson (Commit 11)\n");
    printf("   Acrescentado por Ludovina (Commit 12)\n");
    printf("   Acrescentado por Frederico (Commit 13 - Correcao Buffer e Zero)\n");
    printf("============================================\n\n");
    
    do {
        exibirMenuPrincipal();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferCompleto(); // Usando a nova funcao
        
        switch(opcao) {
            case 1:
                printf("\n--- INSERIR ESTUDANTE ---\n");
                inserirEstudante();
                salvarTodasTabelas();          // <-- AGORA ENCONTRA
                break;
                
            case 2:
                menuProcurar();
                break;
                
            case 3:
                menuRemover();
                salvarTodasTabelas();          // <-- AGORA ENCONTRA
                break;
                
            case 0:
                printf("\nSaindo do sistema...\n");
                printf("Salvando dados...\n");
                salvarTodasTabelas();          // <-- AGORA ENCONTRA
                printf("Obrigado por utilizar!\n");
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                pausar();
        }
        
    } while(opcao != 0);
    
    return 0;
}

// =================================================================
// FUNCOES DE PERSISTENCIA (Commit 8) - ADICIONADAS AQUI
// =================================================================

// ------------------------
// Salvar tabela de encadeamento em arquivo (MODIFICADO Commit 13)
// ------------------------
// Acrescentado por Denilson (Modificado por Frederico)
void salvarEncadeamento() {
    FILE *arquivo = fopen(ARQ_ENCADEAMENTO, "w");
    
    if(arquivo == NULL) {
        printf("Erro ao criar arquivo %s\n", ARQ_ENCADEAMENTO);
        return;
    }
    
    fprintf(arquivo, "# Tabela Hash - Encadeamento\n");
    fprintf(arquivo, "# Formato: indice:numero_str:numero_int:nome:curso\n\n");
    
    for(int i = 0; i < TAM; i++) {
        if(tabelaEncadeamento[i] != NULL) {
            Estudante* temp = tabelaEncadeamento[i];
            while(temp != NULL) {
                fprintf(arquivo, "%d:%s:%d:%s:%s\n", 
                        i, temp->numeroStr, temp->numero, 
                        temp->nome, temp->curso);
                temp = temp->prox;
            }
        }
    }
    
    fclose(arquivo);
}

// ------------------------
// Salvar tabela linear em arquivo (MODIFICADO Commit 13)
// ------------------------
// Acrescentado por Denilson (Modificado por Frederico)
void salvarLinear() {
    FILE *arquivo = fopen(ARQ_LINEAR, "w");
    
    if(arquivo == NULL) {
        printf("Erro ao criar arquivo %s\n", ARQ_LINEAR);
        return;
    }
    
    fprintf(arquivo, "# Tabela Hash - Sondagem Linear\n");
    fprintf(arquivo, "# Formato: indice:numero_str:numero_int:nome:curso\n\n");
    
    for(int i = 0; i < TAM; i++) {
        if(tabelaLinear[i].numero != -1) {
            fprintf(arquivo, "%d:%s:%d:%s:%s\n", 
                    i, tabelaLinear[i].numeroStr, tabelaLinear[i].numero,
                    tabelaLinear[i].nome, tabelaLinear[i].curso);
        }
    }
    
    fclose(arquivo);
}

// ------------------------
// Salvar todas as tabelas
// ------------------------
// Acrescentado por Denilson (Commit 8)
void salvarTodasTabelas() {
    salvarEncadeamento();
    salvarLinear();
    printf("Dados salvos com sucesso!\n");
}

// ------------------------
// Carregar tabela de encadeamento do arquivo (MODIFICADO Commit 13)
// ------------------------
// Acrescentado por Denilson (Modificado por Frederico)
void carregarEncadeamento() {
    FILE *arquivo = fopen(ARQ_ENCADEAMENTO, "r");
    
    if(arquivo == NULL) {
        return;
    }
    
    char linha[200];
    int indice, numero;
    char numeroStr[MAX_STR], nome[MAX_NOME], curso[MAX_CURSO];
    
    while(fgets(linha, sizeof(linha), arquivo)) {
        if(linha[0] == '#') continue;
        
        if(sscanf(linha, "%d:%[^:]:%d:%[^:]:%[^\n]", &indice, numeroStr, &numero, nome, curso) == 5) {
            Estudante* novo = (Estudante*)malloc(sizeof(Estudante));
            strcpy(novo->numeroStr, numeroStr);
            novo->numero = numero;
            strcpy(novo->nome, nome);
            strcpy(novo->curso, curso);
            novo->prox = NULL;
            
            if(tabelaEncadeamento[indice] == NULL) {
                tabelaEncadeamento[indice] = novo;
            } else {
                Estudante* temp = tabelaEncadeamento[indice];
                while(temp->prox != NULL) {
                    temp = temp->prox;
                }
                temp->prox = novo;
            }
        }
    }
    
    fclose(arquivo);
}

// ------------------------
// Carregar tabela linear do arquivo (MODIFICADO Commit 13)
// ------------------------
// Acrescentado por Denilson (Modificado por Frederico)
void carregarLinear() {
    FILE *arquivo = fopen(ARQ_LINEAR, "r");
    
    if(arquivo == NULL) {
        return;
    }
    
    char linha[200];
    int indice, numero;
    char numeroStr[MAX_STR], nome[MAX_NOME], curso[MAX_CURSO];
    
    while(fgets(linha, sizeof(linha), arquivo)) {
        if(linha[0] == '#') continue;
        
        if(sscanf(linha, "%d:%[^:]:%d:%[^:]:%[^\n]", &indice, numeroStr, &numero, nome, curso) == 5) {
            strcpy(tabelaLinear[indice].numeroStr, numeroStr);
            tabelaLinear[indice].numero = numero;
            strcpy(tabelaLinear[indice].nome, nome);
            strcpy(tabelaLinear[indice].curso, curso);
            tabelaLinear[indice].prox = NULL;
        }
    }
    
    fclose(arquivo);
}

// ------------------------
// Carregar todas as tabelas
// ------------------------
// Acrescentado por Denilson (Commit 8)
void carregarTodasTabelas() {
    carregarEncadeamento();
    carregarLinear();
    printf("Dados carregados dos arquivos.\n");
}

// =================================================================
// NOVAS FUNCOES DO COMMIT 13 (Frederico)
// =================================================================

// ------------------------
// Limpar buffer completo (inclui todos os caracteres)
// ------------------------
// Acrescentado por Frederico (Commit 13)
void limparBufferCompleto() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// ------------------------
// Converter string para inteiro (para hash)
// ------------------------
// Acrescentado por Frederico (Commit 13)
void converterParaInteiro(char numeroStr[], int *numero) {
    *numero = atoi(numeroStr);
}

// ------------------------
// Exibir numero completo com zeros a esquerda
// ------------------------
// Acrescentado por Frederico (Commit 13)
void exibirNumeroCompleto(char numeroStr[]) {
    printf("%s", numeroStr);
}

// ------------------------
// Validar entrada numerica (evita erros de buffer)
// ------------------------
// Acrescentado por Frederico (Commit 13)
int validarEntradaNumerica(char numeroStr[]) {
    // Verificar campo vazio
    if(validarCampoVazio(numeroStr)) {
        printf("Erro: Campo vazio! Digite novamente.\n");
        return 0;
    }
    
    // Verificar se contem apenas digitos
    for(int i = 0; numeroStr[i] != '\0'; i++) {
        if(!isdigit(numeroStr[i])) {
            printf("Erro: Apenas numeros sao permitidos!\n");
            return 0;
        }
    }
    
    return 1;
}

// =================================================================
// FUNCOES MODIFICADAS DO COMMIT 13 (Frederico)
// =================================================================

// ------------------------
// Ler dados do estudante com validacoes (MODIFICADO Commit 13)
// ------------------------
// Acrescentado por Frederico (Modificado por Ludovina e Frederico)
void lerDadosEstudante(char numeroStr[], char nome[], char curso[]) {
    int valido;
    
    printf("\n--- Dados do Estudante ---\n");
    
    // LIMPAR BUFFER ANTES DA LEITURA
    limparBufferCompleto();
    
    // Ler numero (agora como string, preserva zeros)
    do {
        printf("Numero do estudante (apenas digitos): ");
        fgets(numeroStr, MAX_STR, stdin);
        numeroStr[strcspn(numeroStr, "\n")] = 0;
        
        valido = validarEntradaNumerica(numeroStr);
        
    } while(!valido);
    
    printf("Numero validado: ");
    exibirNumeroCompleto(numeroStr);
    printf("\n");
    
    // LIMPAR BUFFER ANTES DO NOME
    limparBufferCompleto();
    
    // Ler nome com validacao de espacos (Commit 12)
    do {
        printf("Nome do estudante: ");
        fgets(nome, MAX_NOME, stdin);
        nome[strcspn(nome, "\n")] = 0;
        
        valido = 1;
        
        if(validarCampoVazio(nome)) {
            printf("Erro: Campo vazio! Digite novamente.\n");
            valido = 0;
        }
        else if(!validarNomeCompleto(nome)) {
            valido = 0;
        }
        
    } while(!valido);
    
    // LIMPAR BUFFER ANTES DO CURSO
    limparBufferCompleto();
    
    // Ler curso com validacao de espacos (Commit 12)
    do {
        printf("Curso do estudante: ");
        fgets(curso, MAX_CURSO, stdin);
        curso[strcspn(curso, "\n")] = 0;
        
        valido = 1;
        
        if(validarCampoVazio(curso)) {
            printf("Erro: Campo vazio! Digite novamente.\n");
            valido = 0;
        }
        else if(!validarCurso(curso)) {
            valido = 0;
        }
        
    } while(!valido);
}

// ------------------------
// Inserir estudante (MODIFICADO Commit 13)
// ------------------------
// Acrescentado por Frederico (Modificado por Denilson, Ludovina e Frederico)
void inserirEstudante() {
    char numeroStr[MAX_STR];
    char nome[MAX_NOME];
    char curso[MAX_CURSO];
    int numero;
    
    lerDadosEstudante(numeroStr, nome, curso);
    
    // Converter string para inteiro (para calculo do hash)
    converterParaInteiro(numeroStr, &numero);
    
    // Converter nome e curso para minusculas (Commit 11)
    converterParaMinusculas(nome);
    converterParaMinusculas(curso);
    
    printf("\n--- Dados do Estudante ---\n");
    printf("Numero completo: ");
    exibirNumeroCompleto(numeroStr);
    printf("\nNumero (para hash): %d\n", numero);
    printf("Nome: %s\n", nome);
    printf("Curso: %s\n", curso);
    
    // Verificar se estudante ja existe (Commit 11)
    if(verificarEstudanteDuplicado(numero, nome, curso)) {
        printf("Operacao cancelada.\n");
        pausar();
        return;
    }
    
    printf("\n--- Inserindo nas tabelas ---\n");
    inserirEncadeamento(numeroStr, numero, nome, curso);
    inserirLinear(numeroStr, numero, nome, curso);
    
    printf("\n--- Estado atual das tabelas ---\n");
    exibirTodasTabelas();          // <-- AGORA ENCONTRA
    
    pausar();
}

// ------------------------
// Inserir estudante na tabela de encadeamento (MODIFICADO Commit 13)
// ------------------------
// Acrescentado por Denilson (Modificado por Frederico)
void inserirEncadeamento(char numeroStr[], int numero, char nome[], char curso[]) {
    int indice = funcaoHash(numero);
    Estudante* novo = (Estudante*)malloc(sizeof(Estudante));
    
    strcpy(novo->numeroStr, numeroStr);  // Guarda string com zeros
    novo->numero = numero;
    strcpy(novo->nome, nome);
    strcpy(novo->curso, curso);
    novo->prox = NULL;
    
    printf("\n[ENCADEAMENTO] Numero: ");
    exibirNumeroCompleto(numeroStr);
    printf(" (hash: %d)\n", numero);
    printf("Indice calculado: %d\n", indice);
    
    if(tabelaEncadeamento[indice] == NULL) {
        tabelaEncadeamento[indice] = novo;
        printf("Indice %d: vazio - inserido com sucesso!\n", indice);
    } else {
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
// Inserir estudante na tabela de sondagem linear (MODIFICADO Commit 13)
// ------------------------
// Acrescentado por Ludovina (Modificado por Frederico)
void inserirLinear(char numeroStr[], int numero, char nome[], char curso[]) {
    int indiceOriginal = funcaoHash(numero);
    int indice = indiceOriginal;
    int tentativas = 0;
    
    printf("\n[LINEAR] Numero: ");
    exibirNumeroCompleto(numeroStr);
    printf(" (hash: %d)\n", numero);
    printf("Indice calculado: %d\n", indiceOriginal);
    
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
    
    strcpy(tabelaLinear[indice].numeroStr, numeroStr);  // Guarda string com zeros
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
// Exibir tabela de encadeamento (MODIFICADO Commit 13)
// ------------------------
// Acrescentado por Frederico (Modificado por Frederico)
void exibirTabelaEncadeamento() {
    printf("\n=== TABELA HASH - ENCADEAMENTO ===\n");
    printf("Indice | Status | Alunos (numero completo)\n");
    desenharLinha(50);
    
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
                printf("%s: %s (%s)\n", temp->numeroStr, temp->nome, temp->curso);
                temp = temp->prox;
                cont++;
            }
        }
        desenharLinha(50);
    }
}

// ------------------------
// Exibir tabela de sondagem linear (MODIFICADO Commit 13)
// ------------------------
// Acrescentado por Frederico (Modificado por Frederico)
void exibirTabelaLinear() {
    printf("\n=== TABELA HASH - SONDAGEM LINEAR ===\n");
    printf("Indice | Status   | Aluno (numero completo)\n");
    desenharLinha(50);
    
    for(int i = 0; i < TAM; i++) {
        printf("%3d    | ", i);
        
        if(tabelaLinear[i].numero == -1) {
            printf("Vazio     | (nenhum aluno)\n");
        } else {
            printf("Ocupado   | %s: %s (%s)\n", 
                   tabelaLinear[i].numeroStr, 
                   tabelaLinear[i].nome, 
                   tabelaLinear[i].curso);
        }
        desenharLinha(50);
    }
}

// ------------------------
// Exibir todas as tabelas
// ------------------------
// Acrescentado por Frederico (Commit 6)
void exibirTodasTabelas() {
    exibirTabelaEncadeamento();
    exibirTabelaLinear();
}

// ------------------------
// Desenhar linha separadora
// ------------------------
// Acrescentado por Frederico (Commit 6)
void desenharLinha(int tamanho) {
    for(int i = 0; i < tamanho; i++) {
        printf("-");
    }
    printf("\n");
}

// ------------------------
// Listar todos os alunos de um indice (MODIFICADO Commit 13)
// ------------------------
// Acrescentado por Denilson (Modificado por Frederico)
void listarAlunosIndiceEncadeamento(int indice) {
    printf("\n--- Alunos no indice %d (Encadeamento) ---\n", indice);
    
    if(tabelaEncadeamento[indice] == NULL) {
        printf("Nenhum aluno encontrado neste indice.\n");
        return;
    }
    
    Estudante* temp = tabelaEncadeamento[indice];
    int cont = 1;
    
    printf("Total de alunos neste indice: (lista locada)\n");
    desenharLinha(60);
    
    while(temp != NULL) {
        printf("Aluno %d:\n", cont);
        printf("  Numero completo: %s\n", temp->numeroStr);
        printf("  Nome: %s\n", temp->nome);
        printf("  Curso: %s\n", temp->curso);
        desenharLinha(40);
        
        temp = temp->prox;
        cont++;
    }
}

// ------------------------
// Mostrar aluno de um indice na tabela linear (MODIFICADO Commit 13)
// ------------------------
// Acrescentado por Denilson (Modificado por Frederico)
void mostrarAlunoIndiceLinear(int indice) {
    printf("\n--- Aluno no indice %d (Sondagem Linear) ---\n", indice);
    
    if(tabelaLinear[indice].numero == -1) {
        printf("Nenhum aluno encontrado neste indice.\n");
        return;
    }
    
    printf("Numero completo: %s\n", tabelaLinear[indice].numeroStr);
    printf("Nome: %s\n", tabelaLinear[indice].nome);
    printf("Curso: %s\n", tabelaLinear[indice].curso);
    
    int indiceOriginal = funcaoHash(tabelaLinear[indice].numero);
    if(indiceOriginal != indice) {
        printf("\n(Observacao: Este aluno sofreu colisao na insercao.\n");
        printf("Indice original calculado: %d\n", indiceOriginal);
        printf("Indice real apos sondagem: %d)\n", indice);
    }
}

// ------------------------
// Remover estudante da tabela de encadeamento (MODIFICADO Commit 13)
// ------------------------
// Acrescentado por Frederico (Modificado por Denilson e Frederico)
void removerEncadeamento() {
    int indice;
    char indiceStr[MAX_STR];
    
    printf("\n--- Remocao por Encadeamento ---\n");
    printf("Digite o indice que deseja remover (0 a %d): ", TAM-1);
    
    do {
        lerString(indiceStr, MAX_STR, "");
        if(!validarApenasDigitos(indiceStr)) {
            printf("Erro: Digite apenas numeros! Tente novamente: ");
        }
    } while(!validarApenasDigitos(indiceStr));
    
    indice = atoi(indiceStr);
    
    if(indice < 0 || indice >= TAM) {
        printf("Indice invalido! Deve ser entre 0 e %d.\n", TAM-1);
        return;
    }
    
    if(tabelaEncadeamento[indice] == NULL) {
        printf("Nenhum aluno encontrado no indice %d.\n", indice);
        return;
    }
    
    int posicao = escolherAlunoIndiceEncadeamento(indice);
    
    if(posicao > 0) {
        // Obter a string do numero do estudante antes de remover
        Estudante* temp = tabelaEncadeamento[indice];
        for(int i = 1; i < posicao; i++) {
            temp = temp->prox;
        }
        char numeroRemover[MAX_STR];
        strcpy(numeroRemover, temp->numeroStr);
        
        // Remover da tabela de encadeamento
        removerAlunoEncadeamento(indice, posicao);
        
        // Remover tambem da tabela linear (usando string)
        removerDaTabelaLinear(numeroRemover);
        
        printf("\n--- Resultado da Remocao ---\n");
        printf("Estudante removido das duas tabelas com sucesso!\n");
    }
}

// ------------------------
// Remover estudante da tabela de sondagem linear (MODIFICADO Commit 13)
// ------------------------
// Acrescentado por Frederico (Modificado por Denilson e Frederico)
void removerLinear() {
    int indice;
    char indiceStr[MAX_STR];
    char confirmacao;
    
    printf("\n--- Remocao por Sondagem Linear ---\n");
    printf("Digite o indice que deseja remover (0 a %d): ", TAM-1);
    
    do {
        lerString(indiceStr, MAX_STR, "");
        if(!validarApenasDigitos(indiceStr)) {
            printf("Erro: Digite apenas numeros! Tente novamente: ");
        }
    } while(!validarApenasDigitos(indiceStr));
    
    indice = atoi(indiceStr);
    
    if(indice < 0 || indice >= TAM) {
        printf("Indice invalido! Deve ser entre 0 e %d.\n", TAM-1);
        return;
    }
    
    if(tabelaLinear[indice].numero == -1) {
        printf("Nenhum aluno encontrado no indice %d.\n", indice);
        return;
    }
    
    printf("\nAluno encontrado no indice %d:\n", indice);
    printf("  Numero completo: %s\n", tabelaLinear[indice].numeroStr);
    printf("  Nome: %s\n", tabelaLinear[indice].nome);
    printf("  Curso: %s\n", tabelaLinear[indice].curso);
    
    printf("\nTem certeza que deseja remover este aluno? (s/n): ");
    scanf("%c", &confirmacao);
    limparBufferCompleto();
    
    if(confirmacao == 's' || confirmacao == 'S') {
        char numeroRemover[MAX_STR];
        strcpy(numeroRemover, tabelaLinear[indice].numeroStr);
        
        // Remover da tabela linear
        tabelaLinear[indice].numero = -1;
        strcpy(tabelaLinear[indice].numeroStr, "");
        strcpy(tabelaLinear[indice].nome, "");
        strcpy(tabelaLinear[indice].curso, "");
        
        // Remover tambem da tabela de encadeamento (usando string)
        removerDaTabelaEncadeamento(numeroRemover);
        
        printf("\n--- Resultado da Remocao ---\n");
        printf("Estudante removido das duas tabelas com sucesso!\n");
    } else {
        printf("Operacao cancelada.\n");
    }
}

// ------------------------
// Escolher qual aluno remover (MODIFICADO Commit 13)
// ------------------------
// Acrescentado por Frederico (Modificado por Frederico)
int escolherAlunoIndiceEncadeamento(int indice) {
    Estudante* temp = tabelaEncadeamento[indice];
    int total = 0;
    char escolhaStr[MAX_STR];
    int escolha;
    
    while(temp != NULL) {
        total++;
        temp = temp->prox;
    }
    
    printf("\n--- Alunos no indice %d ---\n", indice);
    printf("Total de alunos: %d\n", total);
    desenharLinha(60);
    
    temp = tabelaEncadeamento[indice];
    for(int i = 1; i <= total; i++) {
        printf("%d. Numero: %s\n", i, temp->numeroStr);
        printf("   Nome: %s\n", temp->nome);
        printf("   Curso: %s\n", temp->curso);
        desenharLinha(40);
        temp = temp->prox;
    }
    
    printf("Escolha o numero do aluno que deseja remover (1 a %d, 0 para cancelar): ", total);
    
    do {
        lerString(escolhaStr, MAX_STR, "");
        if(!validarApenasDigitos(escolhaStr)) {
            printf("Erro: Digite apenas numeros! Tente novamente: ");
        }
    } while(!validarApenasDigitos(escolhaStr));
    
    escolha = atoi(escolhaStr);
    
    if(escolha == 0) {
        printf("Operacao cancelada.\n");
        return 0;
    }
    
    if(escolha < 1 || escolha > total) {
        printf("Escolha invalida! Deve ser entre 1 e %d.\n", total);
        return 0;
    }
    
    return escolha;
}

// ------------------------
// Remover aluno de uma posicao especifica no encadeamento
// ------------------------
// Acrescentado por Frederico (Commit 9)
void removerAlunoEncadeamento(int indice, int posicao) {
    Estudante* temp = tabelaEncadeamento[indice];
    Estudante* ant = NULL;
    
    if(posicao == 1) {
        tabelaEncadeamento[indice] = temp->prox;
        free(temp);
        return;
    }
    
    for(int i = 1; i < posicao; i++) {
        ant = temp;
        temp = temp->prox;
    }
    
    if(ant != NULL) {
        ant->prox = temp->prox;
        free(temp);
    }
}

// ------------------------
// Remover da tabela encadeamento por string (NOVO Commit 13)
// ------------------------
// Acrescentado por Frederico (Commit 13)
void removerDaTabelaEncadeamento(char numeroStr[]) {
    int numero = atoi(numeroStr);
    int indice = funcaoHash(numero);
    Estudante* temp = tabelaEncadeamento[indice];
    Estudante* ant = NULL;
    int encontrado = 0;
    
    while(temp != NULL) {
        if(strcmp(temp->numeroStr, numeroStr) == 0) {
            encontrado = 1;
            if(ant == NULL) {
                tabelaEncadeamento[indice] = temp->prox;
            } else {
                ant->prox = temp->prox;
            }
            free(temp);
            printf("  • Removido da tabela de encadeamento (indice %d)\n", indice);
            break;
        }
        ant = temp;
        temp = temp->prox;
    }
    
    if(!encontrado) {
        printf("  • Estudante nao encontrado na tabela de encadeamento\n");
    }
}

// ------------------------
// Remover da tabela linear por string (NOVO Commit 13)
// ------------------------
// Acrescentado por Frederico (Commit 13)
void removerDaTabelaLinear(char numeroStr[]) {
    int indice = encontrarIndiceLinearPorNumeroStr(numeroStr);
    
    if(indice != -1) {
        tabelaLinear[indice].numero = -1;
        strcpy(tabelaLinear[indice].numeroStr, "");
        strcpy(tabelaLinear[indice].nome, "");
        strcpy(tabelaLinear[indice].curso, "");
        printf("  • Removido da tabela linear (indice %d)\n", indice);
    } else {
        printf("  • Estudante nao encontrado na tabela linear\n");
    }
}

// ------------------------
// Encontrar indice na tabela linear por string (NOVO Commit 13)
// ------------------------
// Acrescentado por Frederico (Commit 13)
int encontrarIndiceLinearPorNumeroStr(char numeroStr[]) {
    for(int i = 0; i < TAM; i++) {
        if(strcmp(tabelaLinear[i].numeroStr, numeroStr) == 0) {
            return i;
        }
    }
    return -1;
}

// ------------------------
// Remover estudante de ambas as tabelas
// ------------------------
// Acrescentado por Denilson (Commit 10) - Modificado Commit 13
void removerDeAmbasTabelas(char numeroStr[]) {
    printf("\n--- Removendo de ambas as tabelas ---\n");
    
    // Remover da tabela de encadeamento
    removerDaTabelaEncadeamento(numeroStr);
    
    // Remover da tabela linear
    removerDaTabelaLinear(numeroStr);
}

// ------------------------
// Remover estudante da tabela linear por numero (int) - Mantido compatibilidade
// ------------------------
// Acrescentado por Denilson (Commit 10)
void removerDaTabelaLinearPorNumero(int numero) {
    int indice = encontrarIndiceLinearPorNumero(numero);
    
    if(indice != -1) {
        tabelaLinear[indice].numero = -1;
        strcpy(tabelaLinear[indice].numeroStr, "");
        strcpy(tabelaLinear[indice].nome, "");
        strcpy(tabelaLinear[indice].curso, "");
        printf("  • Removido da tabela linear (indice %d)\n", indice);
    } else {
        printf("  • Estudante nao encontrado na tabela linear\n");
    }
}

// ------------------------
// Encontrar indice na tabela linear pelo numero (int)
// ------------------------
// Acrescentado por Denilson (Commit 10)
int encontrarIndiceLinearPorNumero(int numero) {
    int indiceOriginal = funcaoHash(numero);
    int indice = indiceOriginal;
    
    do {
        if(tabelaLinear[indice].numero == numero) {
            return indice;
        }
        indice = (indice + 1) % TAM;
    } while(indice != indiceOriginal);
    
    return -1;  // Nao encontrado
}

// =================================================================
// FUNCOES DO COMMIT 12 (MANTIDAS IGUAL)
// =================================================================

// ------------------------
// Validar se string contem apenas digitos
// ------------------------
// Acrescentado por Ludovina (Commit 2)
int validarApenasDigitos(char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

// ------------------------
// Validar se string contem apenas letras e espacos
// ------------------------
// Acrescentado por Ludovina (Commit 2)
int validarApenasLetras(char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(!isalpha(str[i]) && str[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

// ------------------------
// Validar se campo nao esta vazio
// ------------------------
// Acrescentado por Ludovina (Commit 2)
int validarCampoVazio(char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] != ' ' && str[i] != '\n' && str[i] != '\t') {
            return 0;
        }
    }
    return 1;
}

// ------------------------
// Validar se a string tem espacos consecutivos
// ------------------------
// Acrescentado por Ludovina (Commit 12)
int validarEspacos(char str[]) {
    int espacoAnterior = 0;
    
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == ' ') {
            if(espacoAnterior) {
                return 0;  // Dois espacos consecutivos encontrados
            }
            espacoAnterior = 1;
        } else {
            espacoAnterior = 0;
        }
    }
    return 1;  // Validacao passou
}

// ------------------------
// Validar nome completo (permite espacos, mas nao consecutivos)
// ------------------------
// Acrescentado por Ludovina (Commit 12)
int validarNomeCompleto(char str[]) {
    // Primeiro verifica se tem apenas letras e espacos
    for(int i = 0; str[i] != '\0'; i++) {
        if(!isalpha(str[i]) && str[i] != ' ') {
            printf("Erro: Nome deve conter apenas letras e espacos.\n");
            return 0;
        }
    }
    
    // Verifica espacos consecutivos
    if(!validarEspacos(str)) {
        printf("Erro: Nome nao pode ter espacos consecutivos.\n");
        return 0;
    }
    
    return 1;
}

// ------------------------
// Validar curso (permite espacos, mas nao consecutivos)
// ------------------------
// Acrescentado por Ludovina (Commit 12)
int validarCurso(char str[]) {
    // Primeiro verifica se tem apenas letras e espacos
    for(int i = 0; str[i] != '\0'; i++) {
        if(!isalpha(str[i]) && str[i] != ' ') {
            printf("Erro: Curso deve conter apenas letras e espacos.\n");
            return 0;
        }
    }
    
    // Verifica espacos consecutivos
    if(!validarEspacos(str)) {
        printf("Erro: Curso nao pode ter espacos consecutivos.\n");
        return 0;
    }
    
    return 1;
}

// ------------------------
// Ler string (mantida para compatibilidade)
// ------------------------
// Acrescentado por Ludovina (Commit 2)
void lerString(char destino[], int tamanho, char mensagem[]) {
    printf("%s", mensagem);
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = 0;
}

// ------------------------
// Exibir submenu
// ------------------------
// Acrescentado por Ludovina (Commit 2)
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
// Converter string para minusculas
// ------------------------
// Acrescentado por Denilson (Commit 11)
void converterParaMinusculas(char str[]) {
    for(int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

// ------------------------
// Comparar duas strings ignorando maiusculas/minusculas
// ------------------------
// Acrescentado por Denilson (Commit 11)
int compararNomesIgnorandoMaiusculas(char str1[], char str2[]) {
    char temp1[MAX_NOME], temp2[MAX_NOME];
    
    strcpy(temp1, str1);
    strcpy(temp2, str2);
    
    converterParaMinusculas(temp1);
    converterParaMinusculas(temp2);
    
    return strcmp(temp1, temp2);
}

// ------------------------
// Comparar dois cursos ignorando maiusculas/minusculas
// ------------------------
// Acrescentado por Denilson (Commit 11)
int compararCursosIgnorandoMaiusculas(char str1[], char str2[]) {
    char temp1[MAX_CURSO], temp2[MAX_CURSO];
    
    strcpy(temp1, str1);
    strcpy(temp2, str2);
    
    converterParaMinusculas(temp1);
    converterParaMinusculas(temp2);
    
    return strcmp(temp1, temp2);
}

// ------------------------
// Verificar se estudante ja existe nas tabelas
// ------------------------
// Acrescentado por Denilson (Commit 11) - Corrigido
int verificarEstudanteDuplicado(int numero, char nome[], char curso[]) {
    int indice = funcaoHash(numero);
    
    // Converter para minusculas para comparacao
    char nomeMinusculo[MAX_NOME];
    char cursoMinusculo[MAX_CURSO];
    strcpy(nomeMinusculo, nome);
    strcpy(cursoMinusculo, curso);
    converterParaMinusculas(nomeMinusculo);
    converterParaMinusculas(cursoMinusculo);
    
    // Verificar na tabela de encadeamento
    Estudante* temp = tabelaEncadeamento[indice];
    while(temp != NULL) {
        if(temp->numero == numero) {
            char tempNomeMinusculo[MAX_NOME];
            char tempCursoMinusculo[MAX_CURSO];
            strcpy(tempNomeMinusculo, temp->nome);
            strcpy(tempCursoMinusculo, temp->curso);
            converterParaMinusculas(tempNomeMinusculo);
            converterParaMinusculas(tempCursoMinusculo);
            
            if(strcmp(tempNomeMinusculo, nomeMinusculo) == 0 && 
               strcmp(tempCursoMinusculo, cursoMinusculo) == 0) {
                printf("\n!!! ESTUDANTE DUPLICADO DETECTADO !!!\n");
                printf("Ja existe um estudante com:\n");
                printf("  Numero: %d\n", temp->numero);
                printf("  Nome: %s\n", temp->nome);
                printf("  Curso: %s\n", temp->curso);
                return 1;
            }
        }
        temp = temp->prox;
    }
    
    // Verificar na tabela linear
    for(int i = 0; i < TAM; i++) {
        if(tabelaLinear[i].numero == numero) {
            char tempNomeMinusculo[MAX_NOME];
            char tempCursoMinusculo[MAX_CURSO];
            strcpy(tempNomeMinusculo, tabelaLinear[i].nome);
            strcpy(tempCursoMinusculo, tabelaLinear[i].curso);
            converterParaMinusculas(tempNomeMinusculo);
            converterParaMinusculas(tempCursoMinusculo);
            
            if(strcmp(tempNomeMinusculo, nomeMinusculo) == 0 && 
               strcmp(tempCursoMinusculo, cursoMinusculo) == 0) {
                printf("\n!!! ESTUDANTE DUPLICADO DETECTADO !!!\n");
                printf("Ja existe um estudante com:\n");
                printf("  Numero: %d\n", tabelaLinear[i].numero);
                printf("  Nome: %s\n", tabelaLinear[i].nome);
                printf("  Curso: %s\n", tabelaLinear[i].curso);
                return 1;
            }
        }
    }
    
    return 0;
}

// ------------------------
// Exibir mensagem de colisao para encadeamento
// ------------------------
// Acrescentado por Denilson (Commit 4)
void exibirMensagemColisaoEncadeamento(int indice) {
    printf("\n!!! COLISAO DETECTADA !!!\n");
    printf("Indice %d ja esta ocupado.\n", indice);
    printf("Como e uma tabela com encadeamento (lista locada),\n");
    printf("o estudante sera alocado no final da lista existente.\n");
    printf("----------------------------------------\n");
}

// ------------------------
// Exibir mensagem de colisao para sondagem linear
// ------------------------
// Acrescentado por Ludovina (Commit 5)
void exibirMensagemColisaoLinear(int indiceOcupado, int proximoIndice) {
    printf("\n!!! COLISAO DETECTADA !!!\n");
    printf("Indice %d ocupado, apliquei no indice %d (sondagem linear).\n", 
           indiceOcupado, proximoIndice);
    printf("----------------------------------------\n");
}

// ------------------------
// Menu de procura de estudante
// ------------------------
// Acrescentado por Denilson (Commit 7)
void menuProcurar() {
    int opcao;
    
    do {
        exibirSubMenu("PROCURAR ESTUDANTE");
        scanf("%d", &opcao);
        limparBufferCompleto();
        
        switch(opcao) {
            case 1:
                printf("\n--- Busca por Encadeamento ---\n");
                procurarEncadeamento();
                pausar();
                break;
                
            case 2:
                printf("\n--- Busca por Sondagem Linear ---\n");
                procurarLinear();
                pausar();
                break;
                
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
                
            default:
                printf("Opcao invalida!\n");
                pausar();
        }
    } while(opcao != 0);
}

// ------------------------
// Procurar estudante na tabela de encadeamento
// ------------------------
// Acrescentado por Denilson (Commit 7) - Modificado Commit 13
void procurarEncadeamento() {
    int indice;
    char indiceStr[MAX_STR];
    
    exibirTabelaEncadeamento();
    
    printf("\n--- Busca por Encadeamento ---\n");
    printf("Digite o indice que deseja consultar (0 a %d): ", TAM-1);
    
    do {
        lerString(indiceStr, MAX_STR, "");
        if(!validarApenasDigitos(indiceStr)) {
            printf("Erro: Digite apenas numeros! Tente novamente: ");
        }
    } while(!validarApenasDigitos(indiceStr));
    
    indice = atoi(indiceStr);
    
    if(indice < 0 || indice >= TAM) {
        printf("Indice invalido! Deve ser entre 0 e %d.\n", TAM-1);
        return;
    }
    
    listarAlunosIndiceEncadeamento(indice);
}

// ------------------------
// Procurar estudante na tabela de sondagem linear
// ------------------------
// Acrescentado por Denilson (Commit 7) - Modificado Commit 13
void procurarLinear() {
    int indice;
    char indiceStr[MAX_STR];
    
    exibirTabelaLinear();
    
    printf("\n--- Busca por Sondagem Linear ---\n");
    printf("Digite o indice que deseja consultar (0 a %d): ", TAM-1);
    
    do {
        lerString(indiceStr, MAX_STR, "");
        if(!validarApenasDigitos(indiceStr)) {
            printf("Erro: Digite apenas numeros! Tente novamente: ");
        }
    } while(!validarApenasDigitos(indiceStr));
    
    indice = atoi(indiceStr);
    
    if(indice < 0 || indice >= TAM) {
        printf("Indice invalido! Deve ser entre 0 e %d.\n", TAM-1);
        return;
    }
    
    mostrarAlunoIndiceLinear(indice);
}

// ------------------------
// Menu de remocao de estudante
// ------------------------
// Acrescentado por Frederico (Commit 9) - Modificado Commit 13
void menuRemover() {
    int opcao;
    
    do {
        exibirSubMenu("REMOVER ESTUDANTE");
        scanf("%d", &opcao);
        limparBufferCompleto();
        
        switch(opcao) {
            case 1:
                printf("\n--- Remocao por Encadeamento ---\n");
                exibirTabelaEncadeamento();
                removerEncadeamento();
                pausar();
                break;
                
            case 2:
                printf("\n--- Remocao por Sondagem Linear ---\n");
                exibirTabelaLinear();
                removerLinear();
                pausar();
                break;
                
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
                
            default:
                printf("Opcao invalida!\n");
                pausar();
        }
    } while(opcao != 0);
}

// ------------------------
// Funcao hash (resto da divisao)
// ------------------------
// Elaborado por Denilson (Commit 1)
int funcaoHash(int numero) {
    return numero % TAM;
}

// ------------------------
// Inicializar as tabelas hash (MODIFICADO Commit 13)
// ------------------------
// Elaborado por Denilson (Modificado por Frederico)
void inicializarTabelas() {
    for(int i = 0; i < TAM; i++) {
        tabelaEncadeamento[i] = NULL;
        tabelaLinear[i].numero = -1;
        strcpy(tabelaLinear[i].numeroStr, "");
        strcpy(tabelaLinear[i].nome, "");
        strcpy(tabelaLinear[i].curso, "");
        tabelaLinear[i].prox = NULL;
    }
}

// ------------------------
// Exibir menu principal
// ------------------------
// Elaborado por Denilson (Commit 1)
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
// Limpar buffer do teclado (antiga, mantida para compatibilidade)
// ------------------------
// Elaborado por Denilson (Commit 1)
void limparBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// ------------------------
// Pausar execucao
// ------------------------
// Elaborado por Denilson (Commit 1)
void pausar() {
    printf("\nPressione Enter para continuar...");
    limparBufferCompleto();
    getchar();
}
