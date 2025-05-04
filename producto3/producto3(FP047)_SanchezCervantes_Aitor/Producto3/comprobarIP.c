#include "seleccionUbicacion.h"
#include "menuPrincipal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



void comprobarIP() {

	/* ---- Variables ---------------------------------- */
	int opcion;
	int resultado;

	/* ---- Mostrar el menú y leer la opción del usuario --------------------- */
	do {
		printf_s("\n***************MENÚ COMPROBAR IP***************\n");
		printf_s("1. Introducir la ubicación del archivo:\n");
		printf_s("2. Introducir el nombre del archivo\n");
		printf_s("3. Atras\n");
		printf_s("4. Salir\n");
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
			switch (opcion) {
			case 1:
				seleccionarUbicacionArchivo();
				break;
			case 2:
				printf_s("\nDebes seleccionar primero la ubicación del archivo antes de introducir el nombre\n");
				opcion = 0;
				break;
			case 3:
				printf_s("Volviendo al menú principal...\n");
				menuPrincipal();
				break;
			case 4:
				printf_s("Saliendo del programa...\n");
				remove("archivoTemporal.txt");
				exit(0);
				break;
			default:
				printf_s("Opción no válida, Intentalo de nuevo.\n");
				break;
			}
		}


	} while (true);

}