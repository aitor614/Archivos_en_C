
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 512

void escogerAdaptador()
{
	/* ---- Variables ---------------------------------- */
    FILE* archivo;            
    FILE* archivoAdaptador;
	
    char  line[BUFFER_SIZE];
    char  adaptador[BUFFER_SIZE];

    int dentro = 0;          /* 1 = estamos en el bloque correcto      */
    int capturadas = 0;
    
    /* ---- Leer nombre del adaptador ---------------------------------- */
    printf_s("\n*************** SELECCIÓN DE ADAPTADOR DE RED ***************\n");
    printf_s("\nNombre exacto del adaptador: ");
    if (!fgets(adaptador, sizeof adaptador, stdin)) 
        return;

	/* ---- Eliminar salto de línea ---------------------------------- */
    adaptador[strcspn(adaptador, "\n")] = '\0';

    /* ---- Ejecutamos ipconfig ------------------------------------------ */
    archivo = _popen("ipconfig /all", "r");
    if (!archivo) { 
        perror("ipconfig"); 
        return; 
    }

	/* ---- Abrimos el archivo de salida ------------------------------------ */
    if (fopen_s(&archivoAdaptador, "adaptador.txt", "a") || !archivoAdaptador) {
        perror("adaptador.txt");
        _pclose(archivo); 
        return;
    }

	printf_s(archivoAdaptador, "\n*************** ADAPTADOR DE RED ***************\n");
	printf_s("\nAquí tienes los datos del adaptador escogido\n\n");


	/* ---- Leer el archivo y buscar el adaptador -------------------------- */
    while (fgets(line, sizeof line, archivo)) {
        if (strstr(line, "Adaptador") && strstr(line, adaptador)) {
            fprintf(archivoAdaptador, "%s", line);
            printf_s("%s", line);
            dentro = 1;
            continue;
        }

        if (!dentro) continue;

        /* --------- Líneas que nos interesan -------------------------- */
        if (strstr(line, "IPv4")) {
            fprintf(archivoAdaptador, "%s", line);
			printf_s("%s", line);
            ++capturadas;
        }
        else if (strstr(line, "subred")) {
            fprintf(archivoAdaptador, "%s", line);
            printf_s("%s", line);
            ++capturadas;
        }
        else if (strstr(line, "Puerta de enlace")) {
            fprintf(archivoAdaptador, "%s", line);
            printf_s("%s", line);
            fprintf(archivoAdaptador, "\n");
            fprintf(archivoAdaptador, "-----------------------------------------------------------------------------\n");
            ++capturadas;
        }

		

        /* cuando tengamos las 3, terminamos                            */
        if (capturadas == 3) 
            break;
    }

	/* ---- Cerramos el archivo de salida --------------------- */ 
	fclose(archivoAdaptador);

	/* ---- Cerrar el archivo ---------------------------------------- */
    _pclose(archivo);

	/* ---- Comprobamos si hemos capturado las 3 líneas -------------- */
    if (capturadas == 3)
        printf_s("\nInformación guardada en adaptador.txt\n");
    else
        printf_s("\nNo se encontró el adaptador o faltan datos en la salida.\n");
}



