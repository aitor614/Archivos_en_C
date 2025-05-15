#include "limpiar_buffer.h"
#include "menuPrincipal.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>




int main() {

    // Cambiar la página de códigos a UTF-8
    
	setlocale(LC_CTYPE, "spanish"); // Para poder imprimir caracteres especiales


	// Mostrar el menú principal
	menuPrincipal();

    

   
}





