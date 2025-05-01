#include "menuPrincipal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define BUFFER_SIZE 256
#define MAX_ADAPTADORES 20

void adaptadorRed() {

   /* --- Variables ---------------------------------- */
   FILE* archivo; 
   char buffer[BUFFER_SIZE];
   char linea[BUFFER_SIZE];
   char adaptador[MAX_ADAPTADORES][BUFFER_SIZE];
   int contador = 0;
   
   
   /* --- Ejecutar el comando netsh ------------------ */
   archivo = _popen("netsh interface show interface", "r");

   /* --- Comprobar si el comando se ejecutó correctamente --------------------- */
   if (!archivo) {
       perror("Error al ejecutar el comando");
       menuPrincipal();
       return;
   }
   
   /* --- Leer la salida del comando ----------------- */
   while (fgets(linea, sizeof(buffer), archivo) != NULL) {

       if (strstr(linea, "----") || strlen(linea) < 5)
           continue;

       char* posicion = linea + strlen(linea) - 1;

       while (posicion > linea && *posicion != ' ')
           posicion--;

       if (posicion == linea)
           continue;

       if (strcpy_s(adaptador[contador], BUFFER_SIZE, posicion + 1) != 0) {
           fprintf(stderr, "Error al copiar el adaptador elegido\n");
           continue;
       }
       contador++;
       if (contador >= MAX_ADAPTADORES)
           break;
   }
   _pclose(archivo);


   /* --- Mostrar los adaptadores encontrados -------- */
   if (contador == 0) {
       printf("No se encontraron adaptadores de red.\n");
       menuPrincipal();
       return;
   }

   for (int i = 0; i < contador; i++) {
       printf("  %2d) %s\n", i + 1, adaptador[i]);
   }

 
 
}

