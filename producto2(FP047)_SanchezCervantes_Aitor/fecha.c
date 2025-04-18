#include "fecha.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 1024



void insertarFechaHora() {

	/* --- Variables ----------------------------------------- */
	FILE* archivo;
	time_t fecha;

	time(&fecha);

	char buffer[BUFFER_SIZE];


	/* --- Abrir el archivo en modo de modo de añadir (append)  ---------------- */
		if (fopen_s(&archivo, "producto2.txt", "a") !=0 || !archivo) {
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);

	}	else {
		ctime_s(buffer, BUFFER_SIZE, &fecha);
		fprintf(archivo, "\nFecha y hora: %s", buffer);
		printf_s("Fecha y hora insertada correctamente\n");
		fclose(archivo);
	}
	

}
