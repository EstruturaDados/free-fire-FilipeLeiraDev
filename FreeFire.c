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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== ESTRUTURAS DE DADOS ====================

// Struct do Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ==================== PROTÓTIPOS ====================

// --- VETOR ---
void inserirItemVetor(Item vetor[], int *total);
void removerItemVetor(Item vetor[], int *total);
void listarItensVetor(Item vetor[], int total);
void ordenarVetor(Item vetor[], int total);
int buscarSequencialVetor(Item vetor[], int total, char* nome, int *comparacoes);
int buscarBinariaVetor(Item vetor[], int total, char* nome, int *comparacoes);
void limparBuffer();

// --- LISTA ENCADEADA ---
No* inserirItemLista(No* lista);
No* removerItemLista(No* lista, char* nome);
void listarItensLista(No* lista);
int buscarSequencialLista(No* lista, char* nome, int *comparacoes);
void liberarLista(No* lista);

// ==================== FUNÇÕES AUXILIARES ====================

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ==================== IMPLEMENTAÇÃO VETOR ====================

void inserirItemVetor(Item vetor[], int *total) {
    if (*total >= 10) {
        printf("  [ERRO] Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("  Nome: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("  Tipo: ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    do {
        printf("  Quantidade: ");
        scanf("%d", &novo.quantidade);
        limparBuffer();
    } while (novo.quantidade <= 0);

    vetor[(*total)++] = novo;
    printf("  Item inserido com sucesso!\n");
}

void removerItemVetor(Item vetor[], int *total) {
    if (*total == 0) {
        printf("  [ERRO] Mochila vazia!\n");
        return;
    }

    char nome[30];
    printf("  Nome do item a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) {
            for (int j = i; j < *total - 1; j++) {
                vetor[j] = vetor[j + 1];
            }
            (*total)--;
            printf("  Item removido!\n");
            return;
        }
    }
    printf("  Item nao encontrado!\n");
}

void listarItensVetor(Item vetor[], int total) {
    printf("\n  === MOCHILA (VETOR) - %d/10 ITENS ===\n", total);
    if (total == 0) {
        printf("    [VAZIA]\n");
    } else {
        for (int i = 0; i < total; i++) {
            printf("    %d. [%s] %s - Qtd: %d\n",
                   i + 1, vetor[i].tipo, vetor[i].nome, vetor[i].quantidade);
        }
    }
}

void ordenarVetor(Item vetor[], int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                Item temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
    printf("  Itens ordenados por nome!\n");
}

int buscarSequencialVetor(Item vetor[], int total, char* nome, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < total; i++) {
        (*comparacoes)++;
        if (strcmp(vetor[i].nome, nome) == 0) {
            printf("  ENCONTRADO: [%s] %s - Qtd: %d\n",
                   vetor[i].tipo, vetor[i].nome, vetor[i].quantidade);
            return 1;
        }
    }
    return 0;
}

int buscarBinariaVetor(Item vetor[], int total, char* nome, int *comparacoes) {
    *comparacoes = 0;
    int esquerda = 0, direita = total - 1;

    while (esquerda <= direita) {
        (*comparacoes)++;
        int meio = esquerda + (direita - esquerda) / 2;
        int cmp = strcmp(vetor[meio].nome, nome);

        if (cmp == 0) {
            printf("  ENCONTRADO (BINARIA): [%s] %s - Qtd: %d\n",
                   vetor[meio].tipo, vetor[meio].nome, vetor[meio].quantidade);
            return 1;
        }
        if (cmp < 0) esquerda = meio + 1;
        else direita = meio - 1;
    }
    return 0;
}

// ==================== IMPLEMENTAÇÃO LISTA ENCADEADA ====================

No* inserirItemLista(No* lista) {
    No* novo = (No*) malloc(sizeof(No));
    if (!novo) {
        printf("  [ERRO] Falha na alocacao!\n");
        return lista;
    }

    printf("  Nome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

    printf("  Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';

    do {
        printf("  Quantidade: ");
        scanf("%d", &novo->dados.quantidade);
        limparBuffer();
    } while (novo->dados.quantidade <= 0);

    novo->proximo = lista;
    printf("  Item inserido no inicio da lista!\n");
    return novo;
}

No* removerItemLista(No* lista, char* nome) {
    No* atual = lista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                lista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("  Item removido da lista!\n");
            return lista;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("  Item nao encontrado na lista!\n");
    return lista;
}

void listarItensLista(No* lista) {
    printf("\n  === MOCHILA (LISTA ENCADEADA) ===\n");
    if (lista == NULL) {
        printf("    [VAZIA]\n");
        return;
    }

    int i = 1;
    No* atual = lista;
    while (atual != NULL) {
        printf("    %d. [%s] %s - Qtd: %d\n",
               i++, atual->dados.tipo, atual->dados.nome, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

int buscarSequencialLista(No* lista, char* nome, int *comparacoes) {
    *comparacoes = 0;
    No* atual = lista;
    while (atual != NULL) {
        (*comparacoes)++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("  ENCONTRADO: [%s] %s - Qtd: %d\n",
                   atual->dados.tipo, atual->dados.nome, atual->dados.quantidade);
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

void liberarLista(No* lista) {
    No* atual = lista;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    Item vetor[10];
    int totalVetor = 0;
    No* lista = NULL;
    int opcao, subopcao;
    char nomeBusca[30];
    int compSeq, compBin;

    printf("=== COMPARACAO: VETOR vs LISTA ENCADEADA ===\n\n");

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Mochila com VETOR\n");
        printf("2. Mochila com LISTA ENCADEADA\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        if (opcao == 1) {
            do {
                printf("\n--- VETOR ---\n");
                printf("1. Inserir | 2. Remover | 3. Listar\n");
                printf("4. Ordenar | 5. Busca Sequencial | 6. Busca Binaria\n");
                printf("0. Voltar\n");
                printf("Opcao: ");
                scanf("%d", &subopcao);
                limparBuffer();

                switch (subopcao) {
                    case 1: inserirItemVetor(vetor, &totalVetor); break;
                    case 2: removerItemVetor(vetor, &totalVetor); break;
                    case 3: listarItensVetor(vetor, totalVetor); break;
                    case 4: ordenarVetor(vetor, totalVetor); break;
                    case 5:
                        printf("Nome para busca sequencial: ");
                        fgets(nomeBusca, 30, stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        if (!buscarSequencialVetor(vetor, totalVetor, nomeBusca, &compSeq))
                            printf("  Nao encontrado!\n");
                        printf("  Comparacoes: %d\n", compSeq);
                        break;
                    case 6:
                        if (totalVetor == 0) {
                            printf("  Ordene primeiro!\n");
                            break;
                        }
                        ordenarVetor(vetor, totalVetor);
                        printf("Nome para busca binaria: ");
                        fgets(nomeBusca, 30, stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        if (!buscarBinariaVetor(vetor, totalVetor, nomeBusca, &compBin))
                            printf("  Nao encontrado!\n");
                        printf("  Comparacoes: %d\n", compBin);
                        break;
                    case 0: break;
                    default: printf("Opcao invalida!\n");
                }
            } while (subopcao != 0);

        } else if (opcao == 2) {
            do {
                printf("\n--- LISTA ENCADEADA ---\n");
                printf("1. Inserir | 2. Remover | 3. Listar | 4. Busca Sequencial\n");
                printf("0. Voltar\n");
                printf("Opcao: ");
                scanf("%d", &subopcao);
                limparBuffer();

                switch (subopcao) {
                    case 1: lista = inserirItemLista(lista); break;
                    case 2:
                        printf("Nome para remover: ");
                        fgets(nomeBusca, 30, stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        lista = removerItemLista(lista, nomeBusca);
                        break;
                    case 3: listarItensLista(lista); break;
                    case 4:
                        printf("Nome para busca: ");
                        fgets(nomeBusca, 30, stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        if (!buscarSequencialLista(lista, nomeBusca, &compSeq))
                            printf("  Nao encontrado!\n");
                        printf("  Comparacoes: %d\n", compSeq);
                        break;
                    case 0: break;
                    default: printf("Opcao invalida!\n");
                }
            } while (subopcao != 0);

        } else if (opcao == 0) {
            liberarLista(lista);
            printf("Sistema encerrado. Memoria liberada!\n");
        }

    } while (opcao != 0);

    return 0;
}