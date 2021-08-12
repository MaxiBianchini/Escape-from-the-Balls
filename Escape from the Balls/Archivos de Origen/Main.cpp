#include "Juego.h"

#define SALIR		0
#define MENU		1
#define JUEGO		2
#define MENUFINAL	3
#define SALIRFINAL	4

int main(int argc, char *argv[])
{
	char opcion = MENU;

	while (opcion != SALIRFINAL)
	{
		Juego* juego = new Juego();

		opcion = MENU;

		while (opcion != SALIR && opcion != SALIRFINAL) {
			if (opcion == MENU) opcion = juego->Menu();
			if (opcion == JUEGO) opcion = juego->Run();
			if (opcion == MENUFINAL) opcion = juego->MenuFinal();
		}

		delete juego;
	}

	return 0;
}