#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seleccion.h"
#include "limpiar_buffer.h"





void menuPrincipal() {


    int opcion;
    do {
        printf("\nMenu Principal:\n");
        printf("1. Mostrar información del adaptador\n");
        printf("2. Salir\n");
        printf("Seleccione una opcion: ");
        if (scanf_s("%d", &opcion) != 1) {
            printf("Error al leer la entrada.\n");
            limpiar_stdin();
            continue;
        }
        limpiar_stdin(); // Limpiar buffer de entrada

        switch (opcion) {
        case 1:
            seleccionar();
            break;
        case 2:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 2);

    return 0;

}
