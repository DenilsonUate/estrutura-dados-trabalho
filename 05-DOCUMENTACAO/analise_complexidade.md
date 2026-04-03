5.ANÁLISE DE COMPLEXIDADE
5.1 Complexidade Temporal
Operação	Encadeamento	Sondagem Linear
Inserção	O(1) médio, O(n) pior caso	O(1) médio, O(n) pior caso
Busca	O(1) médio, O(n) pior caso	O(1) médio, O(n) pior caso
Remoção	O(1) médio, O(n) pior caso	O(1) médio, O(n) pior caso
Onde:

n = número de elementos na tabela

TAM = 10 (constante)

5.2 Complexidade Espacial
Encadeamento: O(n) + overhead dos ponteiros
-Cada elemento armazenado ocupa espaço;
-Além disso, há ponteiros (próximo nó) em cada elemento da lista;
-Espaço cresce linearmente com o número de elementos (n).

Sondagem Linear: O(TAM) fixo, independente de n
A tabela tem tamanho fixo (10)
-Não importa se n = 0 ou n = 10, a memória alocada é sempre a mesma;
-Vantagem: previsível e não há overhead de ponteiros;
-Desvantagem: quando n se aproxima de TAM, a performance degrada muito.


5.3 Fator de Carga
Fator de carga = n / TAM

Ideal: manter fator de carga ≤ 0.7
Quando TAM = 10 e fator de carga = 0.7 → máximo 7 estudantes
Regra prática: quando o fator de carga ultrapassa 0.7, recomenda-se redimensionar a tabela (aumentar TAM) e rehash de todos os elementos

No nosso caso, TAM = 10, fator 0.7 → máximo 7 estudantes para manter boa performance
Por que sonda linear sofre mais com fator de carga alto?
No encadeamento, mesmo com fator 1.0, cada posição tem em média 1 elemento. Na sonda linear, com fator 0.9, a probabilidade de encontrar aglomerados (clusters) é alta, aumentando o tempo de busca.
