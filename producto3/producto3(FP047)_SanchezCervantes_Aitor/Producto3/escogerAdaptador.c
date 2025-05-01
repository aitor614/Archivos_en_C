#include "limpiarBuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ADAPTADORES 20
#define BUFFER_SIZE 512



/* --- Función principal para escoger un adaptador de red y mostrar su configuración ---- */
void escogerAdaptador() {

    /* --- Variables ---------------------------------- */
    char adaptadores[MAX_ADAPTADORES][BUFFER_SIZE]; // Almacena los nombres de los adaptadores encontrados
    int num_adaptadores = 0; // Contador de adaptadores encontrados
    char linea[BUFFER_SIZE]; // Almacén temporal para líneas leídas del comando
    int lineasSaltadas = 0; // Número de líneas de cabecera a ignorar



    /* --- Ejecutar comando netsh para mostrar interfaces ------------------ */
    FILE* fp = _popen("netsh interface show interface", "r");

    /* --- Comprobar si el comando se ejecutó correctamente -------------------- */
    if (!fp) {
        perror("Error ejecutando netsh");
        return;
    }

    /* --- Leer línea por línea e identificar los nombres de los adaptadores ---- */
    while (fgets(linea, sizeof(linea), fp)) {

        if (lineasSaltadas < 3) { // Saltar cabecera de la salida del comando
            lineasSaltadas++;
            continue;
        }

        // Extraer la última columna (nombre del adaptador)
        char* ultimo_token = strrchr(linea, ' ');
        if (ultimo_token) {
            // Limpiar espacios finales
            while (*ultimo_token == ' ') ultimo_token++;
            ultimo_token[strcspn(ultimo_token, "\r\n")] = 0;

            if (strlen(ultimo_token) > 0 && num_adaptadores < MAX_ADAPTADORES) {
                strcpy_s(adaptadores[num_adaptadores], BUFFER_SIZE, ultimo_token); // Guardar nombre del adaptador
                printf("%d) %s\n", num_adaptadores + 1, ultimo_token); // Mostrar al usuario
                num_adaptadores++;
            }
        }
    }

    _pclose(fp);

	/* --- Comprobar si se encontraron adaptadores --------------------- */
    if (num_adaptadores == 0) {
        printf("No se detectaron adaptadores.\n");
        return;
    }

    /* --- Solicitar al usuario que elija un adaptador ------------------- */
    int seleccion = 0;
    do {
        printf("\nSeleccione el número del adaptador: ");
        if (scanf_s("%d", &seleccion) != 1 || seleccion < 1 || seleccion > num_adaptadores) {
            printf("Entrada no válida. Intente de nuevo.\n");
            limpiar_stdin();
        }
        else {
            limpiar_stdin();
            break;
        }
    } while (1);

	/* --- Comprobar si la selección es válida --------------------- */
    const char* adaptador = adaptadores[seleccion - 1]; // Nombre del adaptador seleccionado

    /* --- Formar y ejecutar comando netsh para ver la configuración IP del adaptador --- */
    char comando[BUFFER_SIZE * 2];
    sprintf_s(comando, sizeof(comando), "netsh interface ipv4 show config name=\"%s\"", adaptador);


    FILE* salida = _popen(comando, "r");
    if (!salida) {
        perror("Error ejecutando netsh para ver configuración");
        return;
    }

    /* --- Abrir archivo de salida para guardar la configuración -------- */
    FILE* archivo = NULL;
    if (fopen_s(&archivo, "adaptador.txt", "a") != 0 || !archivo) {
        perror("Error abriendo adaptador.txt");
        _pclose(salida);
        return;
    }

    printf("\n*************** CONFIGURACIÓN DEL ADAPTADOR '%s' ***************\n\n", adaptador);
    fprintf(archivo, "\n*************** CONFIGURACIÓN DEL ADAPTADOR '%s' ***************\n\n", adaptador);

    /* --- Escribir la configuración en pantalla y en archivo ----------- */
    bool dns_mostrado = false;

    while (fgets(linea, sizeof(linea), salida)) {
        if (strstr(linea, "Servidores DNS") && !dns_mostrado) {
            // Buscar la parte después de los dos puntos
            char* ptr = strchr(linea, ':');
            if (ptr) {
                ptr += 1; // Saltar el ':' 
                while (*ptr == ' ' || *ptr == '\t') ptr++; // Saltar espacios

                // Eliminar salto de línea al final
                ptr[strcspn(ptr, "\r\n")] = 0;

                printf("DNS configurado: %s\n", ptr);
                fprintf(archivo, "DNS configurado: %s\n", ptr);
                dns_mostrado = true;
            }
        }
    }


    fclose(archivo);
    _pclose(salida);

    printf("\nConfiguración guardada en 'adaptador.txt'\n");
}
