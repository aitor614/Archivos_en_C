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

	/* --- Bucle para mostrar el menú y leer la opción del usuario ------------------------- */
	do {
		printf_s("\n***************MENÚ PRINCIPAL***************\n");
		printf_s("1. Inserta la fecha y la hora en el documento de salida\n");
		printf_s("2. Comprobar e informar IP con conexión\n");
		printf_s("3. Mostrar y guardar la configuración de red\n");
		printf_s("4. Salir\n");
		printf_s("\nIntroduce una opción: ");

		/* -- Se lee la opción introducida por el usuario y se guarda en la variable opcion -------- */
		resultado = scanf_s("%d", &opcion); 

		/* --- Limpiar el buffer en caso de entrada incorrecta ------------------------------------ */
		while (getchar() != '\n' && resultado != EOF); 

		/* --- Si scanf_s no pudo leer un entero, mostrar error y repetir -------------------------------- */
		if (resultado != 1) {
			printf("Entrada no válida. Por favor, introduce un número entero.\n");
			continue; 
		}

		else {

			/* ---Dependiendeo de la opcion elegida se ejecuta una funcion diferente ---------------------------- */
			switch (opcion) {
				/* --- Opción 1: Insertar fecha y hora en el documento de salida ------------------------------ */
			case 1:
				insertarFechaHora();
				break;

				/* --- Opción 2: Comprobar e informar IP con conexión ------------------------------------- */
			case 2:
				submenu();
				break;

				/* --- Opción 3: Mostrar y guardar la configuración de red --------------------------------- */
			case 3:
				mostrarAdaptador();
				break;

				/* --- Opción 4: Salir del programa ----------------------------------------------------- */
			case 4:
				printf_s("Saliendo del programa...\n");
				exit(0);
				break;

				/* --- Opción no válida: Mostrar mensaje de error ------------------------------------- */
			default:
				printf_s("Opción no válida, Intentalo de nuevo.\n");
				break;
			}
		}

		/* --- Comprobar si la opción es válida ----------------------------------------------------- */
	} while (true);
}
