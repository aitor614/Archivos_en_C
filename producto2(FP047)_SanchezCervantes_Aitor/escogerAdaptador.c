#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 512

void escogerAdaptador()
{
   
	/* --- Variables ---------------------------------- */
    FILE* archivo = NULL;           
    FILE* archivoAdaptador = NULL;  
    char  line[BUFFER_SIZE];
    char  adaptador[BUFFER_SIZE];
    int   dentro = 0, capturadas = 0;

    /* --- Pedir nombre del adaptador -------------------------- */
    printf("\n*************** SELECCIÓN DE ADAPTADOR DE RED ***************\n");
    printf("Nombre exacto del adaptador: ");

	/* --- Leer el nombre del adaptador introducido por el usuario ------------------------ */
    if (!fgets(adaptador, sizeof adaptador, stdin)) return;
    adaptador[strcspn(adaptador, "\n")] = '\0';

    /* --- Lanzar ipconfig /all ---------------------- */
    archivo = _popen("ipconfig /all", "r");
    if (!archivo) {
        perror("ipconfig"); 
        return; 
    }

    /* --- Abrir/crear adaptador.txt (modo añadir) ---------------- */
    if (fopen_s(&archivoAdaptador, "adaptador.txt", "a") != 0 || !archivoAdaptador) {
        perror("adaptador.txt");
        _pclose(archivo);
        return;
    }

    /* --- cabecera ---------------------------------------- */
    fprintf(archivoAdaptador,
        "\n*************** ADAPTADOR DE RED ***************\n"
        "Datos del adaptador escogido:\n\n");
    printf("\n*************** ADAPTADOR DE RED ***************\n"
        "Datos del adaptador escogido:\n\n");

    /* --- Recorrer la salida de ipconfig -------------------- */
    while (fgets(line, sizeof line, archivo)) {

        if (strstr(line, "Adaptador") && strstr(line, adaptador)) {
            fprintf(archivoAdaptador, "%s", line);
            printf("%s", line);
            dentro = 1;
            continue;
        }
        if (!dentro) continue;

        if (strstr(line, "IPv4")) {
            fprintf(archivoAdaptador, "%s", line);
            printf("%s", line);
            ++capturadas;
        }
        else if (strstr(line, "subred")) {
            fprintf(archivoAdaptador, "%s", line);
            printf("%s", line);
            ++capturadas;
        }
        else if (strstr(line, "Puerta de enlace")) {
            fprintf(archivoAdaptador, "%s", line);
            printf("%s", line);
            fprintf(archivoAdaptador,
                "-------------------------------------------------------------\n");
            ++capturadas;
        }

        if (capturadas == 3) break;
    }

    /* --- Cerrar archivos ---------------------------------------------------------*/
    fclose(archivoAdaptador);
    _pclose(archivo);

    /* --- Mensaje final ----------------------------------------------- */
    if (capturadas == 3)
        printf("\nInformación guardada en adaptador.txt\n");
    else
        printf("\nNo se encontró el adaptador o faltan datos en la salida.\n");
}
