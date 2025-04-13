#include "menuPrincipal.h"
#include "fecha.h"
#include "submenu.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h> 

void menuPrincipal() {
	int opcion;
	int resultado;

	do {
		printf_s("\n***************MEN� PRINCIPAL***************\n");
		printf_s("1. Inserta la fecha y la hora en el documento de salida\n");
		printf_s("2. Comprobar e informar IP con conexi�n\n");
		printf_s("3. Mostrar y guardar la configuraci�n de red\n");
		printf_s("4. Salir\n");
		printf_s("\nIntroduce una opci�n: ");

		resultado = scanf_s("%d", &opcion); // se lee la opci�n introducida por el usuario y se guarda en la variable opcion 

		// Limpiar el buffer en caso de entrada incorrecta
		while (getchar() != '\n' && resultado != EOF); // sirve para limpiar el buffer y evitar que se quede en un bucle infinito si se introduce un caracter no v�lido 

		// Si scanf_s no pudo leer un entero, mostrar error y repetir
		if (resultado != 1) { // si el resultado es diferente de 1, es decir, si no se ha introducido un n�mero entero 
			printf("Entrada no v�lida. Por favor, introduce un n�mero entero.\n");
			continue; // se vuelve a pedir la opci�n al usuario asi hasta que introduzca un n�mero entero 
		}

		else {

			switch (opcion) {
			case 1:
				insertarFechaHora();
				break;

			case 2:
				submenu();
				break;
			case 3:
				//mostrarFichero();
				break;
			case 4:
				printf_s("Saliendo del programa...\n");
				exit(0);
				break;

			default:
				printf_s("Opci�n no v�lida, Intentalo de nuevo.\n");
				break;
			}
		}

	} while (true);
}
