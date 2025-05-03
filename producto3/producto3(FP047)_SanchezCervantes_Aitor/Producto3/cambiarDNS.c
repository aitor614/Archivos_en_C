
#include "limpiarBuffer.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void cambioDNS(const char* dnsEquipo, const char* mejorDNS) {

	/* --- Comprobar si el DNS actual es el mejor --------------------- */
    if (strcmp(dnsEquipo, mejorDNS) == 0) {
        printf("Ya estás usando el DNS más rápido.\n");
        return;
    }


	/* --- Preguntar al usuario si desea cambiar el DNS --------------------- */
    printf("¿Deseas cambiar el DNS al más rápido (%s)? (s/n): ", mejorDNS);
    char respuesta;
    scanf_s(" %c", &respuesta, 1);

	// Limpiar el buffer de entrada
    limpiar_stdin();

    if (respuesta != 's' && respuesta != 'S') {
        printf("No se cambió el DNS.\n");
        return;
    }

    
    
    char comando[BUFFER_SIZE];

	// Formar el comando para cambiar el DNS
    snprintf(comando, sizeof(comando),
        "netsh interface ip set dns name=\"Ethernet\" static %s", mejorDNS);

	// Ejecutar el comando para cambiar el DNS
    FILE* salida = _popen(comando, "r");
    if (!salida) {
        perror("Error al ejecutar el comando para cambiar DNS");
        return;
    }
        
    char buffer[BUFFER_SIZE];
	// Leer la salida del comando
    while (fgets(buffer, sizeof(buffer), salida) != NULL) {
        printf("%s", buffer);  // Muestra la salida del comando netsh
    }

    _pclose(salida);
    printf("DNS cambiado a %s.\n", mejorDNS);
}






