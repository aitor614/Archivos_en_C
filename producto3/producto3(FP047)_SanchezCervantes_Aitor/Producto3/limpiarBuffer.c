#include <stdio.h>


/* --- Función para limpiar el búfer de entrada ------------------------ */
void limpiar_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}