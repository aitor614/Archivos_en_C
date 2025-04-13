#include "submenu.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void submenu() {

	int opcion;
	int resultado;

	do {
		printf_s("\n***************SUBMEN�***************\n");
		printf_s("1. Introducir la ubicaci�n del archivo:\n");
		printf_s("2. Introducir el nombre del archivo\n");
		printf_s("3. Salir\n");
		printf_s("\nIntroduce una opci�n: ");


		resultado = scanf_s("%d", &opcion);

		// Limpiar el buffer en caso de entrada incorrecta
		while (getchar() != '\n' && resultado != EOF);

		// Si scanf_s no pudo leer un entero, mostrar error y repetir
		if (resultado != 1) {
			printf("Entrada no v�lida. Por favor, introduce un n�mero entero.\n");
			continue;
		}
		else {
			switch (opcion) {
			case 1:
				seleccionarUbicacionArchivo();
				break;
			case 2:
				seleccionarNombreArchivo();
				break;
			default:
				printf_s("Opci�n no v�lida, Intentalo de nuevo.\n");
				break;

			}
		}

		
	} while (opcion < 1 || opcion > 3);




}