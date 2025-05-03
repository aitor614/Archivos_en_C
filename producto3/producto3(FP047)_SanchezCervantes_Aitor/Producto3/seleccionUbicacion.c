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

		/* --- Pedir al usuario que introduzca la ubicaci�n del archivo -------------------------------- */
		printf_s("\n***************SELECI�N DE UBICACI�N DEL ARCHIVO***************\n");
		printf_s("Introduce la ubicaci�n del archivo: ");

		/* --- Leer la ubicaci�n del archivo introducida por el usuario ------------------------ */
		if (!fgets(ubicacionArchivo, sizeof ubicacionArchivo, stdin)) {
			perror("Error al leer la ubicaci�n del archivo");
			return;
		}

		/* --- Eliminar el salto de l�nea al final de la cadena ----------------------------------------- */
		ubicacionArchivo[strcspn(ubicacionArchivo, "\n")] = '\0';

		/* --- Comprobar si la ubicaci�n es v�lida ----------------------------------------------------- */
		int longitud = strlen(ubicacionArchivo);
		if (longitud > 0 && ubicacionArchivo[longitud - 1] == '/') {

			printf_s("Ubicacion correcta\n");

			/* --- Seleccionar el nombre del archivo ----------------------------------------- */
			seleccionarNombreArchivo();
		}
		else {
			printf("Error: La ubicaci�n debe ser '/' ya que se encuentra en la raiz del proyecto. Int�ntalo de nuevo.\n");
		}

		/* --- Comprobar si la ubicaci�n es v�lida ----------------------------------------------------- */
	} while (strcmp(ubicacionArchivo, "/") != 0);


}