#include <stdio.h>
#include <stdlib.h>

void mostrarTabuleiro(char jogo[3][3]);
int checkarJogo(char jogo[3][3], int index);
int varrerTabuleiro(char jogo[3][3], int i, int j, int iteradori, int iteradorj);

int main () 
{   
    int check;
    system("cls||clear");
    char jogo[3][3] = {"   ", "   ", "   "};
    mostrarTabuleiro(jogo);
    char cpos1;
    int pos1;
    int pos2;
    printf("Pressione Qualquer tecla para iniciar\n");

    for (int i = 0; i < 9; i++) {
        //getchar();
        system("cls||clear");
        mostrarTabuleiro(jogo);
        printf("Jogador %d informe sua jogada(A1): ", i % 2 + 1);
        scanf("%c%d", &cpos1, &pos2);
        getchar();
        pos1 = cpos1 - 64;
        if (jogo[pos1 - 1][pos2 - 1] == ' ') {
            jogo[pos1 - 1][pos2 - 1] = i % 2 ? 'O' : 'X';
            //printf("%d-%d\n", pos1, pos2);
        }
        else{
            printf("Jogada invalida. Tente novamente!");
            i--;
        }
        if (i >= 4) {
            check = checkarJogo(jogo, i);
            if (check != 0 || i == 8)
                break;
        }
    }
    if (check != 0)
        printf("O vencedor eh o jogador %d", check);
    else
        printf("A sem hora ganhou o jogo");
    
}

#pragma region funções

void mostrarTabuleiro(char jogo[3][3]) {
    printf("   1   2   3 \n");
    printf("A  %c | %c | %c \n", jogo[0][0], jogo[0][1], jogo[0][2]);
    printf("  -----------\n");
    printf("B  %c | %c | %c \n", jogo[1][0], jogo[1][1], jogo[1][2]);
    printf("  -----------\n");
    printf("C  %c | %c | %c \n", jogo[2][0], jogo[2][1], jogo[2][2]);
}

int checkarJogo(char jogo[3][3], int index) {
    char marca = 'N';
    int vencedor = 0;
    int i = 0, j = 0;
    for (i = 0; i < 3; i++) {
        marca = 'N';
        for (j = 0; j < 3; j++) {
            if (marca == 'N')
                marca = jogo[i][j];
            else if(jogo[i][j] != marca || jogo[i][j] == ' ')
                break;
        }
        if (j == 3) {
            vencedor = marca == 'X' ? 1 : 2;
            break;
        }
    }
    for (i = 0; i < 3; i++) {
        marca = 'N';
        for (j = 0; j < 3; j++) {
            if (marca == 'N')
                marca = jogo[j][i];
            else if(jogo[j][i] != marca || jogo[j][i] == ' ')
                break;
        }
        if (j == 3) {
            vencedor = marca == 'X' ? 1 : 2;
            break;
        }
    }
    marca = 'N';
    for (i = 0, j = 0; i < 3; i++, j++) {
        if (marca == 'N')
            marca = jogo[i][j];
        else if (jogo[i][j] != marca || jogo[i][j] == ' ')
            break;
    }
    if (j == 3) {
        vencedor = marca == 'X' ? 1 : 2;
    } else {
        marca = 'N';
        for (i = 2, j = 0; j < 3; i--, j++) {
        if (marca == 'N')
            marca = jogo[i][j];
        else if (jogo[i][j] != marca || jogo[i][j] == ' ')
            break;
        }
        if (j == 3)
        vencedor = marca == 'X' ? 1 : 2;
    }
    
    if (vencedor != 0) {
        system("cls||clear");
        mostrarTabuleiro(jogo);
        return vencedor;
    }
    return 0;
}



#pragma endregion