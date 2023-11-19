#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um veículo
typedef struct Veiculo {
    char proprietario[50];
    char combustivel[20];
    char modelo[50];
    char cor[20];
    char chassi[20];
    int ano;
    char placa[8];
    struct Veiculo* proximo;
} Veiculo;

// Função para inicializar uma lista vazia
Veiculo* inicializarLista() {
    return NULL;
}

// Função para adicionar um novo veículo à lista
Veiculo* adicionarVeiculo(Veiculo* lista, char proprietario[], char combustivel[], char modelo[], char cor[], char chassi[], int ano, char placa[]) {
    Veiculo* novoVeiculo = (Veiculo*)malloc(sizeof(Veiculo));
    strcpy(novoVeiculo->proprietario, proprietario);
    strcpy(novoVeiculo->combustivel, combustivel);
    strcpy(novoVeiculo->modelo, modelo);
    strcpy(novoVeiculo->cor, cor);
    strcpy(novoVeiculo->chassi, chassi);
    novoVeiculo->ano = ano;
    strcpy(novoVeiculo->placa, placa);
    novoVeiculo->proximo = lista;
    return novoVeiculo;
}

// Função para listar proprietários de carros do ano 2010 ou posterior e movidos a diesel
void listarProprietariosDiesel2010OuPosterior(Veiculo* lista) {
    printf("Proprietários de carros do ano 2010 ou posterior e movidos a diesel:\n");
    while (lista != NULL) {
        if (lista->ano >= 2010 && strcmp(lista->combustivel, "diesel") == 0) {
            printf("%s\n", lista->proprietario);
        }
        lista = lista->proximo;
    }
}

// Função para listar placas que começam com a letra J e terminam com 0, 2, 4 ou 7, com seus respectivos proprietários
void listarPlacasComLetraJ(Veiculo* lista) {
    printf("Placas que começam com a letra J e terminam com 0, 2, 4 ou 7, com seus respectivos proprietários:\n");
    while (lista != NULL) {
        if (lista->placa[0] == 'J' &&
            (lista->placa[7] == '0' || lista->placa[7] == '2' || lista->placa[7] == '4' || lista->placa[7] == '7')) {
            printf("Placa: %s - Proprietário: %s\n", lista->placa, lista->proprietario);
        }
        lista = lista->proximo;
    }
}

// Função para listar modelo e cor de veículos com placas que têm como segunda letra uma vogal e cuja soma dos valores numéricos é par
void listarModeloCorPlacasVogalSomaPar(Veiculo* lista) {
    printf("Modelo e cor de veículos com placas que têm como segunda letra uma vogal e cuja soma dos valores numéricos é par:\n");
    while (lista != NULL) {
        if (strchr("AEIOUaeiou", lista->placa[1]) != NULL) {
            int somaNumeros = 0;
            for (int i = 0; i < 7; i++) {
                if (isdigit(lista->placa[i])) {
                    somaNumeros += lista->placa[i] - '0';
                }
            }
            if (somaNumeros % 2 == 0) {
                printf("Modelo: %s - Cor: %s\n", lista->modelo, lista->cor);
            }
        }
        lista = lista->proximo;
    }
}

// Função para realizar a troca de proprietário com fornecimento do número do chassi para carros com placas sem dígitos iguais a zero
void trocarProprietarioPorChassi(Veiculo* lista, char chassi[], char novoProprietario[]) {
    while (lista != NULL) {
        if (strcmp(lista->chassi, chassi) == 0 && strcspn(lista->placa, "0") == strlen(lista->placa)) {
            strcpy(lista->proprietario, novoProprietario);
            printf("Proprietário trocado com sucesso!\n");
            return;
        }
        lista = lista->proximo;
    }
    printf("Carro não encontrado ou placa contém dígitos iguais a zero.\n");
}

// Função para liberar a memória alocada para a lista
void liberarLista(Veiculo* lista) {
    while (lista != NULL) {
        Veiculo* proximo = lista->proximo;
        free(lista);
        lista = proximo;
    }
}

// Função principal
int main() {
    Veiculo* lista = inicializarLista();
    char opcao;

    do {
        printf("\nEscolha uma opção:\n");
        printf("1. Adicionar veículo\n");
        printf("2. Listar proprietários de carros do ano 2010 ou posterior e movidos a diesel\n");
        printf("3. Listar placas que começam com a letra J e terminam com 0, 2, 4 ou 7\n");
        printf("4. Listar modelo e cor de veículos com placas que têm como segunda letra uma vogal e cuja soma dos valores numéricos é par\n");
        printf("5. Trocar proprietário por chassi para carros com placas sem dígitos iguais a zero\n");
        printf("0. Sair\n");
        scanf(" %c", &opcao);

        switch (opcao) {
            case '1': {
                char proprietario[50], combustivel[20], modelo[50], cor[20], chassi[20], placa[8];
                int ano;

                printf("Digite o nome do proprietário: ");
                scanf("%s", proprietario);

                printf("Digite o tipo de combustível (álcool, diesel ou gasolina): ");
                scanf("%s", combustivel);

                printf("Digite o modelo do veículo: ");
                scanf("%s", modelo);

                printf("Digite a cor do veículo: ");
                scanf("%s", cor);

                printf("Digite o número do chassi: ");
                scanf("%s", chassi);

                printf("Digite o ano do veículo: ");
                scanf("%d", &ano);

                printf("Digite a placa do veículo: ");
                scanf("%s", placa);

                lista = adicionarVeiculo(lista, proprietario, combustivel, modelo, cor, chassi, ano, placa);
                break;
            }
            case '2':
                listarProprietariosDiesel2010OuPosterior(lista);
                break;
            case '3':
                listarPlacasComLetraJ(lista);
                break;
            case '4':
                listarModeloCorPlacasVogalSomaPar(lista);
                break;
            case '5': {
                char chassi[20], novoProprietario[50];
                printf("Digite o número do chassi: ");
                scanf("%s", chassi);

                printf("Digite o novo proprietário: ");
                scanf("%s", novoProprietario);

                trocarProprietarioPorChassi(lista, chassi, novoProprietario);
                break;
            }
            case '0':
                printf("Saindo do programa. Até mais!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != '0');

    // Liberar a memória alocada para a lista antes de encerrar o programa
    liberarLista(lista);

    return 0;
}
