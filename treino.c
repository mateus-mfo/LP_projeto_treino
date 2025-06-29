#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treino.h"
#include "aluno.h"

// Array de ponteiros para as filas circulares de treino
// Cada posição corresponde ao ID de um aluno
Treino* filaTreinos[100] = { NULL };

/**
 * Adiciona um grupo de treinos para um aluno específico
 * O instrutor define quantas vezes cada treino deve ser executado
 */
void adicionarGrupoDeTreinos() {
    char nome[50];
    int qtd_treinos, execucoes;
    
    printf("Nome do aluno: ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = 0;  // Remove quebra de linha
    
    // Busca o aluno pelo nome
    Aluno* a = buscarAlunoPorNome(nome);
    if (!a) {
        printf("Aluno '%s' nao encontrado!\n", nome);
        printf("Alunos disponiveis:\n");
        listarAlunos();
        return;
    }
    
    printf("Quantos tipos de treino deseja adicionar para %s? ", a->nome);
    scanf("%d", &qtd_treinos); 
    getchar();  // Consome quebra de linha
    
    printf("Quantas vezes cada treino deve ser executado? ");
    scanf("%d", &execucoes); 
    getchar();  // Consome quebra de linha
    
    // Cria cada treino e adiciona à fila circular
    for (int i = 0; i < qtd_treinos; i++) {
        Treino* novo = (Treino*)malloc(sizeof(Treino));
        novo->alunoId = a->id;
        novo->execucoes_restantes = execucoes;
        novo->execucoes_totais = execucoes;
        
        printf("Grupo muscular do treino %d: ", i + 1);
        fgets(novo->grupo_muscular, 50, stdin);
        novo->grupo_muscular[strcspn(novo->grupo_muscular, "\n")] = 0;
        
        novo->prox = NULL;
        
        // Se é o primeiro treino da fila
        if (filaTreinos[a->id] == NULL) {
            filaTreinos[a->id] = novo;
            novo->prox = novo;  // Aponta para si mesmo (circular)
        } else {
            // Encontra o último nó da fila circular
            Treino* atual = filaTreinos[a->id];
            while (atual->prox != filaTreinos[a->id]) {
                atual = atual->prox;
            }
            // Insere o novo treino no final da fila
            atual->prox = novo;
            novo->prox = filaTreinos[a->id];
        }
    }
    
    printf("%d treinos adicionados para %s!\n", qtd_treinos, a->nome);
    printf("Cada treino deve ser executado %d vezes.\n", execucoes);
    salvarTreinos();  // Salva automaticamente
}

/**
 * Lista todos os treinos de um aluno específico
 * Mostra o progresso de cada treino (execuções restantes)
 */
void listarTreinosDoAluno(int alunoId) {
    Treino* atual = filaTreinos[alunoId];
    if (!atual) {
        printf("Sem treinos encontrados para este aluno.\n");
        return;
    }
    
    Aluno* aluno = buscarAlunoPorId(alunoId);
    printf("\n=== Fila de treinos de %s ===\n", aluno ? aluno->nome : "Aluno");
    
    Treino* inicio = atual;
    int contador = 1;
    
    // Percorre a fila circular exibindo cada treino
    do {
        printf("%d. %s (Restam: %d/%d execucoes)\n", 
               contador++, 
               atual->grupo_muscular, 
               atual->execucoes_restantes,
               atual->execucoes_totais);
        atual = atual->prox;
    } while (atual != inicio);
    
    printf("===============================\n");
}

/**
 * Marca o treino atual como feito
 * Move o treino para o final da fila ou remove se completou todas as execuções
 */
void marcarTreinoComoFeito(int alunoId) {
    Treino* fila = filaTreinos[alunoId];
    if (!fila) {
        printf("Nenhum treino para marcar como feito.\n");
        return;
    }
    
    printf("Treino concluido: %s\n", fila->grupo_muscular);
    
    // Decrementa o número de execuções restantes
    fila->execucoes_restantes--;
    
    // Se ainda restam execuções, move para o final da fila (rotação)
    if (fila->execucoes_restantes > 0) {
        printf("Ainda restam %d execucoes deste treino.\n", fila->execucoes_restantes);
        
        // Se há mais de um treino na fila, faz a rotação
        if (fila->prox != fila) {
            filaTreinos[alunoId] = fila->prox;  // Próximo treino vira o primeiro
            printf("Proximo treino: %s\n", filaTreinos[alunoId]->grupo_muscular);
        } else {
            printf("Continue com o mesmo treino.\n");
        }
    } else {
        // Treino completou todas as execuções, remove da fila
        printf("Treino '%s' completamente finalizado!\n", fila->grupo_muscular);
        
        // Se é o único treino na fila
        if (fila->prox == fila) {
            free(fila);
            filaTreinos[alunoId] = NULL;
            printf("Parabens! Voce completou todos os treinos!\n");
            printf("Procure seu instrutor para novos treinos.\n");
        } else {
            // Encontra o último nó para atualizar o ponteiro
            Treino* ultimo = fila;
            while (ultimo->prox != fila) {
                ultimo = ultimo->prox;
            }
            // Remove o treino atual da fila
            ultimo->prox = fila->prox;
            filaTreinos[alunoId] = fila->prox;
            free(fila);
            printf("Proximo treino: %s\n", filaTreinos[alunoId]->grupo_muscular);
        }
    }
    
    salvarTreinos();  // Salva automaticamente
}

/**
 * Carrega os treinos do arquivo
 */
void carregarTreinos() {
    FILE *f = fopen("../treino.txt", "r");
    if (!f) {
        // Tenta carregar do diretório atual como fallback
        f = fopen("treino.txt", "r");
        if (!f) return;  // Arquivo não existe
    }
    
    int alunoId, execucoes_restantes, execucoes_totais;
    char grupo[50];
    
    // Limpa as filas existentes antes de carregar
    for (int i = 0; i < 100; i++) {
        while (filaTreinos[i] != NULL) {
            Treino* temp = filaTreinos[i];
            if (temp->prox == temp) {
                // Único elemento na fila
                filaTreinos[i] = NULL;
                free(temp);
                break;
            } else {
                // Remove o primeiro elemento da fila circular
                Treino* ultimo = temp;
                while (ultimo->prox != filaTreinos[i]) {
                    ultimo = ultimo->prox;
                }
                ultimo->prox = temp->prox;
                filaTreinos[i] = temp->prox;
                free(temp);
            }
        }
    }
    
    // Carrega os treinos do arquivo no formato:
    // TREINO alunoId grupo_muscular execucoes_restantes execucoes_totais
    while (fscanf(f, "TREINO %d %[^|]|%d|%d\n", &alunoId, grupo, &execucoes_restantes, &execucoes_totais) == 4) {
        Treino* novo = (Treino*)malloc(sizeof(Treino));
        novo->alunoId = alunoId;
        strcpy(novo->grupo_muscular, grupo);
        novo->execucoes_restantes = execucoes_restantes;
        novo->execucoes_totais = execucoes_totais;
        novo->prox = NULL;
        
        // Adiciona à fila circular
        if (filaTreinos[alunoId] == NULL) {
            filaTreinos[alunoId] = novo;
            novo->prox = novo;
        } else {
            Treino* atual = filaTreinos[alunoId];
            while (atual->prox != filaTreinos[alunoId]) {
                atual = atual->prox;
            }
            atual->prox = novo;
            novo->prox = filaTreinos[alunoId];
        }
    }
    fclose(f);
}

/**
 * Salva os treinos no arquivo
 */
void salvarTreinos() {
    FILE *f = fopen("../treino.txt", "w");
    if (!f) {
        // Tenta salvar no diretório atual como fallback
        f = fopen("treino.txt", "w");
        if (!f) {
            printf("Erro: Nao foi possivel salvar os dados dos treinos!\n");
            return;
        }
    }
    
    // Percorre todas as filas de treino
    for (int i = 0; i < 100; i++) {
        if (filaTreinos[i] != NULL) {
            Treino* atual = filaTreinos[i];
            Treino* inicio = atual;
            
            // Percorre a fila circular salvando cada treino
            do {
                fprintf(f, "TREINO %d %s|%d|%d\n", 
                       atual->alunoId, 
                       atual->grupo_muscular,
                       atual->execucoes_restantes,
                       atual->execucoes_totais);
                atual = atual->prox;
            } while (atual != inicio);
        }
    }
    fclose(f);
}