#include <stdio.h>

#define LINHAS 10
#define COLUNAS 10
#define NAVIO 3
#define HABILIDADE 1

void posicionarNavio(int tabuleiro[LINHAS][COLUNAS], int x_inicial, int y_inicial, int comprimento, int direcao)
{
    for (int i = 0; i < comprimento; i++)
    {
        int x = x_inicial;
        int y = y_inicial;

        if (direcao == 0) // Horizontal
        {
            y += i;
        }
        else if (direcao == 1) // Vertical
        {
            x += i;
        }
        else if (direcao == 2) // Diagonal principal
        {
            x += i;
            y += i;
        }
        else if (direcao == 3) // Diagonal secundária
        {
            x += i;
            y -= i;
        }

        if (tabuleiro[x][y] != 0)
        {
            printf("\nErro: posição (%d, %d) já ocupada!\n", x, y);
            return;
        }
    }

    // Posicionando o navio
    for (int i = 0; i < comprimento; i++)
    {
        if (direcao == 0)
        {
            tabuleiro[x_inicial][y_inicial + i] = NAVIO;
        }
        else if (direcao == 1)
        {
            tabuleiro[x_inicial + i][y_inicial] = NAVIO;
        }
        else if (direcao == 2)
        {
            tabuleiro[x_inicial + i][y_inicial + i] = NAVIO;
        }
        else if (direcao == 3)
        {
            tabuleiro[x_inicial + i][y_inicial - i] = NAVIO;
        }
    }
}

void exibirTabuleiro(int tabuleiro[LINHAS][COLUNAS])
{
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void habilidadeCone(int habilidade[LINHAS][COLUNAS], int ponta_x, int ponta_y)
{
    ponta_x--;
    ponta_y--;

    if (ponta_x < 0 || ponta_x >= LINHAS - 2 || ponta_y < 2 || ponta_y >= COLUNAS - 2)
    {
        printf("Erro: posição fora dos limites para formar um cone corretamente!\n");
        return;
    }

    for (int altura = 0; altura < 3; altura++)
    {
        for (int i = -altura; i <= altura; i++)
        {
            habilidade[ponta_x + altura][ponta_y + i] = HABILIDADE;
        }
    }
}

void habilidadeCruz(int habilidade[LINHAS][COLUNAS], int centro_x, int centro_y)
{
    centro_x--;
    centro_y--;

    for (int i = 0; i < COLUNAS; i++)
    {
        habilidade[centro_x][i] = HABILIDADE;
    }
    for (int i = 0; i < LINHAS; i++)
    {
        habilidade[i][centro_y] = HABILIDADE;
    }
}

void habilidadeOctaedro(int habilidade[LINHAS][COLUNAS], int centro_x, int centro_y)
{
    centro_x--;
    centro_y--;

    
    habilidade[centro_x][centro_y] = HABILIDADE;

    int dx[5] = {0, -1, 1, 0, 0};
    int dy[5] = {0, 0, 0, -1, 1};


    for (int i = 0; i < 5; i++)
    {
        int nx = centro_x + dx[i];
        int ny = centro_y + dy[i];

        if (nx >= 0 && nx < LINHAS && ny >= 0 && ny < COLUNAS)
        {
            habilidade[nx][ny] = HABILIDADE;
        }
    }
}

void resetarMatriz(int matriz[LINHAS][COLUNAS])
{
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            matriz[i][j] = 0;
        }
    }
}

int main(){
    int tabuleiro[LINHAS][COLUNAS] = {0};

    int habilidade[LINHAS][COLUNAS] = {0};

    // Posicionando navios
    posicionarNavio(tabuleiro, 2, 1, 5, 0); // Horizontal
    posicionarNavio(tabuleiro, 5, 4, 3, 1); // Vertical
    posicionarNavio(tabuleiro, 6, 0, 4, 2); // Diagonal principal
    posicionarNavio(tabuleiro, 0, 9, 5, 3); // Diagonal secundária
    printf("Tabuleiro com os navios:\n");
    exibirTabuleiro(tabuleiro);

    // Habilidade em formato de cone
    habilidadeCone(habilidade, 1, 3);
    printf("\nHabilidade em cone:\n");
    exibirTabuleiro(habilidade);

    // Resetando a matriz de habilidade
    resetarMatriz(habilidade);

    // Habilidade em formato de cruz
    habilidadeCruz(habilidade, 5, 5);
    printf("\nHabilidade em cruz:\n");
    exibirTabuleiro(habilidade);

    // Resetando a matriz de habilidade
    resetarMatriz(habilidade);

    // Habilidade em formato de octaedro
    habilidadeOctaedro(habilidade, 3, 3);
    printf("\nHabilidade em octaedro:\n");
    exibirTabuleiro(habilidade);

    return 0;

}
