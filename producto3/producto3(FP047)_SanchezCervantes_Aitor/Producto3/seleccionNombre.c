#include "conexionIP.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>


#define BUFFER_SIZE 100


void seleccionarNombreArchivo() {

	/* ---- Variables ---------------------------------- */
	char nombreArchivo[BUFFER_SIZE];
	int longitudMax = sizeof(nombreArchivo);

	/* --- Bucle para la seleccion del archivo que contiene las direcciones IP -------------------------------- */
	do {

		/* --- Pedir al usuario que introduzca la ubicación del archivo -------------------------------- */
		printf_s("\n***************SELECCIÓN DE NOMBRE DEL ARCHIVO***************\n");
		printf_s("Introduce el nombre del archivo: ");

		/* --- Leer el nombre del archivo introducido por el usuario ------------------------ */
		if (!fgets(nombreArchivo, sizeof nombreArchivo, stdin)) {
			perror("Error al leer el nombre del archivo");
			break;
		}

		/* --- Eliminar el salto de línea al final de la cadena ----------------------------------------- */
		nombreArchivo[strcspn(nombreArchivo, "\n")] = '\0';

		/* --- Comprobar si la ubicación es válida ----------------------------------------------------- */
		if (strcmp(nombreArchivo, "DNSips.txt") == 0) {
			printf_s("Nombre correcto\n");
			mostarIpConexiones();


		}
		else {
			printf("Error: El nombre del archivo que contiene las IP's es: 'DNSips.txt'. Inténtalo de nuevo.\n");
		}

		

		/* --- Comprobar si la ubicación es válida ----------------------------------------------------- */
	} while (true);
}
