#include "limpiar_buffer.h"
#include <stdio.h>

// Limpiar el buffer de entrada
void limpiar_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {} // Limpiar el buffer hasta el final de la línea o archivo
}