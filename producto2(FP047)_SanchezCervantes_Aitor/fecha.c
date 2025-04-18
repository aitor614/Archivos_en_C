#include "fecha.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 1024





void insertarFechaHora() {

	FILE* archivo;
	errno_t error;
	time_t fecha;
	time(&fecha);
	char buffer[BUFFER_SIZE];

	error = fopen_s(&archivo, "producto2.txt", "a");
	if (error != 0 || archivo == NULL) {
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}
	else {
		ctime_s(buffer, BUFFER_SIZE, &fecha);
		fprintf(archivo, "Fecha y hora: %s", buffer);
		printf_s("Fecha y hora insertada correctamente\n");
		fclose(archivo);
	}
	

}
