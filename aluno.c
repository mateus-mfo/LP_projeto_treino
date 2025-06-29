#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

// Array global para armazenar todos os alunos
Aluno alunos[100];
// Contador global do total de alunos cadastrados
int totalAlunos = 0;

/**
 * Busca um aluno pelo nome (case-insensitive)
 * @param nome Nome do aluno a ser buscado
 * @return Ponteiro para o aluno encontrado ou NULL se não encontrado
 */
Aluno* buscarAlunoPorNome(const char* nome) {
    // Percorre todos os alunos cadastrados
    for (int i = 0; i < totalAlunos; i++) {
        // Compara nomes ignorando maiúsculas/minúsculas
        if (strcasecmp(alunos[i].nome, nome) == 0) {
            return &alunos[i];  // Retorna ponteiro para o aluno encontrado
        }
    }
    return NULL;  // Aluno não encontrado
}

/**
 * Busca um aluno pelo ID
 * @param id ID do aluno a ser buscado
 * @return Ponteiro para o aluno encontrado ou NULL se não encontrado
 */
Aluno* buscarAlunoPorId(int id) {
    // Percorre todos os alunos cadastrados
    for (int i = 0; i < totalAlunos; i++) {
        if (alunos[i].id == id) {
            return &alunos[i];  // Retorna ponteiro para o aluno encontrado
        }
    }
    return NULL;  // Aluno não encontrado
}

/**
 * Lista todos os alunos cadastrados
 */
void listarAlunos() {
    printf("\n=== Lista de Alunos ===\n");
    // Percorre e exibe todos os alunos
    for (int i = 0; i < totalAlunos; i++) {
        printf("ID: %d - Nome: %s\n", alunos[i].id, alunos[i].nome);
    }
    printf("=======================\n");
}

/**
 * Carrega dados dos alunos do arquivo
 */
void carregarAlunos() {
    FILE *f = fopen("../dados.txt", "r");
    if (!f) {
        // Tenta carregar do diretório atual como fallback
        f = fopen("dados.txt", "r");
        if (!f) return;  // Arquivo não existe, não há dados para carregar
    }
    
    // Lê cada linha do arquivo no formato "ALUNO ID NOME"
    while (fscanf(f, "ALUNO %d %[^\n]\n", &alunos[totalAlunos].id, alunos[totalAlunos].nome) == 2) {
        totalAlunos++;  // Incrementa contador de alunos
    }
    fclose(f);
}

/**
 * Salva dados dos alunos no arquivo
 */
void salvarAlunos() {
    FILE *f = fopen("../dados.txt", "w");
    if (!f) {
        // Tenta salvar no diretório atual como fallback
        f = fopen("dados.txt", "w");
        if (!f) {
            printf("Erro: Nao foi possivel salvar os dados dos alunos!\n");
            return;
        }
    }
    
    // Escreve cada aluno no formato "ALUNO ID NOME"
    for (int i = 0; i < totalAlunos; i++) {
        fprintf(f, "ALUNO %d %s\n", alunos[i].id, alunos[i].nome);
    }
    fclose(f);
}

/**
 * Adiciona um novo aluno ao sistema
 */
void adicionarAluno() {
    Aluno novo;
    char nome_temp[50];
    
    printf("Nome do aluno: ");
    fgets(nome_temp, 50, stdin);
    nome_temp[strcspn(nome_temp, "\n")] = 0;  // Remove quebra de linha
    
    // Verifica se já existe um aluno com este nome
    if (buscarAlunoPorNome(nome_temp) != NULL) {
        printf("Erro: Ja existe um aluno com o nome '%s'!\n", nome_temp);
        return;
    }
    
    // Gera ID automático (sequencial)
    novo.id = (totalAlunos == 0) ? 1 : alunos[totalAlunos - 1].id + 1;
    strcpy(novo.nome, nome_temp);
    
    // Adiciona o novo aluno ao array
    alunos[totalAlunos++] = novo;
    salvarAlunos();  // Salva automaticamente
    
    printf("Aluno '%s' cadastrado com sucesso! ID atribuido: %d\n", novo.nome, novo.id);
}