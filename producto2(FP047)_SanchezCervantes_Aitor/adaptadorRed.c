# include "escogerAdaptador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

void mostrarAdaptador() {

	/* -- Variables ---------------------------------- */
	FILE* archivo;
	char buffer[BUFFER_SIZE];
    char line[BUFFER_SIZE];

    /* -- Ejecutar ipconfig ---------------------------------- */
    archivo = _popen("ipconfig /all", "r");

	if (!archivo) {
		perror("_popen");
        return;
	}
    
    /* -- Listar adaptadores ---------------------------------- */
    printf_s("\nAdaptadores de red disponibles:\n");
    while (fgets(line, sizeof(line), archivo) != NULL) {
        if (strstr(line, "Adaptador de")) {
            printf("%s", line);
        }
    }

    /* -- Cerrar el archivo ---------------------------------- */
    _pclose(archivo);

	/* -- Pedir al usuario que seleccione un adaptador -------- */
    escogerAdaptador();
}
