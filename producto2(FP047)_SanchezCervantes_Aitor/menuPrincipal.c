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
		printf_s("\n***************MENÚ PRINCIPAL***************\n");
		printf_s("1. Inserta la fecha y la hora en el documento de salida\n");
		printf_s("2. Comprobar e informar IP con conexión\n");
		printf_s("3. Mostrar y guardar la configuración de red\n");
		printf_s("4. Salir\n");
		printf_s("\nIntroduce una opción: ");

		resultado = scanf_s("%d", &opcion); // se lee la opción introducida por el usuario y se guarda en la variable opcion 

		// Limpiar el buffer en caso de entrada incorrecta
		while (getchar() != '\n' && resultado != EOF); // sirve para limpiar el buffer y evitar que se quede en un bucle infinito si se introduce un caracter no válido 

		// Si scanf_s no pudo leer un entero, mostrar error y repetir
		if (resultado != 1) { // si el resultado es diferente de 1, es decir, si no se ha introducido un número entero 
			printf("Entrada no válida. Por favor, introduce un número entero.\n");
			continue; // se vuelve a pedir la opción al usuario asi hasta que introduzca un número entero 
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
				printf_s("Opción no válida, Intentalo de nuevo.\n");
				break;
			}
		}

	} while (true);
}
