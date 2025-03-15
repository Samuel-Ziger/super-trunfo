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
    scanf(" %[^\n]", nova.estado);
    
    printf("Código da cidade: ");
    scanf("%d", &nova.codigo);
    
    printf("Nome da cidade: ");
    scanf(" %[^\n]", nova.nome);
    
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
        printf("\n[Carta %d]\n", i + 1);
        printf("Estado: %s\n", cartas[i].estado);
        printf("Código: %d\n", cartas[i].codigo);
        printf("Cidade: %s\n", cartas[i].nome);
        printf("População: %ld habitantes\n", cartas[i].populacao);
        printf("PIB: %.2f bilhões\n", cartas[i].pib);
        printf("Área: %.2f km²\n", cartas[i].area);
        printf("Pontos turísticos: %d\n", cartas[i].pontos_turisticos);
        printf("Densidade populacional: %.2f hab/km²\n", cartas[i].densidade);
        printf("PIB per capita: %.2f mil reais\n", cartas[i].pib_per_capita);
    }
}

// Função para salvar cartas em um arquivo
void salvar_cartas(Carta cartas[], int quantidade) {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "wb");
    if (arquivo == NULL) {
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
    if (arquivo == NULL) {
        printf("Nenhum arquivo salvo encontrado.\n");
        return;
    }

    fread(quantidade, sizeof(int), 1, arquivo);
    fread(cartas, sizeof(Carta), *quantidade, arquivo);
    fclose(arquivo);
    printf("\nCartas carregadas com sucesso!\n");
}

// Função para comparar duas cartas em uma batalha
void batalha(Carta cartas[], int quantidade) {
    if (quantidade < 2) {
        printf("\nÉ necessário pelo menos duas cartas para iniciar uma batalha!\n");
        return;
    }

    int idx1, idx2, opcao;
    printf("\n--- Modo Super Trunfo ---\n");
    exibir_cartas(cartas, quantidade);

    printf("\nEscolha a primeira carta (1-%d): ", quantidade);
    scanf("%d", &idx1);
    printf("Escolha a segunda carta (1-%d): ", quantidade);
    scanf("%d", &idx2);

    if (idx1 < 1 || idx1 > quantidade || idx2 < 1 || idx2 > quantidade || idx1 == idx2) {
        printf("Escolha inválida!\n");
        return;
    }

    Carta c1 = cartas[idx1 - 1];
    Carta c2 = cartas[idx2 - 1];

    printf("\nEscolha um atributo para comparar:\n");
    printf("1. População\n2. PIB\n3. Área\n4. Pontos turísticos\n5. Densidade populacional\n6. PIB per capita\n");
    printf("Digite a opção: ");
    scanf("%d", &opcao);

    double valor1, valor2;
    switch (opcao) {
        case 1: valor1 = c1.populacao; valor2 = c2.populacao; break;
        case 2: valor1 = c1.pib; valor2 = c2.pib; break;
        case 3: valor1 = c1.area; valor2 = c2.area; break;
        case 4: valor1 = c1.pontos_turisticos; valor2 = c2.pontos_turisticos; break;
        case 5: valor1 = c1.densidade; valor2 = c2.densidade; break;
        case 6: valor1 = c1.pib_per_capita; valor2 = c2.pib_per_capita; break;
        default:
            printf("Opção inválida!\n");
            return;
    }

    printf("\nResultado da batalha:\n");
    printf("%s: %.2f\n", c1.nome, valor1);
    printf("%s: %.2f\n", c2.nome, valor2);

    if (valor1 > valor2) {
        printf("\n%s venceu!\n", c1.nome);
    } else if (valor1 < valor2) {
        printf("\n%s venceu!\n", c2.nome);
    } else {
        printf("\nEmpate!\n");
    }
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
        printf("3. Modo Super Trunfo (Batalha)\n");
        printf("4. Salvar e sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrar_carta(cartas, &quantidade); break;
            case 2: exibir_cartas(cartas, quantidade); break;
            case 3: batalha(cartas, quantidade); break;
            case 4: salvar_cartas(cartas, quantidade); printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 4);

    return 0;
}
