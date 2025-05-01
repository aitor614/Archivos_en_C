#include "conexionIP.h"
#include "menuPrincipal.h"
#include "ping.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024


void mostarIpConexiones() {
	
	/* -- Variables ---------------------------------- */
	FILE* archivo;
	char buffer[BUFFER_SIZE];
	int isEmpty = 1;

	/* -- Abrir el archivo direccionesIP.txt -------------- */
	fopen_s(&archivo, "direccionesIP.txt", "r");

	if (!archivo) {
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);	
	}
	else {
		/* -- Leer el archivo y mostrar su contenido -------- */
		printf_s("\nArchivo abierto correctamente\n");
		printf_s("\nEl contenido del archivo direccionesIP.txt es:\n");
	
		while (fgets(buffer, BUFFER_SIZE, archivo) != NULL) {
			isEmpty = 0;
			buffer[strcspn(buffer, "\n")] = 0; /* --- strcspn: Devuelve la longitud de la cadena sin el salto de l�nea --- */ 
			printf_s("%s\n", buffer);
		}

		
	}
	/* -- Cerrar el archivo ------------------------------ */
	fclose(archivo);

	/* -- Comprobar si el archivo est� vac�o ------------- */
	if (isEmpty) {
		printf_s("El archivo est� vac�o\n");
		printf_s("Volviedo al men� principal...\n");

		/* -- Volver al Menu Principal ------------------- */
		menuPrincipal();
		return;
	}

	/* -- Realizar ping a las IPs ----------------------- */
	ping();

	
}

