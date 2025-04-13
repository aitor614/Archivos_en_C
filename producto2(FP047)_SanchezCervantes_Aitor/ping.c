#include "ping.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 1024

void ping() {

	FILE* archivo;
	errno_t error;
	char buffer[BUFFER_SIZE];
	char bufferSalida[BUFFER_SIZE];


	error = fopen_s(&archivo, "direccionesIP.txt", "r");

	if (error != 0 || archivo == NULL) {
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}


	while (fgets(buffer, sizeof(buffer), archivo) != NULL) {


		buffer[strcspn(buffer, "\r\n")] = '\0'; // Elimina saltos de línea
		printf_s("\nRealizando ping a la IP: %s", buffer);

		char bufferPing[BUFFER_SIZE + 50];  // Espacio extra para el comando
		snprintf(bufferPing, sizeof(bufferPing), "ping -n 4 %s", buffer); // Comando para realizar ping a la IP 4 veces y guardar la salida en un archivo temporal 
		

		FILE* archivoTemporal;
		archivoTemporal = _popen(bufferPing, "r");
		if (!archivoTemporal) {
			printf_s("Error al ejecutar ping para: %s\n", buffer);
			continue;
		}

		int exitoso = 0;
		char pingExitoso[BUFFER_SIZE * 10] = ""; // Guardar la salida del ping en caso de ser exitoso

		// Verificar si el ping fue exitoso buscando "tiempo" o "time" en la salida
		while (fgets(bufferSalida, sizeof(bufferSalida), archivoTemporal) != NULL) {
			printf_s("%s", bufferSalida);
			if (strstr(bufferSalida, "tiempo") || strstr(bufferSalida, "time")) {
				exitoso = 1;
			}
			if (exitoso) {
				strcat_s(pingExitoso, sizeof(pingExitoso), bufferSalida);
			}
		}
		_pclose(archivoTemporal);
		
		if (exitoso) {
			FILE* archivo2;
			error = fopen_s(&archivo2, "producto2.txt", "a");
				
			if (error == 0 && archivo2 != NULL) {
				fprintf(archivo2, "\nPing a la IP: %s\n%s", buffer, pingExitoso);
				fclose(archivo2);
				printf_s("\nPing exitoso para: %s\nGuardado en producto2.txt\n", buffer);
			}
			else {
				perror("Error al abrir producto2.txt para escribir el resultado");
				exit(EXIT_FAILURE);
			}
		}
		else {
			printf_s("\nError: No se recibió respuesta de la IP %s\n", buffer);
		}

	}
	fclose(archivo);
	printf_s("Volviendo al menú Principal...\n");
	menuPrincipal();

}


		

	