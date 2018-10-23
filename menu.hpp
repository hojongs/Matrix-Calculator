#include <string.h>
#define MENU_DESC_SIZE 256

typedef struct _Menu
{
	int id;
	char description[MENU_DESC_SIZE];
	void(*callback)();
}Menu;

Menu initMenu(int id, char description[], void(*func)())
{
	Menu menu = { 0 };
	menu.id = id;
	memcpy(menu.description, description, MENU_DESC_SIZE);
	menu.callback = func;

	return menu;
}

void printMenu(Menu menuArr[], int n)
{
	if (MATRIX_LOG_ENABLE)
	{
		for (int i = 0; i < n; i++)
		{
			Menu menu = menuArr[i];
			fprintf(stdout, "%d. %s \n", menu.id, menu.description);
		}
	}
	fprintf(stdout, "select : ");
}

void runMenu(Menu menuArr[], int menuCnt, int selection)
{
	for (int i = 0; i < menuCnt; i++)
	{
		Menu menu = menuArr[i];
		if (menu.id == selection)
			menu.callback();
	}
}