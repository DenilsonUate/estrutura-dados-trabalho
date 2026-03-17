Exercício 6
Enunciado:
O código abaixo tenta remover um estudante da tabela de encadeamento, mas contém erros. Identifique e corrija os problemas.

c
void removerDaTabelaEncadeamento(int numero) {
    int indice = funcaoHash(numero);
    Estudante* temp = tabelaEncadeamento[indice];
    
    while(temp != NULL) {
        if(temp->numero == numero) {
            free(temp);
            return;
        }
        temp = temp->prox;
    }
}
Resolução:

Problemas identificados:

Não atualiza o ponteiro anterior: Ao remover um elemento do meio da lista, o elemento anterior deve apontar para o próximo do removido.

Caso especial do primeiro elemento: Se o elemento a remover for o primeiro, a tabela deve apontar para o segundo.

Não libera apenas o nó correto: O código libera o nó mas não ajusta os ponteiros.

Código corrigido:

c
void removerDaTabelaEncadeamento(int numero) {
    int indice = funcaoHash(numero);
    Estudante* temp = tabelaEncadeamento[indice];
    Estudante* anterior = NULL;
    
    while(temp != NULL) {
        if(temp->numero == numero) {
            // Encontrou o elemento a remover
            if(anterior == NULL) {
                // Caso 1: é o primeiro da lista
                tabelaEncadeamento[indice] = temp->prox;
            } else {
                // Caso 2: está no meio ou no final
                anterior->prox = temp->prox;
            }
            
            printf("Removido: %d - %s\n", temp->numero, temp->nome);
            free(temp);  // Libera memória
            return;
        }
        
        anterior = temp;
        temp = temp->prox;
    }
    
    printf("Estudante %d não encontrado.\n", numero);
