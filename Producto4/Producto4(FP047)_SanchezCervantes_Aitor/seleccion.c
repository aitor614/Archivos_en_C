#include "seleccion.h"
#include "adaptador.h"
#include "limpiar_buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


void seleccionar() {
    char adaptadores[10][LONG_BUFFER];

    // Listar y seleccionar adaptadores
    printf("\nAdaptadores de red disponibles:\n");
    int num_adaptadores = listar_adaptadores(adaptadores, 10);
    if (num_adaptadores == 0) {
        printf("No se encontraron adaptadores de red.\n");
        return;
    }

    int eleccion;
    do {
        printf("Seleccione el número del adaptador para ver su configuración: ");
        if (scanf_s("%d", &eleccion) != 1) {
            printf("Error al leer la entrada.\n");
            limpiar_stdin();
            continue;
        }
        limpiar_stdin(); 
        if (eleccion > 0 && eleccion <= num_adaptadores) {
            mostrar_informacion_del_adaptador(adaptadores[eleccion - 1]);
            break;
        }
        else {
            printf("Selección inválida.\n");
        }
    } while (1);
}