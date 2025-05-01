#include "seleccionNombre.h"
#include "seleccionUbicacion.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void menuPrincipal() {

	/* ---- Variables ---------------------------------- */
	int opcion;
	int resultado;


	/* ---- Mostrar el men� y leer la opci�n del usuario --------------------- */
	do {
		printf_s("\n***************MEN� PRINCIPAL***************\n");
		printf_s("1. Introducir la ubicaci�n del archivo:\n");
		printf_s("2. Introducir el nombre del archivo\n");
		printf_s("3. Salir\n");
		printf_s("\nIntroduce una opci�n: ");


		/* --- Leer la opci�n introducida por el usuario ------------------------ */
		resultado = scanf_s("%d", &opcion);

		/* --- Limpiar el buffer en caso de entrada incorrecta --------------------- */
		while (getchar() != '\n' && resultado != EOF);

		/* --- Si scanf_s no pudo leer un entero, mostrar error y repetir ---------------- */
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
				printf_s("\nDebes seleccionar primero la ubicaci�n del archivo antes de introducir el nombre\n");
				opcion = 0;
				break;
			default:
				printf_s("Opci�n no v�lida, Intentalo de nuevo.\n");
				break;

			}
		}

		/* --- Comprobar si la opci�n es v�lida ------------------------------------- */
	} while (opcion < 1 || opcion > 3);




}