#include "comprobarIP.h"
#include "menuAdaptadorRed.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void menuPrincipal() {

	/* ---- Variables ---------------------------------- */
	int opcion;
	int resultado;


	/* ---- Mostrar el menú y leer la opción del usuario --------------------- */
	do {
		printf_s("\n***************MENÚ PRINCIPAL***************\n");
		printf_s("1. Comprobar las IP válidas\n");
		printf_s("2. Modificar el adaptador de red\n");
		printf_s("3. Salir\n");
		printf_s("\nIntroduce una opción: ");


		/* --- Leer la opción introducida por el usuario ------------------------ */
		resultado = scanf_s("%d", &opcion);

		/* --- Limpiar el buffer en caso de entrada incorrecta --------------------- */
		while (getchar() != '\n' && resultado != EOF);

		/* --- Si scanf_s no pudo leer un entero, mostrar error y repetir ---------------- */
		if (resultado != 1) {
			printf("Entrada no válida. Por favor, introduce un número entero.\n");
			continue;
		}
		else {
			switch (opcion) {
			case 1:
				comprobarIP();
				break;
			case 2:
				menuAdaptadorRed();
				break;	
			case 3:
				printf_s("Saliendo del programa...\n");
				remove("archivoTemporal.txt");
				exit(0);
				break;
			default:
				printf_s("Opción no válida, Intentalo de nuevo.\n");
				break;

			}
		}

		/* --- Comprobar si la opción es válida ------------------------------------- */
	} while (true);




}