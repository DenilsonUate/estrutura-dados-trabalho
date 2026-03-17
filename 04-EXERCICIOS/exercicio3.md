Exercício 3
Enunciado:
Analise o código da função inserirEncadeamento() abaixo e identifique possíveis problemas de memória. Proponha uma correção.

c
void inserirEncadeamento(int numero, char nome[], char curso[]) {
    int indice = funcaoHash(numero);
    Estudante novo;
    
    novo.numero = numero;
    strcpy(novo.nome, nome);
    strcpy(novo.curso, curso);
    novo.prox = NULL;
    
    if(tabelaEncadeamento[indice] == NULL) {
        tabelaEncadeamento[indice] = &novo;
    } else {
        Estudante* temp = tabelaEncadeamento[indice];
        while(temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = &novo;
    }
}
Resolução:

Problemas identificados:

Variável local no stack: Estudante novo é uma variável local alocada na pilha (stack). Quando a função termina, essa memória é liberada, mas o ponteiro na tabela continua apontando para uma área de memória que não pertence mais ao programa (ponteiro pendurado - dangling pointer).

Acesso inválido: Qualquer tentativa futura de acessar esse estudante resultará em comportamento indefinido.

Código corrigido:

c
void inserirEncadeamento(int numero, char nome[], char curso[]) {
    int indice = funcaoHash(numero);
    
    // Alocação dinâmica no heap
    Estudante* novo = (Estudante*)malloc(sizeof(Estudante));
    
    if(novo == NULL) {
        printf("Erro: Memória insuficiente!\n");
        return;
    }
    
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

