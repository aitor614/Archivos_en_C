
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>


int main(void) {

	setlocale(LC_CTYPE, "spanish"); // Para poder imprimir caracteres especiales
	
	menuPrincipal();

}