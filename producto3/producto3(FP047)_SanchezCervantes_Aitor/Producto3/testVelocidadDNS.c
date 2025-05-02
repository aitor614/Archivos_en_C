#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define BUFFER_SIZE 1024




void velocidadDNS() {

	/* ---- Variables ---------------------------------- */ 
	
	/* ---- Abrir archivo con las IPs en modo lectura ---------------------------------- */

	FILE* archivo;
	if (fopen_s(&archivo, "archivoTemporal.txt", "r") != 0 || !archivo) {
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}


	/* -Abrir el archivo temporal rn modo lectura -------------------------------- */

	FILE* archivoTemporal;
	if (fopen_s(&archivoTemporal, "DNSTemporal.txt", "r") != 0 || !archivoTemporal) {
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}

	/* ---- Variables para almacenar la IP y el tiempo de respuesta ------------------ */
	char ip[BUFFER_SIZE];
	char tiempo[BUFFER_SIZE];
	int exitoso = 0;
	char pingExitoso[BUFFER_SIZE * 10] = "";
	char buffer[BUFFER_SIZE];
	char bufferSalida[BUFFER_SIZE];
	char bufferPing[BUFFER_SIZE + 50];
	int tiempoRespuesta = 0;
	

	/* ---- Leer cada línea del archivo ---------------------------------- */
	while (fgets(ip, sizeof(ip), archivo) != NULL) {
		/* --- Eliminar el salto de linea al final de la cadena ----------------------------------------- */
		ip[strcspn(ip, "\r\n")] = '\0';
		printf_s("\nRealizando ping a la IP: %s", ip);
		/* --- Reiniciar exitoso para cada IP ------------------ */
		exitoso = 0;
		pingExitoso[0] = '\0';
	
		/* --- Comprovar la velocidad del DNS --------------------------- */
		snprintf(bufferPing, sizeof(bufferPing), "ping -n 4 %s", ip);
		/* ---- Ejecutar el comando ping y capturar la salida ---------------------------------- */
		FILE* archivoPingSalida = _popen(bufferPing, "r");
		if (!archivoPingSalida) {
			printf_s("Error al ejecutar ping para: %s\n", ip);
			continue;
		}
		/* ---- Leer la salida del comando ping ---------------------------------- */
		while (fgets(bufferSalida, sizeof(bufferSalida), archivoPingSalida) != NULL) {
			printf_s("%s", bufferSalida);
			/* ---- Si contiene "tiempo" o "time", consideramos que hubo una respuesta ------------------ */
			if (strstr(bufferSalida, "tiempo") || strstr(bufferSalida, "time")) {
				exitoso = 1;
				/* --- Extraer el tiempo de respuesta ------------------ */
				sscanf_s(bufferSalida, "%*[^=]=%dms", &tiempoRespuesta);
				break;
			}
		}
		/* ---- Cerrar el archivo de salida ------------------------------- */
		_pclose(archivoPingSalida);

		/* ---- Guardar la salida en pingExitoso a partir del éxito detectado ---------------------------------- */
		if (exitoso) {
			strcat_s(pingExitoso, sizeof(pingExitoso), bufferSalida);
		}
		else {
			printf_s("No se recibió respuesta de la IP: %s\n", ip);
		}
		/* ---- Guardar el tiempo de respuesta en el archivo temporal ------------------------------- */
		fprintf(archivoTemporal, "IP: %s, Tiempo de respuesta: %d ms\n", ip, tiempoRespuesta);
		printf_s("Tiempo de respuesta: %d ms\n", tiempoRespuesta);

		/* ---- Limpiar el buffer de pingExitoso ------------------------------- */
		pingExitoso[0] = '\0';
			
		/* --- Capturar los saltos -----------------------*/
		while (fgets(buffer, sizeof(buffer), archivoTemporal) != NULL) {
			printf_s("%s", buffer);
		}
		/* ---- Cerrar el archivo temporal ------------------------------- */
		fclose(archivoTemporal);
		/* ---- Cerrar el archivo de salida ------------------------------- */
		fclose(archivo);

		



	}
	







}