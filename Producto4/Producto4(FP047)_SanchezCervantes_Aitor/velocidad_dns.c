#include "velocidad_dns.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "limpiar_buffer.h"



// Obtener la velocidad media de respuesta del servidor DNS
void obtener_velocidad_respuesta_dns(const char* dns, char* promedio) {
    char comando[256];
    sprintf_s(comando, sizeof(comando), "ping %s -n 4", dns);
    FILE* fp = _popen(comando, "r");
    if (!fp) {
        printf("Fallo al intentar ejecutar el comando ping.\n");
        return;
    }

    char line[LONG_BUFFER];
    char* token;
    char* context = NULL;

    while (fgets(line, sizeof(line), fp) != NULL) {
        // Buscar la línea que contiene "Media"
        if (strstr(line, "Media")) {
            // Extraer el valor numérico usando strtok_s
            token = strtok_s(line, "=", &context);
            while (token != NULL) {
                token = strtok_s(NULL, " ", &context); // Saltar el "Media ="
                if (token != NULL && strstr(token, "ms")) {
                    strcpy_s(promedio, LONG_BUFFER, token);
                    break;
                }
                token = strtok_s(NULL, "=", &context);
            }
        }
    }

    if (strlen(promedio) > 0) {
        printf("\nVelocidad media de respuesta del servidor DNS: %s\n", promedio);
    }
    else {
        printf("No se pudo determinar la velocidad media de respuesta del servidor DNS.\n");
    }

    _pclose(fp);
}

// Trazar la ruta al servidor DNS y devolver el número de saltos
int trazar_ruta_dns(const char* dns) {
    char comando[256];
    sprintf_s(comando, sizeof(comando), "tracert %s", dns);
    FILE* archivo = _popen(comando, "r");
    if (!archivo) {
        printf("Fallo al intentar ejecutar el comando tracert.\n");
        return 0;
    }

    char line[1024];
    int saltos = 0;

    printf("\nTrazando la ruta al servidor DNS %s:\n", dns);
    while (fgets(line, sizeof(line), archivo) != NULL) {
        printf("%s", line); // Mostrar cada línea de la salida de tracert
        if (strstr(line, "ms")) {
            saltos++;
        }
    }

    _pclose(archivo);

    if (saltos > 0) {
        printf("\nNúmero total de saltos: %d\n", saltos);
    }
    else {
        printf("No se pudo determinar el número de saltos.\n");
    }

    return saltos;
}
