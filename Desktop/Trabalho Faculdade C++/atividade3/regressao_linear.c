#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    float y;
} Ponto;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <nome_do_arquivo.csv>\n", argv[0]);
        return 1;
    }

    // Abrir o arquivo CSV
    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return 1;
    }

    // Contar quantos registros existem no arquivo
    int numRegistros = 0;
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        numRegistros++;
    }
    rewind(arquivo);  // Voltar ao início do arquivo

    // Alocar memória para o array de pontos
    Ponto *pontos = (Ponto *)malloc(numRegistros * sizeof(Ponto));
    if (pontos == NULL) {
        printf("Erro na alocação de memória.\n");
        return 1;
    }

    // Ler os pontos do arquivo e calcular somas
    int somaX = 0;
    float somaY = 0.0;
    for (int i = 0; i < numRegistros; i++) {
        fscanf(arquivo, "%d,%f", &pontos[i].x, &pontos[i].y);
        somaX += pontos[i].x;
        somaY += pontos[i].y;
    }
    fclose(arquivo);

    // Calcular a média de x e y
    float mediaX = (float)somaX / numRegistros;
    float mediaY = somaY / numRegistros;

    // Calcular a inclinação e o coeficiente linear
    float numerador = 0.0, denominador = 0.0;
    for (int i = 0; i < numRegistros; i++) {
        numerador += (pontos[i].x - mediaX) * (pontos[i].y - mediaY);
        denominador += (pontos[i].x - mediaX) * (pontos[i].x - mediaX);
    }
    float coeficienteAngular = numerador / denominador;
    float coeficienteLinear = mediaY - coeficienteAngular * mediaX;

    // Exibir a equação da regressão linear
    printf("Saída: y = %.2fx + %.2f\n", coeficienteAngular, coeficienteLinear);

    // Liberar a memória alocada
    free(pontos);

    return 0;
}
