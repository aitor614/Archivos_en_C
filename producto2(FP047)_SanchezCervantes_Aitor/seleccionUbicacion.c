#include "seleccionUbicacion.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFFER_SIZE 100


void seleccionarUbicacionArchivo() {

	char ubicacionArchivo[BUFFER_SIZE];
	int longitudMax = sizeof(ubicacionArchivo);


	do {

		printf_s("\n***************SELECI�N DE UBICACI�N DEL ARCHIVO***************\n");
		printf_s("Introduce la ubicaci�n del archivo: ");

		scanf_s("%99s", ubicacionArchivo, (unsigned int)sizeof(ubicacionArchivo)) != 1;
			
		// Verificar si el �ltimo car�cter es '/'
		int longitud = strlen(ubicacionArchivo);
		if (longitud > 0 && ubicacionArchivo[longitud - 1] == '/') {

			printf_s("Ubicacion correcta\n");
			seleccionarNombreArchivo();
		}
		else {
			printf("Error: La ubicaci�n debe ser '/' ya que se encuentra en la raiz del pproyecto. Int�ntalo de nuevo.\n");
		}
		

	} while (strcmp(ubicacionArchivo, "/") != 0);


}