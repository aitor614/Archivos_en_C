#include "conexionIP.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024


void mostarIpConexiones() {
	FILE* archivo;
	errno_t error;
	char buffer[BUFFER_SIZE];
	int isEmpty = 1;

	error = fopen_s(&archivo, "direccionesIP.txt", "r");

	if (error != 0 || archivo == NULL) {
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}
	else {
		

		printf_s("\nArchivo abierto correctamente\n");
		printf_s("\nEl contenido del archivo direccionesIP.txt es:\n");

		while (fgets(buffer, BUFFER_SIZE, archivo) != NULL) {
			isEmpty = 0;
			buffer[strcspn(buffer, "\n")] = 0; // strcspn: Devuelve la longitud de la cadena sin el salto de línea
			printf_s("%s\n", buffer);
		}

		
	}
	fclose(archivo);
	if (isEmpty) {
		printf_s("El archivo está vacío\n");
		printf_s("Volviedo al menú principal...\n");
		menuPrincipal();
		return;
	}
	ping();

	
}

