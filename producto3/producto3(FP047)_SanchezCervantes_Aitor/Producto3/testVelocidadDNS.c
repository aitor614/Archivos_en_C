#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 1024

void velocidadDNS() {

	/* ---- Variables ---------------------------------- */

	char ip[BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	char bufferSalida[BUFFER_SIZE];
	int mejorTiempo = -1;
	char mejorIP[BUFFER_SIZE] = "";

	/* -Abrir el archivo temporal en modo lectura -------------------------------- */
	FILE* archivo;
	if (fopen_s(&archivo, "archivoTemporal.txt", "r") != 0 || !archivo) {
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}

	/* ---- Leer cada línea del archivo ---------------------------------- */
	while (fgets(ip, sizeof(ip), archivo) != NULL) {

		/* --- Eliminar el salto de linea al final de la cadena ----------------------------------------- */
		ip[strcspn(ip, "\r\n")] = '\0';

		printf_s("\nRealizando ping a la IP: %s\n", ip);

		/* --- Comprovar la velocidad del DNS --------------------------- */

		/* --- Hacemos ping ------------------------------ */
		snprintf(buffer, sizeof(buffer), "ping -n 1 -w 1000 %s", ip);

		/* ---- Ejecutar el comando ping y capturar la salida ---------------------------------- */
		FILE* archivoPingSalida = _popen(buffer, "r");
		if (!archivoPingSalida) {
			printf_s("Error al ejecutar ping para: %s\n", buffer);
			continue;
		}

		bool encontrado = false; // Variable para verificar si se encontró el tiempo de respuesta



		/* ---- Leer la salida del comando ping ---------------------------------- */
		while (fgets(bufferSalida, sizeof(bufferSalida), archivoPingSalida) != NULL) {

			char* velocidad = strstr(bufferSalida, "tiempo="); // Buscar la cadena "tiempo=" en minúsculas
			if (velocidad != NULL) {
				int tiempoRespuesta;
				if (sscanf_s(velocidad, "tiempo=%d", &tiempoRespuesta) == 1) {
					printf_s("Tiempo de respuesta: %d ms\n", tiempoRespuesta);
					encontrado = true;

					/* --- Guardar la IP más rápida si es la primera o la mejor hasta ahora ------------------------ */
					if (mejorTiempo == -1 || tiempoRespuesta < mejorTiempo) {
						mejorTiempo = tiempoRespuesta;
						strcpy_s(mejorIP, sizeof(mejorIP), ip);
					}

				}
				else {
					printf_s("Error al extraer el tiempo de respuesta.\n");
				}
			}
		}

		if (!encontrado) {
			printf_s("No se pudo obtener el tiempo de respuesta para %s\n", ip);
		}

		_pclose(archivoPingSalida);
	}

	fclose(archivo);

	// Mostrar la IP más rápida
	if (mejorTiempo != -1) {
		printf_s("\nLa IP más rápida es: %s con %d ms\n", mejorIP, mejorTiempo);
	}
	else {
		printf_s("\nNo se obtuvo respuesta de ninguna IP.\n");
	}
}

