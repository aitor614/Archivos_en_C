#include "limpiar_buffer.h"
#include "menuPrincipal.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>




int main() {

    // Cambiar la p�gina de c�digos a UTF-8
    
	setlocale(LC_CTYPE, "spanish"); // Para poder imprimir caracteres especiales


	// Mostrar el men� principal
	menuPrincipal();

    

   
}





