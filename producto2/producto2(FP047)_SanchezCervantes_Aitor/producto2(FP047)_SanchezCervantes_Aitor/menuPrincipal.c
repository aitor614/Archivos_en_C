#include "menuPrincipal.h"
#include "fecha.h"
#include "submenu.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h> 



void menuPrincipal() {

	/* --- Variables ----------------- */
	int opcion;
	int resultado;

	/* --- Bucle para mostrar el men� y leer la opci�n del usuario ------------------------- */
	do {
		printf_s("\n***************MEN� PRINCIPAL***************\n");
		printf_s("1. Inserta la fecha y la hora en el documento de salida\n");
		printf_s("2. Comprobar e informar IP con conexi�n\n");
		printf_s("3. Mostrar y guardar la configuraci�n de red\n");
		printf_s("4. Salir\n");
		printf_s("\nIntroduce una opci�n: ");

		/* -- Se lee la opci�n introducida por el usuario y se guarda en la variable opcion -------- */
		resultado = scanf_s("%d", &opcion); 

		/* --- Limpiar el buffer en caso de entrada incorrecta ------------------------------------ */
		while (getchar() != '\n' && resultado != EOF); 

		/* --- Si scanf_s no pudo leer un entero, mostrar error y repetir -------------------------------- */
		if (resultado != 1) {
			printf("Entrada no v�lida. Por favor, introduce un n�mero entero.\n");
			continue; 
		}

		else {

			/* ---Dependiendeo de la opcion elegida se ejecuta una funcion diferente ---------------------------- */
			switch (opcion) {
				/* --- Opci�n 1: Insertar fecha y hora en el documento de salida ------------------------------ */
			case 1:
				insertarFechaHora();
				break;

				/* --- Opci�n 2: Comprobar e informar IP con conexi�n ------------------------------------- */
			case 2:
				submenu();
				break;

				/* --- Opci�n 3: Mostrar y guardar la configuraci�n de red --------------------------------- */
			case 3:
				mostrarAdaptador();
				break;

				/* --- Opci�n 4: Salir del programa ----------------------------------------------------- */
			case 4:
				printf_s("Saliendo del programa...\n");
				exit(0);
				break;

				/* --- Opci�n no v�lida: Mostrar mensaje de error ------------------------------------- */
			default:
				printf_s("Opci�n no v�lida, Intentalo de nuevo.\n");
				break;
			}
		}

		/* --- Comprobar si la opci�n es v�lida ----------------------------------------------------- */
	} while (true);
}
