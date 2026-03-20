5. ANÁLISE DE COMPLEXIDADE
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

Sondagem Linear: O(TAM) fixo, independente de n

5.3 Fator de Carga
Fator de carga = n / TAM

Ideal: manter fator de carga ≤ 0.7

Quando TAM = 10 e fator de carga = 0.7 → máximo 7 estudantes
