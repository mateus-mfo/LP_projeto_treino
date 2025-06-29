# Sistema de Treinos

Um sistema de gerenciamento de treinos para academias desenvolvido em C, que permite o controle de alunos e seus respectivos exercícios através de uma estrutura de fila circular.

## Funcionalidades

### Para Instrutores
- **Cadastrar alunos**: Adiciona novos alunos ao sistema com ID único
- **Listar alunos**: Visualiza todos os alunos cadastrados
- **Adicionar treinos**: Cria grupos de treinos personalizados para cada aluno

### Para Alunos
- **Visualizar treinos**: Consulta a fila de treinos pendentes
- **Marcar treino como concluído**: Registra a execução de exercícios
- **Controle de progresso**: Acompanha quantas execuções restam para cada treino

##  Estrutura do Projeto

```
projeto/
├── main.c              # Programa principal e menus
├── aluno.h             # Header para funcionalidades de alunos
├── aluno.c             # Implementação das funções de alunos
├── treino.h            # Header para funcionalidades de treinos
├── treino.c            # Implementação das funções de treinos
├── instrutor.h         # Header para funcionalidades do instrutor
├── instrutor.c         # Implementação do menu do instrutor
├── CMakeLists.txt      # Configuração do CMake
├── dados.txt           # Arquivo de dados dos alunos (gerado automaticamente)
└── treino.txt          # Arquivo de dados dos treinos (gerado automaticamente)
```

## Compilação e Execução

### Usando CMake (Recomendado)

```bash
# Criar diretório de build
mkdir build
cd build

# Configurar o projeto
cmake ..

# Compilar
make

# Executar
./LP_projeto_treino_rev01
```

### Compilação Manual

```bash
gcc -o sistema_treinos main.c aluno.c treino.c instrutor.c
./sistema_treinos
```

## Estruturas de Dados

### Aluno
```c
typedef struct {
    int id;           // ID único do aluno
    char nome[50];    // Nome do aluno
} Aluno;
```

### Treino (Fila Circular)
```c
typedef struct Treino {
    int alunoId;                    // ID do aluno
    char grupo_muscular[50];        // Nome do grupo muscular
    int execucoes_restantes;        // Execuções pendentes
    int execucoes_totais;           // Total de execuções
    struct Treino* prox;            // Próximo treino na fila
} Treino;
```

## Como Funciona a Fila Circular

O sistema utiliza uma **fila circular** para gerenciar os treinos de cada aluno:

1. **Adição de treinos**: Novos treinos são inseridos no final da fila
2. **Execução**: O treino atual (primeiro da fila) é executado
3. **Rotação**: Após a execução, o treino move para o final da fila
4. **Remoção**: Treinos são removidos apenas quando todas as execuções são completadas

### Exemplo Visual
```
Início: [Peito] → [Costas] → [Pernas] → [Peito]
                    ↑
               Treino atual

Após execução: [Costas] → [Pernas] → [Peito] → [Costas]
                   ↑
              Próximo treino
```

## Persistência de Dados

### Formato do arquivo `dados.txt`
```
ALUNO 1 João Silva
ALUNO 2 Maria Santos
ALUNO 3 Pedro Oliveira
```

### Formato do arquivo `treino.txt`
```
TREINO 1 Peito|3|5
TREINO 1 Costas|2|3
TREINO 2 Pernas|4|4
```

**Formato**: `TREINO [ID_ALUNO] [GRUPO_MUSCULAR]|[EXECUÇÕES_RESTANTES]|[EXECUÇÕES_TOTAIS]`

## Como Usar

### 1. Acesso do Instrutor
1. Execute o programa
2. Escolha opção "1 - Instrutor"
3. Cadastre alunos (opção 1)
4. Adicione treinos para os alunos (opção 3)

### 2. Acesso do Aluno
1. Execute o programa
2. Escolha opção "2 - Aluno"
3. Digite seu nome (deve estar cadastrado)
4. Visualize seus treinos (opção 1)
5. Marque treinos como concluídos (opção 2)

## Configurações

### Limites do Sistema
- **Máximo de alunos**: 100
- **Tamanho máximo do nome**: 50 caracteres
- **Tamanho máximo do grupo muscular**: 50 caracteres

### Arquivos de Dados
O sistema tenta salvar/carregar arquivos em duas localizações:
1. `../dados.txt` e `../treino.txt` (diretório pai)
2. `dados.txt` e `treino.txt` (diretório atual - fallback)

## Funcionalidades Detalhadas

### Busca de Alunos
- **Por nome**: Busca case-insensitive usando `strcasecmp()`
- **Por ID**: Busca direta por identificador único

### Controle de Execuções
- Cada treino tem um contador de execuções restantes
- O sistema automaticamente gerencia a rotação dos treinos
- Treinos completados são removidos automaticamente

### Validações
- Nomes de alunos duplicados não são permitidos
- IDs são gerados automaticamente de forma sequencial
- Verificação de existência de alunos antes de adicionar treinos

## Requisitos do Sistema

- **Compilador**: GCC ou equivalente com suporte a C99
- **Sistema Operacional**: Linux, macOS, Windows (com MinGW)
- **CMake**: Versão 3.10 ou superior (opcional)

## Notas de Implementação

- Uso de arrays globais para simplicidade de acesso
- Gerenciamento manual de memória para estruturas dinâmicas
- Validação de entrada básica para prevenir erros
- Sistema de fallback para localização de arquivos

## Contribuições

Este projeto é um sistema educacional demonstrando conceitos de:
- Estruturas de dados (filas circulares)
- Gerenciamento de arquivos em C
- Modularização de código
- Alocação dinâmica de memória

## Licença

Projeto desenvolvido para fins educacionais.
