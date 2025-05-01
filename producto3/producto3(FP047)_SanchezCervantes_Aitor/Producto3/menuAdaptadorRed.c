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



	/* ---- Mostrar el men� y leer la opci�n del usuario --------------------- */
	do {
		printf_s("\n***************MEN� ADAPTADOR DE RED***************\n");
		printf_s("1. Escoger el adaptador de red a modificar\n");
		printf_s("2. Atras\n");
		printf_s("3. Salir\n");
		printf_s("4. Realizar prueba de conexi�n\n");
		printf_s("\nIntroduce una opci�n: ");

		/* --- Leer la opci�n introducida por el usuario ------------------------ */
		int resultado = scanf_s("%d", &opcion);

		/* --- Limpiar el buffer en caso de entrada incorrecta --------------------- */
		while (getchar() != '\n' && resultado != EOF);

		/* --- Si scanf_s no pudo leer un entero, mostrar error y repetir ---------------- */
		if (resultado != 1) {
			printf("Entrada no v�lida. Por favor, introduce un n�mero entero.\n");
			continue;
		}
		else {
			switch (opcion)
			{
			case 1:
				escogerAdaptador();
			case 2:
				printf_s("Volviendo al men� principal...\n");
				menuPrincipal();
				break;
			case 3:
				printf_s("Saliendo del programa...\n");
				exit(0);

			case 4:
				printf_s("Realizando prueba de conexi�n...\n");
				adaptadorRed();
				break;
			default:
				break;
			}
		}


	} while (true);

}