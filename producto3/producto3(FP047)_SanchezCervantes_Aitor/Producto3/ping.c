#include "ping.h"
#include "menuPrincipal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define BUFFER_SIZE 1024

void ping() {

	/* ---- Variables ---------------------------------- */
	FILE* archivo;
	FILE* archivoPingSalida;
	FILE* archivoTemporal;

	int exitoso = 0;
	char pingExitoso[BUFFER_SIZE * 10] = "";

	char buffer[BUFFER_SIZE];
	char bufferSalida[BUFFER_SIZE];

	/* ---- Abrir archivo con las IPs en modo lectura ---------------------------------- */
	if (fopen_s(&archivo, "DNSips.txt", "r") !=0 || !archivo) {
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}


	/* ---- Leer cada línea del archivo ---------------------------------- */
	while (fgets(buffer, sizeof(buffer), archivo) != NULL) {

		/* --- Eliminar el salto de línea al final de la cadena ----------------------------------------- */
		buffer[strcspn(buffer, "\r\n")] = '\0'; 
		printf_s("\nRealizando ping a la IP: %s", buffer);

		/* --- Reiniciar exitoso para cada IP ------------------ */
		exitoso = 0; 
		pingExitoso[0] = '\0';

		/* --- Comando ping con 4 paquetes ----------------------------------------------------- */
		char bufferPing[BUFFER_SIZE + 50];  
		snprintf(bufferPing, sizeof(bufferPing), "ping -n 4 %s", buffer); 
		

		/* ---- Ejecutar el comando ping y capturar la salida ---------------------------------- */
		archivoPingSalida = _popen(bufferPing, "r");
		if (!archivoPingSalida) {
			printf_s("Error al ejecutar ping para: %s\n", buffer);
			continue;
		}

		

		/* ---- Leer la salida del comando ping ---------------------------------- */
		while (fgets(bufferSalida, sizeof(bufferSalida), archivoPingSalida) != NULL) {
			printf_s("%s", bufferSalida);

			/* ---- Si contiene "tiempo" o "time", consideramos que hubo una respuesta ------------------ */
			if (strstr(bufferSalida, "TTL")) {
				exitoso = 1;
			}
			/* ---- Guardar la salida en pingExitoso a partir del éxito detectado ---------------------------------- */
			if (exitoso) {
				strcat_s(pingExitoso, sizeof(pingExitoso), bufferSalida);
			}
		}
		/* ---- Cerrar el archivo temporal ------------------------------- */
		_pclose(archivoPingSalida);
		
		/* ---- Guardar el resultado en producto2.txt ------------------------------- */
		if (exitoso) {
			/* --- Abrir el archivo en modo de añadir (append) ---------------- */
			fopen_s(&archivoTemporal, "archivoTemporal.txt", "a");
				
			if (exitoso && archivoTemporal) {
				fprintf(archivoTemporal, "\nPing a la IP: %s\n%s", buffer, pingExitoso);
				fclose(archivoTemporal);
				printf_s("\nPing exitoso para: %s\nGuardado en archivoTemporal.txt\n", buffer);
			}
			else if (exitoso && !archivoTemporal){
				perror("Error al abrir archivoTemporal.txt para escribir el resultado");
				exit(EXIT_FAILURE);
				
			}
		}
		else {
			printf_s("\nError: No se recibió respuesta de la IP %s\n", buffer);
		}

	}
	/* ---- Cerrar el archivo ------------------------------- */
	fclose(archivo);
	printf_s("Volviendo al menú Principal...\n");
	menuPrincipal();

}


		

	