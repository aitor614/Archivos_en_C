#include "adaptador.h"
#include "limpiar_buffer.h"
#include "velocidad_dns.h"
#include "xml.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>



// Eliminar espacios en blanco al principio y al final de una cadena
void trim_whitespace(char* str) {
    char* end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    // Trim trailing space
    if (*str == 0) return;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';
}

// Mostrar información del adaptador de red
void mostrar_informacion_del_adaptador(const char* adaptador) {
    char comando[256];
    sprintf_s(comando, sizeof(comando), "netsh interface ipv4 show config name=\"%s\"", adaptador);
    FILE* fp = _popen(comando, "r");
    if (!fp) {
        printf("Fallo al intentar ejecutar el comando, puede que necesite permisos de administrador.\n");
        return;
    }

    char line[LONG_BUFFER];
    char ip[LONG_BUFFER] = "";
    char mascara_subred[LONG_BUFFER] = "";
    char puerta_enlace[LONG_BUFFER] = "";
    char dns[LONG_BUFFER] = "";
    char velocidad_media[LONG_BUFFER] = "";
    int numero_saltos = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line); // Mostrar cada línea de la salida de netsh

        // Extraer la IP
        if (strstr(line, "IP")) {
            char* start = strchr(line, ':');
            if (start) {
                start += 1; // Saltar el ":"
                while (isspace((unsigned char)*start)) start++; // Saltar espacios en blanco
                strcpy_s(ip, sizeof(ip), start);
                trim_whitespace(ip);
                char* end = strchr(ip, '\n');
                if (end) {
                    *end = '\0';
                }
            }
        }

        // Extraer la máscara de subred
        if (strstr(line, "Prefijo de subred")) {
            char* start = strchr(line, ':');
            if (start) {
                start += 1; // Saltar el ":"
                while (isspace((unsigned char)*start)) start++; // Saltar espacios en blanco
                strcpy_s(mascara_subred, sizeof(mascara_subred), start);
                trim_whitespace(mascara_subred);
                char* end = strchr(mascara_subred, '\n');
                if (end) {
                    *end = '\0';
                }
            }
        }

        // Extraer la puerta de enlace
        if (strstr(line, "Puerta de enlace") || strstr(line, "Default Gateway")) {
            char* start = strchr(line, ':');
            if (start) {
                start += 1; // Saltar el ":"
                while (isspace((unsigned char)*start)) start++; // Saltar espacios en blanco
                strcpy_s(puerta_enlace, sizeof(puerta_enlace), start);
                trim_whitespace(puerta_enlace);
                char* end = strchr(puerta_enlace, '\n');
                if (end) {
                    *end = '\0';
                }
            }
        }

        // Extraer el servidor DNS
        if (strstr(line, "Servidores DNS configurados") || strstr(line, "DNS Servers")) {
            char* start = strchr(line, ':');
            if (start) {
                start += 1; // Saltar el ":"
                while (isspace((unsigned char)*start)) start++; // Saltar espacios en blanco
                strcpy_s(dns, sizeof(dns), start);
                trim_whitespace(dns);
                char* end = strchr(dns, '\n');
                if (end) {
                    *end = '\0';
                }
            }
        }
    }

    _pclose(fp);

    if (strlen(ip) > 0) {
        printf("\nIP: %s\n", ip);
    }
    else {
        printf("No se encontró una dirección IP.\n");
    }

    if (strlen(mascara_subred) > 0) {
        printf("\nMáscara de Subred: %s\n", mascara_subred);
    }
    else {
        printf("No se encontró una máscara de subred.\n");
    }

    if (strlen(puerta_enlace) > 0) {
        printf("\nPuerta de Enlace: %s\n", puerta_enlace);
    }
    else {
        printf("No se encontró una puerta de enlace.\n");
    }

    if (strlen(dns) > 0) {
        printf("\nServidor DNS: %s\n", dns);
        obtener_velocidad_respuesta_dns(dns, velocidad_media);
        numero_saltos = trazar_ruta_dns(dns);

        printf("\nGenerando archivo XML...\n");
        crear_archivo_xml(ip, mascara_subred, puerta_enlace, dns, velocidad_media, numero_saltos);
        printf("Archivo XML generado: configuracion_red.xml\n");
    }
    else {
        printf("No se encontró un servidor DNS configurado.\n");
    }
}

// Listar adaptadores de red disponibles
int listar_adaptadores(char adaptadores[][LONG_BUFFER], int max_adaptadores) {
    FILE* fp = _popen("netsh interface show interface", "r");
    if (!fp) {
        perror("Failed to run command");
        exit(1);
    }

    char line[LONG_BUFFER];
    int count = 0;
    while (fgets(line, sizeof(line), fp) != NULL && count < max_adaptadores) {
        if (strstr(line, "Ethernet") || strstr(line, "Wi-Fi")) {
            char* name_start = strstr(line, "Ethernet");
            if (!name_start) {
                name_start = strstr(line, "Wi-Fi");
            }
            if (name_start) {
                // Salta espacios iniciales y caracteres especiales
                while (*name_start == ' ' || *name_start == '\t') {
                    name_start++;
                }
                char* name_end = strchr(name_start, '\n');
                if (name_end) {
                    *name_end = '\0';
                }
                strncpy_s(adaptadores[count], LONG_BUFFER, name_start, LONG_BUFFER - 1);
                printf("%d. %s\n", count + 1, name_start); // Mostrar el nombre del adaptador
                count++;
            }
        }
    }
    _pclose(fp);
    return count;
}
