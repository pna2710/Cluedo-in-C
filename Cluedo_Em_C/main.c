#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Cluedo.h"

void ShowMenu();

int main(void)
{
	srand((int)time(NULL));

	int MenuBit;
	do
	{
		ShowMenu();
		MenuBit = 0;
		while (MenuBit < 1 || MenuBit>4)
		{
			printf("\nChoose an option between 1 and 10");
			scanf("%d", &MenuBit);
		}

		switch (MenuBit)
		{
		case 1:

			break;

		case 2:

			break;

		case 3:

			break;

		case 4:

			break;

		case 5:

			break;

		case 6:

			break;


		default:
			break;
		}
	}

	while (MenuBit != 6);
	printf("\nThank you and goodbye!\n\n");

	return 0;
}

void ShowMenu()
{
	printf("______________________________\n\n");
	printf("\t\tCLUEDO\n\n");
	printf("______________________________\n");
	printf("\nChoose one of the following options:\n\n");
	printf("1. New Game\n");
	printf("2. Continue Game\n");
	printf("3. Load Game\n");
	printf("4. Options\n");
	printf("5. Credits\n");
	printf("6. Exit Game\n");
	printf("______________________________\n\n");
	printf("\t\tEnter your choice:\n\n");
	printf("______________________________\n");
}