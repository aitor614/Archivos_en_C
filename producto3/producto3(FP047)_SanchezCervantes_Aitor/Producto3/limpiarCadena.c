
#include <stdio.h>


void limpiarCadena(char* str) {
    str[strcspn(str, "\r\n")] = 0;
    size_t cadena = strlen(str);
    while (cadena > 0 && str[cadena - 1] == ' ') {
        str[--cadena] = '\0';
    }
}