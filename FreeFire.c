#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

//int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    //return 0;
//}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
/*
 * Programa: Sistema de Inventário - Mochila de Loot
 * Disciplina: Programação em C
 * Descrição: Gerencia até 10 itens com cadastro, remoção, listagem e busca sequencial.
 */

/*
 * Programa: Comparação Vetor vs Lista Encadeada - Mochila de Loot
 * Disciplina: Estruturas de Dados em C
 * Descrição: Implementa duas mochilas (vetor e lista encadeada) com inserção,
 *            remoção, listagem, busca sequencial, ordenação (vetor) e busca binária.
 *            Exibe número de comparações em cada busca.
 */
/*
 * Programa: TORRE DE FUGA - Desafio Final
 * Disciplina: Estruturas de Dados em C
 * Descrição: Sistema de montagem da torre com 3 algoritmos de ordenação,
 *            busca binária, medição de tempo e comparações.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==================== ESTRUTURA DE DADOS ====================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // 1 (baixa) a 10 (alta)
} Componente;

// Capacidade máxima
#define MAX_COMP 20

// ==================== PROTÓTIPOS ====================
void cadastrarComponentes(Componente v[], int *n);
void mostrarComponentes(Componente v[], int n);

// Algoritmos de ordenação
void bubbleSortNome(Componente v[], int n, int *comparacoes);
void insertionSortTipo(Componente v[], int n, int *comparacoes);
void selectionSortPrioridade(Componente v[], int n, int *comparacoes);

// Busca binária
int buscaBinariaPorNome(Componente v[], int n, char* chave, int *comparacoes);

// Função genérica para medir tempo
double medirTempo(void (*algoritmo)(Componente[], int, int*), Componente v[], int n, int *comparacoes);

void limparBuffer();

// ==================== FUNÇÃO PRINCIPAL ====================
int main() {
    Componente componentes[MAX_COMP];
    int total = 0;
    int opcao;
    int comp = 0;
    double tempo;

    printf("=== TORRE DE FUGA - MONTAGEM ESTRATEGICA ===\n\n");

    // Cadastro inicial
    cadastrarComponentes(componentes, &total);

    do {
        printf("\n--- MENU DE ESTRATEGIA ---\n");
        printf("1. Ordenar por NOME (Bubble Sort)\n");
        printf("2. Ordenar por TIPO (Insertion Sort)\n");
        printf("3. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("4. Buscar componente-chave (Busca Binaria)\n");
        printf("5. Mostrar componentes atuais\n");
        printf("0. Finalizar montagem e fugir!\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                tempo = medirTempo(bubbleSortNome, componentes, total, &comp);
                printf("Ordenacao por NOME concluida!\n");
                printf("  Comparacoes: %d | Tempo: %.6f segundos\n", comp, tempo);
                mostrarComponentes(componentes, total);
                break;

            case 2:
                tempo = medirTempo(insertionSortTipo, componentes, total, &comp);
                printf("Ordenacao por TIPO concluida!\n");
                printf("  Comparacoes: %d | Tempo: %.6f segundos\n", comp, tempo);
                mostrarComponentes(componentes, total);
                break;

            case 3:
                tempo = medirTempo(selectionSortPrioridade, componentes, total, &comp);
                printf("Ordenacao por PRIORIDADE concluida!\n");
                printf("  Comparacoes: %d | Tempo: %.6f segundos\n", comp, tempo);
                mostrarComponentes(componentes, total);
                break;

            case 4: {
                char chave[30];
                printf("Nome do componente-chave: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = '\0';

                // Garante que está ordenado por nome
                int comp_dummy;
                bubbleSortNome(componentes, total, &comp_dummy);

                int comp_bin = 0;
                int encontrado = buscaBinariaPorNome(componentes, total, chave, &comp_bin);

                if (encontrado) {
                    printf("COMPONENTE-CHAVE ENCONTRADO!\n");
                    printf("  Comparacoes na busca: %d\n", comp_bin);
                    printf("TORRE ATIVADA! Fuga iniciada...\n");
                } else {
                    printf("Componente '%s' nao encontrado. Fuga comprometida!\n", chave);
                }
                break;
            }

            case 5:
                mostrarComponentes(componentes, total);
                break;

            case 0:
                printf("\nFUGA CONCLUIDA COM SUCESSO!\n");
                printf("Todos os componentes foram organizados.\n");
                printf("A torre esta pronta. Boa sorte na proxima partida!\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// ==================== CADASTRO ====================
void cadastrarComponentes(Componente v[], int *n) {
    printf("=== CADASTRO DE COMPONENTES DA TORRE ===\n");
    printf("Quantos componentes (max %d)? ", MAX_COMP);
    scanf("%d", n);
    limparBuffer();

    if (*n <= 0 || *n > MAX_COMP) {
        printf("Numero invalido! Usando 5 componentes padrao.\n");
        *n = 5;
    }

    for (int i = 0; i < *n; i++) {
        printf("\n--- Componente %d ---\n", i + 1);
        printf("Nome: ");
        fgets(v[i].nome, 30, stdin);
        v[i].nome[strcspn(v[i].nome, "\n")] = '\0';

        printf("Tipo (controle/suporte/propulsao): ");
        fgets(v[i].tipo, 20, stdin);
        v[i].tipo[strcspn(v[i].tipo, "\n")] = '\0';

        do {
            printf("Prioridade (1 a 10): ");
            scanf("%d", &v[i].prioridade);
            limparBuffer();
        } while (v[i].prioridade < 1 || v[i].prioridade > 10);
    }
    printf("\nCadastro concluido!\n");
}

// ==================== EXIBIÇÃO ====================
void mostrarComponentes(Componente v[], int n) {
    printf("\n=== COMPONENTES DA TORRE (%d) ===\n", n);
    for (int i = 0; i < n; i++) {
        printf("  [%02d] %-15s | %-12s | Prior: %2d\n",
               i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

// ==================== BUBBLE SORT (NOME) ====================
void bubbleSortNome(Componente v[], int n, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// ==================== INSERTION SORT (TIPO) ====================
void insertionSortTipo(Componente v[], int n, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(v[j].tipo, chave.tipo) > 0) {
                v[j + 1] = v[j];
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
    }
}

// ==================== SELECTION SORT (PRIORIDADE) ====================
void selectionSortPrioridade(Componente v[], int n, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (v[j].prioridade > v[max_idx].prioridade) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            Componente temp = v[i];
            v[i] = v[max_idx];
            v[max_idx] = temp;
        }
    }
}

// ==================== BUSCA BINÁRIA (NOME) ====================
int buscaBinariaPorNome(Componente v[], int n, char* chave, int *comparacoes) {
    *comparacoes = 0;
    int esquerda = 0, direita = n - 1;

    while (esquerda <= direita) {
        (*comparacoes)++;
        int meio = esquerda + (direita - esquerda) / 2;
        int cmp = strcmp(v[meio].nome, chave);

        if (cmp == 0) {
            printf("  ENCONTRADO: [%s] %s - Prior: %d\n",
                   v[meio].tipo, v[meio].nome, v[meio].prioridade);
            return 1;
        }
        if (cmp < 0) esquerda = meio + 1;
        else direita = meio - 1;
    }
    return 0;
}

// ==================== MEDIÇÃO DE TEMPO ====================
double medirTempo(void (*algoritmo)(Componente[], int, int*), Componente v[], int n, int *comparacoes) {
    clock_t inicio = clock();
    algoritmo(v, n, comparacoes);
    clock_t fim = clock();
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

// ==================== LIMPAR BUFFER ====================
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}