#include <stdio.h>


/* --- Funci�n para limpiar el b�fer de entrada ------------------------ */
void limpiar_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}