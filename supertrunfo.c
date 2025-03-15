#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARTAS 50  
#define ARQUIVO_DADOS "cartas.bin"  

typedef struct {
    char estado[30];
    int codigo;
    char nome[50];
    long int populacao;
    double pib;
    double area;
    int pontos_turisticos;
    double densidade;
    double pib_per_capita;
} Carta;

// Função para calcular densidade populacional e PIB per capita
void calcular_propriedades(Carta *c) {
    c->densidade = (c->area > 0) ? c->populacao / c->area : 0;
    c->pib_per_capita = (c->populacao > 0) ? c->pib / c->populacao : 0;
}

// Função para cadastrar uma nova carta
void cadastrar_carta(Carta cartas[], int *quantidade) {
    if (*quantidade >= MAX_CARTAS) {
        printf("Limite de cartas atingido!\n");
        return;
    }

    Carta nova;
    printf("\n--- Cadastro de Carta ---\n");
    printf("Estado: ");
    scanf(" %[^"]s", nova.estado);
    
    printf("Código da cidade: ");
    scanf("%d", &nova.codigo);
    
    printf("Nome da cidade: ");
    scanf(" %[^"]s", nova.nome);
    
    printf("População: ");
    scanf("%ld", &nova.populacao);
    
    printf("PIB (em bilhões): ");
    scanf("%lf", &nova.pib);
    
    printf("Área (km²): ");
    scanf("%lf", &nova.area);
    
    printf("Número de pontos turísticos: ");
    scanf("%d", &nova.pontos_turisticos);

    calcular_propriedades(&nova);
    cartas[*quantidade] = nova;
    (*quantidade)++;
    printf("\nCarta cadastrada com sucesso!\n");
}

// Função para exibir todas as cartas cadastradas
void exibir_cartas(Carta cartas[], int quantidade) {
    if (quantidade == 0) {
        printf("\nNenhuma carta cadastrada ainda!\n");
        return;
    }

    printf("\n--- Cartas Cadastradas ---\n");
    for (int i = 0; i < quantidade; i++) {
        printf("\n[Carta %d] - %s (%s)\n", i + 1, cartas[i].nome, cartas[i].estado);
        printf("Código: %d\nPopulação: %ld hab\nPIB: %.2f bilhões\nÁrea: %.2f km²\n", 
               cartas[i].codigo, cartas[i].populacao, cartas[i].pib, cartas[i].area);
        printf("Pontos turísticos: %d\nDensidade populacional: %.2f hab/km²\nPIB per capita: %.2f mil reais\n", 
               cartas[i].pontos_turisticos, cartas[i].densidade, cartas[i].pib_per_capita);
    }
}

// Função para buscar uma carta por nome ou código
void buscar_carta(Carta cartas[], int quantidade) {
    int codigo;
    char nome[50];
    printf("\nDigite o código da cidade ou o nome para buscar: ");
    scanf(" %[^"]s", nome);
    
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(cartas[i].nome, nome) == 0 || cartas[i].codigo == atoi(nome)) {
            printf("\n[Carta encontrada] - %s (%s)\n", cartas[i].nome, cartas[i].estado);
            return;
        }
    }
    printf("\nCarta não encontrada.\n");
}

// Função para salvar cartas em um arquivo
void salvar_cartas(Carta cartas[], int quantidade) {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "wb");
    if (!arquivo) {
        printf("Erro ao salvar os dados!\n");
        return;
    }
    fwrite(&quantidade, sizeof(int), 1, arquivo);
    fwrite(cartas, sizeof(Carta), quantidade, arquivo);
    fclose(arquivo);
    printf("\nCartas salvas com sucesso!\n");
}

// Função para carregar cartas do arquivo
void carregar_cartas(Carta cartas[], int *quantidade) {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "rb");
    if (!arquivo) {
        printf("Nenhum arquivo salvo encontrado.\n");
        return;
    }
    fread(quantidade, sizeof(int), 1, arquivo);
    fread(cartas, sizeof(Carta), *quantidade, arquivo);
    fclose(arquivo);
    printf("\nCartas carregadas com sucesso!\n");
}

// Função principal
int main() {
    Carta cartas[MAX_CARTAS];
    int quantidade = 0;
    int opcao;

    carregar_cartas(cartas, &quantidade);

    do {
        printf("\n===== Super Trunfo - Cidades =====\n");
        printf("1. Cadastrar nova carta\n");
        printf("2. Exibir cartas cadastradas\n");
        printf("3. Buscar carta\n");
        printf("4. Salvar e sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrar_carta(cartas, &quantidade); break;
            case 2: exibir_cartas(cartas, quantidade); break;
            case 3: buscar_carta(cartas, quantidade); break;
            case 4: salvar_cartas(cartas, quantidade); printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 4);

    return 0;
}
