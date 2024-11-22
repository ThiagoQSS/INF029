// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome:
//  email:
//  Matrícula:
//  Semestre:

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "ThiagoSacramento20241160010.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>

#pragma region CoisasDoProf

DataQuebrada quebraData(char data[]);
DataSeparada separarData(char data[]);
/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
  int soma;
  soma = x + y;
  return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ // função utilizada para testes
  int i, fat = 1;

  for (i = x; i > 1; i--)
    fat = fat * i;

  return fat;
}

int teste(int a)
{
  int val;
  if (a == 2)
    val = 3;
  else
    val = 4;

  return val;
}
#pragma endregion

#pragma region Q1
/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
  DataSeparada sData = separarData(data);
  return sData.valido;
}

#pragma endregion

#pragma region Q2
/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal.
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

  // calcule os dados e armazene nas três variáveis a seguir
  DataSeparada datas1 = separarData(datainicial);
  DataSeparada datas2 = separarData(datafinal);
  DiasMesesAnos dma;

  dma.qtdDias = 0;
  dma.qtdMeses = 0;
  dma.qtdAnos = 0;
  dma.retorno = 1;

  if (q1(datainicial) == 0)
  {
    printf("data inicial invalida!\n");
    dma.retorno = 2;
    return dma;
  }
  else if (q1(datafinal) == 0)
  {
    printf("data final invalida!\n");
    dma.retorno = 3;
    return dma;
  }
  else
  {
    // verifique se a data final não é menor que a data inicial
    if (datas1.ano > datas2.ano) {
      dma.retorno = 4;
      return dma;
    }
    else if (datas1.ano == datas2.ano && datas1.mes > datas2.mes) {
      dma.retorno = 4;
      return dma;
    }
    else if (datas1.ano == datas2.ano && datas1.mes == datas2.mes && datas1.dia > datas2.dia) {
      dma.retorno = 4;
      return dma;
    }
    // Visto que a data é valida:
    DiasMesesAnos dmaCont;
    dmaCont.qtdDias = datas1.dia;
    dmaCont.qtdMeses = datas1.mes;
    dmaCont.qtdAnos = datas1.ano;
    // calcule a distancia entre as datas
    while (dmaCont.qtdAnos != datas2.ano || dmaCont.qtdMeses != datas2.mes || dmaCont.qtdDias != datas2.dia)
    {
      //printf("%d %d %d\n", dmaCont.qtdDias, dmaCont.qtdMeses, dmaCont.qtdAnos);
      incrementarDia(&dma, &dmaCont);
    }
    // se tudo der certo
    dma.retorno = 1;
    printf("dias: %d\n", dma.qtdDias);
    printf("Meses: %d\n", dma.qtdMeses);
    printf("Anos: %d\n", dma.qtdAnos);
    return dma;
  }
}
#pragma endregion

#pragma region Q3
/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
    Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *text, char c, int isCaseSensitive)
{
	char texto[250];
	int i;
	for (i = 0; text[i]; i++)
		texto[i] = text[i];
	texto[i] = '\0';
  int qtdOcorrencias = 0; //começou = -1, não sei pq

  if (isCaseSensitive != 1) {
    for (int i = 0; texto[i]; i++)
      if(texto[i] <= 'z' && texto[i] >= 'a')
        texto[i] -= 32; 
		//
    if(c <= 'z' && c >= 'a')
      c -= 32;
  }
  
	//printf("\n%c ", c);
	
  for (int i = 0; texto[i]; i++) {
    if (texto[i] == c)
      qtdOcorrencias++;
  }
	//printf("qtd: %d\n", qtdOcorrencias);
  return qtdOcorrencias;
}
#pragma endregion

#pragma region Q4
/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
  int qtdOcorrencias = 0; //pq ele deixa -1?
  int index = 0;
  int inicio, final;
  int achou = 1;

  for (int i = 0; strTexto[i]; i++)
      if(strTexto[i] <= 'z' && strTexto[i] >= 'a')
        strTexto[i] -= 32;

  for (int i = 0; strBusca[i]; i++)
      if(strBusca[i] <= 'z' && strBusca[i] >= 'a')
        strBusca[i] -= 32;
  //

  for(int i = 0; strTexto[i]; i++) {
    int j, k;
    int achou = 1;

    if (strTexto[i] == strBusca[0]) {
			inicio = i + 1;
      for(j = i, k = 0; strBusca[k]; j++, k++) {
        if (strBusca[k] != strTexto[j]) {
          achou = 0;
          break;
        }
      }
      if (achou) {
        
				final = j;
				i = final - 1;
        //printf("\ninicio: %d\n", inicio);
        //printf("final: %d\n\n", final);
        posicoes[index++] = inicio;
        posicoes[index++] = final;
        qtdOcorrencias++;
      }
    }

  }

  return qtdOcorrencias;
}
#pragma endregion

#pragma region Q5
/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
  int newNum = 0;
  int digitos;
  int pot;
  int twopot;

  //ver qnts digitos temos em num
  newNum = num;
  for (digitos = 1; newNum > 9; digitos++) 
    newNum /= 10;
  //

  //
  newNum = 0;
  for (int i = 0; digitos > 0; digitos--, i++) {
    int aux;
    pot = 1;
    twopot = 1;
    for (aux = digitos - 1; aux > 0; aux--) {
      pot *= 10;
    }
    for (int j = 0; j < i; j++) {
      twopot *= 10;
    }
    newNum += ((num / pot) % 10) * twopot;
    // printf("num: %d\n", num);
    // printf("inverso: %d\n\n", newNum);
  }
  //

  num = newNum;
  return num;
}
#pragma endregion

#pragma region Q6
/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
  int qtdOcorrencias;
	char numBase[100];
	char numBusca[100];

	intToString(numBase, numerobase);
	intToString(numBusca, numerobusca);

	qtdOcorrencias = BuscarString(numBase, numBusca);


  return qtdOcorrencias;
}

#pragma endregion

#pragma region SeparadordeData
DataSeparada separarData(char data[]) 
{
  DataSeparada DS;
  DS.valido = 1;
  DS.dia = 0;
  DS.mes = 0;
  DS.ano = 0;
  // quebrar a string data em strings sDia, sMes, sAno
  char sDia[3];
  char sMes[3];
  char sAno[5];
  int i, j;
  for (i = 0; i < 2 && data[i] != '/'; i++)
    sDia[i] = data[i];
  sDia[i++] = '\0';

  for (j = 0; j < 2 && data[i] != '/'; i++, j++)
    sMes[j] = data[i];
  sMes[j] = '\0';
  i++;

  for (j = 0; j < 4 && data[i] != '\0'; i++, j++)
    sAno[j] = data[i];
  sAno[j] = '\0';
  i++;

  //printf("..%s, ", sDia);
  //printf("%s, ", sMes);
  //printf("%s\n", sAno);

  // dia = stringToInt(sDia);
  // mes = stringToInt(sMes);
  // ano = stringToInt(sAno);

  for (int i = 0; sDia[i]; i++) {
    DS.dia *= 10;
    DS.dia += sDia[i] - 48;
  }

  for (int i = 0; sMes[i]; i++) {
    DS.mes *= 10;
    DS.mes += sMes[i] - 48;
  }

  for (int i = 0; sAno[i]; i++) {
    DS.ano *= 10;
    DS.ano += sAno[i] - 48;
  }
  int ano = DS.ano, mes = DS.mes, dia = DS.dia;
  //printf("%d %d %d\n", dia, mes, ano);
  if (mes < 13 && mes > 0 && dia > 0) {
    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || 
        mes == 8 || mes == 10 || mes == 12) {
        if (dia > 31)
            DS.valido = 0;
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        if (dia > 30)
            DS.valido = 0;
    } else if (ano % 4 == 0 && ano % 100 != 0 || ano % 400 == 0 && ano % 4 == 0) {
        if (dia > 29) {
            DS.valido = 0;
        }
    } else if (dia > 28)
      DS.valido = 0;
  } else
    DS.valido = 0;
  return DS;
}

void incrementarDia(DiasMesesAnos *dmaCont, DiasMesesAnos *dma) {
  int dia = dma->qtdDias;
  int mes = dma->qtdMeses;
  int ano = dma->qtdAnos;
  if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) {
    if (dia == 31) {
      dma->qtdDias = 1;
      dmaCont->qtdDias = 0;
      incrementarMeses(dma, dmaCont);
    } else 
      dma->qtdDias++;
      dmaCont->qtdDias++;
  } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
    if (dia == 30) {
      dma->qtdDias = 1;
      dmaCont->qtdDias = 0;
      incrementarMeses(dma, dmaCont);
    } else 
      dma->qtdDias++;
      dmaCont->qtdDias++;
  } else if (ano % 4 == 0 && ano % 100 != 0 || ano % 400 == 0 && ano % 4 == 0) {
    if (dia == 29) {
      dma->qtdDias = 1;
      dmaCont->qtdDias = 0;
      incrementarMeses(dma, dmaCont);
    } else 
      dma->qtdDias++;
      dmaCont->qtdDias++;
  } else if (dia == 28) {
    dma->qtdDias = 1;
    dmaCont->qtdDias = 0;
    incrementarMeses(dma, dmaCont);
  } else
    dma->qtdDias++;
    dmaCont->qtdDias++;
}

void incrementarMeses(DiasMesesAnos *dma, DiasMesesAnos *dmaCont) {
  int mes = dma->qtdMeses;
  if (mes == 12) {
    dma->qtdMeses = 1;
    dmaCont->qtdMeses = 0;
    incrementarAnos(dma, dmaCont);
  } else 
    dma->qtdMeses++;
    dmaCont->qtdMeses++;
}

void incrementarAnos(DiasMesesAnos *dma, DiasMesesAnos *dmaCont) {
  dma->qtdAnos++;
  dmaCont->qtdAnos++;
}

#pragma endregion

#pragma region Prof
DataQuebrada quebraData(char data[])
{
  DataQuebrada dq;
  char sDia[3];
  char sMes[3];
  char sAno[5];
  int i;

  for (i = 0; data[i] != '/'; i++)
  {
    sDia[i] = data[i];
  }
  if (i == 1 || i == 2)
  {                 // testa se tem 1 ou dois digitos
    sDia[i] = '\0'; // coloca o barra zero no final
  }
  else
  {
    dq.valido = 0;
    return dq;
  }

  int j = i + 1; // anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '/'; j++)
  {
    sMes[i] = data[j];
    i++;
  }

  if (i == 1 || i == 2)
  {                 // testa se tem 1 ou dois digitos
    sMes[i] = '\0'; // coloca o barra zero no final
  }
  else
  {
    dq.valido = 0;
    return dq;
  }

  j = j + 1; // anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '\0'; j++)
  {
    sAno[i] = data[j];
    i++;
  }

  if (i == 2 || i == 4)
  {                 // testa se tem 2 ou 4 digitos
    sAno[i] = '\0'; // coloca o barra zero no final
  }
  else
  {
    dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno);

  dq.valido = 1;

  return dq;
}
#pragma endregion

void intToString(char string[], int num) {

	int newNum;
	//printf("%d\n", num);

	int i;
	for (i = 0; num > 0; i++) {
		string[i] = (num % 10) + 48;
		num /= 10;
	}
	string[i] = '\0';
	
	char aux[100];
	int j;
	for (j = 0; string[j]; j++)
		aux[j] = string[j];
	aux[j] = '\0';

	for (j = j - 1, i = 0; j >= 0; j--, i++)
		string[i] = aux[j];
	string[i] = '\0';
	//printf("%s\n", string);

}

int BuscarString(char stringBase[], char strBusca[]) {
	int qtdOcorrencias = 0;
	for(int i = 0; stringBase[i]; i++) {
    int j, k;
    int achou = 1;
    if (stringBase[i] == strBusca[0]) {
      for(j = i, k = 0; strBusca[k]; j++, k++) {
        if (strBusca[k] != stringBase[j]) {
          achou = 0;
          break;
        }
      }
      if (achou) {
        qtdOcorrencias++;
				i = j - 1;
      }
    }
	}

	return qtdOcorrencias;

}
