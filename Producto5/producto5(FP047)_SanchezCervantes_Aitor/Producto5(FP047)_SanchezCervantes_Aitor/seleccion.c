#include <stdio.h>
#include <stdlib.h>
#include "crearXSLT.h"
#include "crearHTML.h"
#include "seleccion.h"

void mostrarMenu() {
    printf("\n**********MENU**********\n");
    printf("1. Crear archivo XSLT\n");
    printf("2. Crear archivo HTML\n");
    printf("3. Salir\n");
    printf("\nSeleccione una opción: ");
}

void procesarSeleccion(const char* xmlFilename, const char* xsltFilename, const char* htmlFilename) {
    int opcion;

    while (1) {
        mostrarMenu();
        if (scanf_s("%d", &opcion) != 1) {
            fprintf(stderr, "Entrada no válida. Por favor, seleccione una opción del 1 al 3.\n");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }

        switch (opcion) {
        case 1:
        {
            // Crear y escribir el archivo XSLT
            char* xsltContent = createXSLTFromXML(xmlFilename);
            if (xsltContent == NULL) {
                fprintf(stderr, "Error al crear el contenido XSLT.\n");
                return;
            }
            writeFile(xsltFilename, xsltContent);
            free(xsltContent);
        }
        break;

        case 2:
            // Generar el archivo HTML a partir del XML y XSLT
            transformXMLtoHTML(xmlFilename, xsltFilename, htmlFilename);
            break;

        case 3:
            printf("\nSaliendo...\n");
            return;

        default:
            fprintf(stderr, "Opción no válida. Por favor, seleccione una opción del 1 al 3.\n");
            break;
        }
    }
}
