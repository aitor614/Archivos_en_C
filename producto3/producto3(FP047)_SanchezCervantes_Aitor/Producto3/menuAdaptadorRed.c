#include "mostrarAdaptadorRed.h"
#include "escogerAdaptador.h"
#include "menuPrincipal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



void menuAdaptadorRed() {

	/* ---- Variables ---------------------------------- */
	int opcion;
	int resultado;



	/* ---- Mostrar el menú y leer la opción del usuario --------------------- */
	do {
		printf_s("\n***************MENÚ ADAPTADOR DE RED***************\n");
		printf_s("1. Escoger el adaptador de red a modificar\n");
		printf_s("2. Atras\n");
		printf_s("3. Salir\n");
		printf_s("4. Realizar prueba de conexión\n");
		printf_s("\nIntroduce una opción: ");

		/* --- Leer la opción introducida por el usuario ------------------------ */
		int resultado = scanf_s("%d", &opcion);

		/* --- Limpiar el buffer en caso de entrada incorrecta --------------------- */
		while (getchar() != '\n' && resultado != EOF);

		/* --- Si scanf_s no pudo leer un entero, mostrar error y repetir ---------------- */
		if (resultado != 1) {
			printf("Entrada no válida. Por favor, introduce un número entero.\n");
			continue;
		}
		else {
			switch (opcion)
			{
			case 1:
				escogerAdaptador();
			case 2:
				printf_s("Volviendo al menú principal...\n");
				menuPrincipal();
				break;
			case 3:
				printf_s("Saliendo del programa...\n");
				exit(0);

			case 4:
				printf_s("Realizando prueba de conexión...\n");
				adaptadorRed();
				break;
			default:
				break;
			}
		}


	} while (true);

}