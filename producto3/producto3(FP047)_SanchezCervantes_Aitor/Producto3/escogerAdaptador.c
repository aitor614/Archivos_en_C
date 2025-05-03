#include "limpiarBuffer.h"
#include "limpiarCadena.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ADAPTADORES 20
#define BUFFER_SIZE 512



/* --- Función principal para escoger un adaptador de red y mostrar su configuración ---- */
void escogerAdaptador(char* dnsEquipo, size_t size) {

    /* --- Variables ---------------------------------- */
    char adaptadores[MAX_ADAPTADORES][BUFFER_SIZE]; // Almacena los nombres de los adaptadores encontrados
    int num_adaptadores = 0; // Contador de adaptadores encontrados
    char linea[BUFFER_SIZE]; // Almacén temporal para líneas leídas del comando
    int lineasSaltadas = 0; // Número de líneas de cabecera a ignorar
	


    /* --- Ejecutar comando netsh para mostrar interfaces ------------------ */
    FILE* salidaAdaptador = _popen("netsh interface show interface", "r");

    /* --- Comprobar si el comando se ejecutó correctamente -------------------- */
    if (!salidaAdaptador) {
        perror("Error ejecutando netsh");
        return;
    }

    printf_s("\n*************** ADAPTADORES DISPONIBLES ***************\n");

    /* --- Leer línea por línea e identificar los nombres de los adaptadores ---- */
    while (fgets(linea, sizeof(linea), salidaAdaptador)) {

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

    _pclose(salidaAdaptador);

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
    if (fopen_s(&archivo, "archivoTemporal.txt", "a") != 0 || !archivo) {
        perror("Error abriendo archivoTemporal.txt");
        _pclose(salida);
        return;
    }

    printf("\n*************** CONFIGURACIÓN DEL ADAPTADOR '%s' ***************\n\n", adaptador);
    

    /* --- Escribir la configuración en pantalla y en archivo ----------- */
    bool dns_mostrado = false;
	; // Almacena el DNS encontrado;
    /* --- Leer la salida del comando y buscar información de DNS ----------- */
    while (fgets(linea, sizeof(linea), salida)) {
        if (strstr(linea, "Servidores DNS")) {

            // Buscar la parte después de ':'
            char* valorDNS = strchr(linea, ':');
            if (valorDNS) {
                valorDNS++;
                while (*valorDNS == ' ' || *valorDNS == '\t') valorDNS++;
                limpiarCadena(valorDNS);

                // Mostrar el DNS en pantalla una sola vez
                if (!dns_mostrado) {

                    /* --- Validar si el valor es una IP válida ---------- */
                    int a, b, c, d;
                    if (sscanf_s(valorDNS, "%d.%d.%d.%d", &a, &b, &c, &d) == 4 &&
                        a >= 0 && a <= 255 &&
                        b >= 0 && b <= 255 &&
                        c >= 0 && c <= 255 &&
                        d >= 0 && d <= 255) {
						
						
                        strcpy_s(dnsEquipo, BUFFER_SIZE, valorDNS);
                        fprintf(archivo, "%s\n", valorDNS);
                        printf("DNS configurado: %s\n", dnsEquipo);
                        break;
                    }
                    else {
                        printf("El valor encontrado no es una IP válida, no se guarda.\n");
                    }

                    dns_mostrado = true; // Marcamos que ya se ha procesado un DNS
				}
				else {
                    printf("No se ha encontrado ningún DNS configurado para este adaptador.\n");
                }
            }
		}

        
	}
    fclose(archivo);
    _pclose(salida);
	

   
}


