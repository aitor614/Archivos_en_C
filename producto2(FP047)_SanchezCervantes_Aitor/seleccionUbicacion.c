#include "seleccionUbicacion.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFFER_SIZE 100


void seleccionarUbicacionArchivo() {

	/* ---- Variables ---------------------------------- */
	char ubicacionArchivo[BUFFER_SIZE];
	int longitudMax = sizeof(ubicacionArchivo);


	/* ---- Pedir al usuario que introduzca la ubicación del archivo -------- */
	do {

		printf_s("\n***************SELECIÓN DE UBICACIÓN DEL ARCHIVO***************\n");
		printf_s("Introduce la ubicación del archivo: ");

		if (!fgets(ubicacionArchivo, sizeof ubicacionArchivo, stdin)) {
			perror("Error al leer la ubicación del archivo");
			return;
		}

		//scanf_s("%99s", ubicacionArchivo, (unsigned int)sizeof(ubicacionArchivo)) != 1;
			
		/* --- Eliminar el salto de línea al final de la cadena ----------------------------------------- */
		ubicacionArchivo[strcspn(ubicacionArchivo, "\n")] = '\0'; 

		/* --- Comprobar si la ubicación es válida ----------------------------------------------------- */
		int longitud = strlen(ubicacionArchivo);
		if (longitud > 0 && ubicacionArchivo[longitud - 1] == '/') {

			printf_s("Ubicacion correcta\n");
			seleccionarNombreArchivo();
		}
		else {
			printf("Error: La ubicación debe ser '/' ya que se encuentra en la raiz del pproyecto. Inténtalo de nuevo.\n");
		}
		

	} while (strcmp(ubicacionArchivo, "/") != 0);


}