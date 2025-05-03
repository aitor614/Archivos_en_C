#include "seleccionNombre.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 100


void seleccionarUbicacionArchivo() {

	/* ---- Variables ---------------------------------- */
	char ubicacionArchivo[BUFFER_SIZE];
	int longitudMax = sizeof(ubicacionArchivo);


	/* --- Bucle para la seleccion del archivo que contiene las direcciones IP -------------------------------- */
	do {

		/* --- Pedir al usuario que introduzca la ubicación del archivo -------------------------------- */
		printf_s("\n***************SELECIÓN DE UBICACIÓN DEL ARCHIVO***************\n");
		printf_s("Introduce la ubicación del archivo: ");

		/* --- Leer la ubicación del archivo introducida por el usuario ------------------------ */
		if (!fgets(ubicacionArchivo, sizeof ubicacionArchivo, stdin)) {
			perror("Error al leer la ubicación del archivo");
			return;
		}

		/* --- Eliminar el salto de línea al final de la cadena ----------------------------------------- */
		ubicacionArchivo[strcspn(ubicacionArchivo, "\n")] = '\0';

		/* --- Comprobar si la ubicación es válida ----------------------------------------------------- */
		int longitud = strlen(ubicacionArchivo);
		if (longitud > 0 && ubicacionArchivo[longitud - 1] == '/') {

			printf_s("Ubicacion correcta\n");

			/* --- Seleccionar el nombre del archivo ----------------------------------------- */
			seleccionarNombreArchivo();
		}
		else {
			printf("Error: La ubicación debe ser '/' ya que se encuentra en la raiz del proyecto. Inténtalo de nuevo.\n");
		}

		/* --- Comprobar si la ubicación es válida ----------------------------------------------------- */
	} while (strcmp(ubicacionArchivo, "/") != 0);


}