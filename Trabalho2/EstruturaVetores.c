#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

typedef struct {
    int * vetorSecundario;
    int topo;
    int size;
} Base;

Base vetorPrincipal[TAM];


typedef struct no {
    int conteudo;
    struct no *prox;
} No;


/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    if (posicao < 1 || posicao > 10) // se posição é um valor válido {entre 1 e 10}
        return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1].vetorSecundario != NULL) // na posicao pode já existir estrutura auxiliar
        return JA_TEM_ESTRUTURA_AUXILIAR;
    if (tamanho < 1) // o tamanho nao pode ser menor que 1
        return TAMANHO_INVALIDO;
    vetorPrincipal[posicao - 1].vetorSecundario = malloc(tamanho * sizeof(int));
    if (vetorPrincipal[posicao - 1].vetorSecundario == NULL)
        return SEM_ESPACO_DE_MEMORIA; // o tamanho ser muito grande
    // deu tudo certo, crie
    vetorPrincipal[posicao - 1].size = tamanho;
    vetorPrincipal[posicao - 1].topo = 0;
    
    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{

    if (posicao < 1 || posicao > 10)
        return POSICAO_INVALIDA;
    posicao--;
    if (vetorPrincipal[posicao].vetorSecundario == NULL) 
        return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao].topo >= vetorPrincipal[posicao].size)
        return SEM_ESPACO;
    //insere
    int posIns = vetorPrincipal[posicao].topo;
    vetorPrincipal[posicao].vetorSecundario[posIns] = valor;
    vetorPrincipal[posicao].topo++;

    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    if (posicao < 1 || posicao > 10)
        return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao - 1].vetorSecundario == NULL) 
        return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao - 1].topo == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;
    vetorPrincipal[posicao - 1].topo--;

    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    int achou = 0;
    if (posicao < 1 || posicao > 10)
        return POSICAO_INVALIDA;
    //
    posicao--;
    if (vetorPrincipal[posicao].vetorSecundario == NULL) 
        return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao].topo == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;
    
    for (int i = 0; i < vetorPrincipal[posicao].topo; i++) {
        if (vetorPrincipal[posicao].vetorSecundario[i] == valor) {
            achou = 1;
            for (int j = i; j < vetorPrincipal[posicao].topo; j++) 
                vetorPrincipal[posicao].vetorSecundario[j] = vetorPrincipal[posicao].vetorSecundario[j + 1];
            break;
        }
    }
    if (achou == 1) {
        vetorPrincipal[posicao].topo--;
    } else {
        return NUMERO_INEXISTENTE;
    }

    return SUCESSO;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    if (posicao < 1 || posicao > 10)
        return POSICAO_INVALIDA;
    else
        return SUCESSO;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    posicao--;
    if (posicao > 9 || posicao < 0)
        return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao].vetorSecundario == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
    else 
        for (int i = 0; i < vetorPrincipal[posicao].topo; i++) 
            vetorAux[i] = vetorPrincipal[posicao].vetorSecundario[i];
    //
    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    posicao--;
    if (posicao > 9 || posicao < 0)
        return POSICAO_INVALIDA;
    if (vetorPrincipal[posicao].vetorSecundario == NULL) 
        return SEM_ESTRUTURA_AUXILIAR;
    else {
        for (int i = 0; i < vetorPrincipal[posicao].topo; i++)
            vetorAux[i] = vetorPrincipal[posicao].vetorSecundario[i];
        //
        bubbleSort(vetorAux, 2);
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = 0;
    int areAllEmpty = 1;
    
    int auxCont = 0;

    for (int i = 0; i < 10; i++) 
    {
        if (vetorPrincipal[i].vetorSecundario != NULL)
        {
            if (vetorPrincipal[i].topo != 0) 
            {
                areAllEmpty = 0;
                for (int j = 0; j < vetorPrincipal[i].topo; j++, auxCont++) 
                    vetorAux[auxCont] = vetorPrincipal[i].vetorSecundario[j];
            }
        }
    }

    if(areAllEmpty)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    //

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{   
    
    getDadosDeTodasEstruturasAuxiliares(vetorAux);
    
    int size = 0;

    int areAllEmpty = 1;

    for (int i = 0; i < 10; i++) 
    {
        if (vetorPrincipal[i].vetorSecundario != NULL)
        {
            if (vetorPrincipal[i].topo != 0) 
            {
                areAllEmpty = 0;
                for (int j = 0; j < vetorPrincipal[i].topo; size++, j++); 
            }
        }
    }
    
    if (size == 0)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    //

    bubbleSort(vetorAux, size);

    return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{

    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;
    posicao--;
    if (vetorPrincipal[posicao].vetorSecundario == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
    if (novoTamanho + vetorPrincipal[posicao].size < 1)
        return NOVO_TAMANHO_INVALIDO;
    //
    
    vetorPrincipal[posicao].vetorSecundario = realloc(vetorPrincipal[posicao].vetorSecundario, (vetorPrincipal[posicao].size + novoTamanho) * sizeof(int));

    if (vetorPrincipal[posicao].vetorSecundario == NULL)
        return SEM_ESPACO_DE_MEMORIA;
    //

    if (vetorPrincipal[posicao].topo >= vetorPrincipal[posicao].size + novoTamanho)
        vetorPrincipal[posicao].topo = vetorPrincipal[posicao].size + novoTamanho;
    //
    vetorPrincipal[posicao].size = vetorPrincipal[posicao].size + novoTamanho;

    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{

    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;
    posicao--;
    if (vetorPrincipal[posicao].vetorSecundario == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao].topo == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;
    //

    return vetorPrincipal[posicao].topo;

}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    
    int num;
    No * lista;
    No * aux;

    for (int i; i < 10; i++) 
    {
        if(vetorPrincipal[i].vetorSecundario)
        {
            int j = 0;
            while (j < vetorPrincipal[i].topo) 
            {
                num = vetorPrincipal[i].vetorSecundario[j];
                No * novo = malloc(sizeof(No));
                if(novo) {
                    novo->conteudo = num;
                    novo->prox = NULL;

                    if (lista == NULL)
                        lista = novo;
                    else 
                    {
                        aux = lista;
                        while (aux->prox)
                            aux = aux->prox;
                        //
                        aux->prox = novo;
                    }
                } 
                else    
                    printf("Erro ao alocar memoria!!!");
                //
                j++;
                return lista;
            }
        }
    }

    
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
    for (int i = 0; i < TAM; i++) {
        vetorPrincipal[i].vetorSecundario = NULL;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].vetorSecundario != NULL) {
            free(vetorPrincipal[i].vetorSecundario);
        }
    }
}

void bubbleSort(int * vetor, int size) 
{
    int i = 1;
    int aux;
    int troca = 1;
    while (troca) 
    {
        troca = 0;
        i = 1;
        while (i < size) 
        {
            if (vetor[i] < vetor[i - 1]) 
            {
                aux = vetor[i];
                vetor[i] = vetor[i - 1];
                vetor[i - 1] = aux;
                troca = 1;
            }
            i++;
        }
    }
}

void inserirNoFim(No **lista, int num) 
{
    No * aux;
    No * novo = malloc(sizeof(No));

    if(novo) {
        novo->conteudo = num;
        novo->prox = NULL;

        if (*lista == NULL)
            *lista = novo;
        else 
        {
            aux = *lista;
            while (aux->prox)
                aux = aux->prox;
            //
            aux->prox = novo;
        }
    } 
    else    
        printf("Erro ao alocar memoria!!!");
    
} 