#include <stdio.h>
#include <stdlib.h>
#include "./Arvore.h"

int menu()
{
	printf("--------------------------------------------------------------- \n");
	printf("| 1. Inserir a faixa valor de [ a .. b ], inteiros.           | \n");
	printf("| 2. Remover a faixa valor de [ a .. b ], inteiros.           | \n");
	printf("| 3. Retornar a quantidade de nos e memoria alocada da arvore | \n");
	printf("| 4. Salvar.                                                  | \n");
	printf("--------------------------------------------------------------- \n => ");

	int option;
	scanf("%d", &option);
	while (option < 1 || option > 4)
	{
		printf("Opicao invalida, digite um numero entre 1 e 4.\n => ");
		scanf("%d", &option);
	}
	return option;
}

void handleOptionOne(Arvore *arv)
{
	int a, b;
	printf("\n Digite o valor de a e b, onde b>= a >=0, respectivamente.\n a => ");
	scanf("%d", &a);
	printf("b => ");

	scanf("%d", &b);
	while (b < a || a < 0)
	{
		printf("\n Valores invalidos, digite novamente\n a=> ");
		scanf("%d", &a);
		printf("b => ");
		scanf("%d", &b);
	}
	printf("\n Inserindo os valores de [ %d .. %d] \n", a, b);
	for (a; a <= b; a++)
	{
		inserir(arv, a);
	}
}

void handleOptionTwo(Arvore *arv)
{
	int a, b;
	printf("\n Digite o valor de a e b, onde b>= a >=0, respectivamente.\n a => ");
	scanf("%d", &a);
	printf("b => ");
	scanf("%d", &b);
	while (b < a || a < 0)
	{
		printf("\n Valores invalidos, digite novamente\n a=> ");
		scanf("%d", &a);
		printf("b => ");
		scanf("%d", &b);
	}
	printf("\n Removendo os valores de [ %d .. %d] \n", a, b);
	for (a; a <= b; a++)
	{
		remover(arv, a);
	}
}

int main(int argc, char *argv[])
{
	Arvore *arv = criar();

	int option;
	do
	{
		option = menu();
		switch (option)
		{
		case 1:
			system("cls");
			handleOptionOne(arv);
			break;
		case 2:
			system("cls");
			handleOptionTwo(arv);
			break;
		case 3:
			system("cls");
			printf("\n Quantidade de nos %d\n", getCountNo(arv));
			printf("\n Memoria ocupada %d\n", getMemory(arv));
			break;
		case 4:
			system("cls");
			printf("\n Salvando os dados...\n ");
			save(arv);
			break;
		default:
			break;
		}

	} while (option > 0 && option < 5);

	destruir(arv);
	return 0;
}
