#include "seleccionNombre.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>


#define BUFFER_SIZE 100


void seleccionarNombreArchivo() {
	
	
	char nombreArchivo[BUFFER_SIZE];
	int longitudMax= sizeof(nombreArchivo);

	do {
		printf_s("\n***************SELECCIÓN DE NOMBRE DEL ARCHIVO***************\n");
		printf_s("Introduce el nombre del archivo: ");

		scanf_s("%99s", nombreArchivo, (unsigned int)sizeof(nombreArchivo)) != 1;
		
		if (strcmp(nombreArchivo, "direccionesIP.txt") == 0) {
			printf_s("Nombre correcto\n");
			mostarIpConexiones();
			
			
		}
		else {
			printf("Error: El nombre del archivo que contiene las IP's es: 'direccionesIP.txt'. Inténtalo de nuevo.\n");
		}


		
	} while (true);
}
