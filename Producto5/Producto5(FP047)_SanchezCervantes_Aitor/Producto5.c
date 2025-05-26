#include <stdio.h>
#include "seleccion.h"
#include <locale.h>


int main() {
    // Cambiar la página de códigos a UTF-8

    setlocale(LC_CTYPE, "spanish"); // Para poder imprimir caracteres especiales

    const char* xmlFilename = "configuracion_red.xml";
    const char* xsltFilename = "configuracion_red.xslt";
    const char* htmlFilename = "configuracion_red.html";

    procesarSeleccion(xmlFilename, xsltFilename, htmlFilename);

    return 0;
}

