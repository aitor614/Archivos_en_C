#include "menuPrincipal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

int main(void) {

	/* --- Para poder imprimir caracteres especiales ---------------------- */
	setlocale(LC_ALL, "spanish");

	/* --- Funci�n para ir al men� Principal ------------- */
	menuPrincipal();

}