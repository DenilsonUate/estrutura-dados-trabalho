# estrutura-dados-trabalho
# Estruturas de Dados e Algoritmos
## Trabalho Prático

### Tema
Implementação de Tabela Hash

### Grupo
- Denilson 
- Ludovina 
- Frederico

### Descrição
Este projeto implementa um sistema de registro de estudantes utilizando duas abordagens de tabelas hash:
- **Encadeamento (Lista Ligada)**: Resolve colisões através de listas encadeadas
- **Sondagem Linear**: Resolve colisões procurando a próxima posição disponível

O sistema permite inserir, buscar e remover estudantes, com persistência de dados em arquivos e validações robustas de entrada.

### Funcionalidades
-  **Inserir Estudante**: Adiciona novo estudante nas duas tabelas simultaneamente
-  **Procurar Estudante**: Busca por índice em qualquer uma das tabelas
-  **Remover Estudante**: Remove de ambas as tabelas de forma sincronizada

#### Linguagem utilizada
 -C

### Como executar

- **Compilar o programa**
  -gcc -o CODIGO main.c -std=c99
  
- **Executar** 
- ./CODIGO
