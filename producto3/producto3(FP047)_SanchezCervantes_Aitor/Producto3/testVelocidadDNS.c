#include "limpiarCadena.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 1024

void velocidadDNS(char* mejorDNS, size_t size) {

	/* ---- Variables ---------------------------------- */

	char ip[BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	char bufferSalida[BUFFER_SIZE];
	int mejorTiempo = -1;
	int menosSaltos = -1;


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

			limpiarCadena(ip);

			char* velocidad = strstr(bufferSalida, "tiempo="); // Buscar la cadena "tiempo=" en minúsculas
			char* salto = strstr(bufferSalida, "TTL"); // Buscar la cadena "TTL" en mayusculas
			if (velocidad != NULL) {

				int tiempoRespuesta;
				int saltoDNS;

				/* --- Extraer el valor de tiempo de respuesta --------------------- */
				if (sscanf_s(velocidad, "tiempo=%d", &tiempoRespuesta) == 1) {
					/* --- Extraer el valor de TTL --------------------- */
					
					/* --- Extraer el valor de los saltos de respuesta --------------------- */
					sscanf_s(salto, "TTL=%d", &saltoDNS);

					/* --- Mostrar el tiempo de respuesta  y los saltos --------------------- */
					printf_s("Tiempo de respuesta: %d ms \nSaltos: %d TTL\n", tiempoRespuesta, saltoDNS);
					encontrado = true;

					/* --- Guardar la IP más rápida si es la primera o la mejor hasta ahora ------------------------ */
					if (mejorTiempo == -1 || tiempoRespuesta < mejorTiempo) {
						mejorTiempo = tiempoRespuesta;
						menosSaltos = saltoDNS;

						strcpy_s(mejorDNS, BUFFER_SIZE *2, ip);
						
					}

					else if (tiempoRespuesta == mejorTiempo) {
						/* --- Guardar la IP con menos saltos si el tiempo es el mismo ------------------------ */
						if (menosSaltos == -1 || saltoDNS < menosSaltos) {
							mejorTiempo = tiempoRespuesta;
							menosSaltos = saltoDNS;
							strcpy_s(mejorDNS, BUFFER_SIZE * 2, ip);
						}
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
	remove("archivoTemporal.txt");
	// Mostrar la IP más rápida 
	if (mejorTiempo != -1 && menosSaltos != -1) {
		printf_s("\nLa IP más rápida es: %s con %d ms y %d TTL\n", mejorDNS, mejorTiempo, menosSaltos);
	}
	else {
		printf_s("\nNo se obtuvo respuesta de ninguna IP.\n");
	}

}

