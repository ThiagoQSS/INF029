#include <stdio.h>
#include <stdlib.h>

#define QTD_NAVIOS 5

void definirPosicoes(char lado[10][10], int pos1, int pos2, int jogador);
void mostrartabuleiro(char lado[10][10]);
int validarJogada(char lado[10][10], int pos1, int pos2, char direction, int tamNavio);
void mostrarTabuleiros(int jogador, char lado1[10][10], char lado2[10][10]);
void mostrartabuleiroInimigo(char lado[10][10]);
int atirar(char lado[10][10]);
int verificarVencedor(char lado[10][10]);

int main() 
{
    system("cls||clear");
    char lado1[10][10] = {"          ","          ","          ","          ","          ","          ","          ","          ","          ","          ",};
    char lado2[10][10] = {"          ","          ","          ","          ","          ","          ","          ","          ","          ","          "};
    //definindo inicialmente como espaços vazios!
    int naviosRestando = QTD_NAVIOS; 
    int pos1, pos2;
    int vencedor = 0;
    int jogador = 1;
    int tentativa;
    definirPosicoes(lado1, pos1, pos2, 1);
    system("cls||clear");
    mostrartabuleiro(lado1);
    getchar();
    printf("\nEm seguida é vez do jogador 2 posicionar seus navios!\nPressione Enter para continuar...");
    getchar();
    definirPosicoes(lado2, pos1, pos2, 2);
    mostrartabuleiro(lado2);
    printf("\nFase de ataque!!!\nPressione Enter para continuar...");
    getchar();
    system("cls||clear");
    //fase de ataque
    printf("Fase de ataque!\n");
    for (int i = 0; vencedor == 0; i++) {
        jogador = (i % 2) + 1;
        int opcao;
        do {
            printf("Jogador %d:\n0 - ver os tabuleiros\n1 - Atirar\n", jogador);
            scanf("%d", &opcao);
            if(!opcao)
                mostrarTabuleiros(jogador, lado1, lado2);
        } while (!opcao);

        system("cls||clear");

        if (jogador == 1)
            tentativa = atirar(lado2);
        else
            tentativa = atirar(lado1);
        //
        if (tentativa) 
            printf("Tiro certeiro!");
        else 
            printf("Errou!");
        if (verificarVencedor(lado1)) {
            printf("O vencedor eh o jogador 2!!!!!");
            break;
        }
        if (verificarVencedor(lado2)) {
            printf("O vencedor eh o jogador 1!!!!!");
            break;
        }
    }
}

void definirPosicoes (char lado[10][10], int pos1, int pos2, int jogador) {
    int naviosRestando = QTD_NAVIOS; 
    int tamNavio;
    int valido;
    int posTest;
    char direction;
    while (naviosRestando > 0) {
        valido = 1;
        if (naviosRestando == QTD_NAVIOS)
            tamNavio = 4;
        else if(naviosRestando == QTD_NAVIOS - 1)
            tamNavio = 3;
        else if(naviosRestando <= QTD_NAVIOS - 2 && naviosRestando >= QTD_NAVIOS - 5)
            tamNavio = 1;
        else 
            tamNavio = 2;
        system("cls||clear");
        mostrartabuleiro(lado);
        printf("jogador %d,\ndefina a posicao do canto de seu navio de tamanho %d!\nfomato: (1 A x) x ou y indica a direcao \n%d restando ://> ", jogador, tamNavio, naviosRestando);
        scanf("%d %d %c", &pos1, &pos2, &direction);
        direction = direction == 'x' || direction == 'X' ? 'x' : 'y';
        pos1 -= 1;
        pos2 -= 1;

        valido = validarJogada(lado, pos1, pos2, direction, tamNavio);
        if (valido) {
            if(direction == 'x'){
                for (int i = pos2; i <= pos2 + tamNavio - 1; i++)
                    lado[pos1][i] = 'N';
            } else {
                for (int i = pos1; i <= pos1 + tamNavio - 1; i++)
                    lado[i][pos2] = 'N';
            }        

            naviosRestando--;
        } else  
            printf("entrada INvalida\n");
    }
}

void mostrartabuleiro(char lado[10][10]) {
    int i, j;
    printf("    A  B  C  D  E  F  G  H  I  J \n");
    for (i = 0; i < 10; i++) {
        printf("%d  ", i + 1);
        for (j = 0; j < 10; j++){
            printf(" %c ", lado[i][j]);
        }
        printf("\n");
    }
}

void mostrarTabuleiros(int jogador, char lado1[10][10], char lado2[10][10]) {
    if(jogador == 1) {
        mostrartabuleiroInimigo(lado2);
        printf("\n--------------------------------------\n\n");
        mostrartabuleiro(lado1);
    } else {
        mostrartabuleiroInimigo(lado1);
        printf("\n--------------------------------------\n\n");
        mostrartabuleiro(lado2);
    }
}

int validarJogada(char lado[10][10], int pos1, int pos2, char direction, int tamNavio) {
    int i = 0;
    int j = 0;
    if (!(pos1 < 10 && pos2 < 10 && pos1 > -1 && pos2 > -1)) { 
        return 0;
    } else if (direction == 'x') {
        if (pos2 + tamNavio - 1 > 9)
            return 0;
        for (i = pos2; i <= pos2 + tamNavio - 1; i++)
            if (lado[pos1][i] != ' ')
                return 0;
    } else {
        if (pos1 + tamNavio - 1 > 9)
            return 0;
        for (j = pos1; j <= pos1 + tamNavio - 1; j++)
            if (lado[j][pos2] != ' ')
                return 0;
    }
    return 1;
}

void mostrartabuleiroInimigo(char lado[10][10]) {
    int i, j;
    printf("    A  B  C  D  E  F  G  H  I  J \n");
    for (i = 0; i < 10; i++) {
        printf("%d  ", i + 1);
        for (j = 0; j < 10; j++){
            printf(" %c ", lado[i][j] == 'N' || lado[i][j] == ' ' ? ' ' : lado[i][j]);
        }
        printf("\n");
    }
}

int atirar(char lado[10][10]) {
    int pos1, pos2;
    int valido = 1;
    printf("\nDigite a posicao dos disparos: (i j)\n");
    do {
        scanf("%d %d", &pos1, &pos2);
        pos1 -= 1;
        pos2 -= 1;
        if (!(pos1 < 10 && pos2 < 10 && pos1 > -1 && pos2 > -1))
            valido = 0;
    } while (!valido);
    if (lado[pos1][pos2] == 'N'){
        lado[pos1][pos2] = 'O';
        return 1;
    } else {
        lado[pos1][pos2] = 'X';
        return 0;
    }
}

int verificarVencedor(char lado[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (lado[i][j] == 'N')
                return 0;
    
    return 1;
}