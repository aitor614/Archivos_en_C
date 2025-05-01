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
  char* linea = (char*)malloc(BUFFER_SIZE); // Cambiado a puntero de char  
  char adaptador[MAX_ADAPTADORES][BUFFER_SIZE];  
  int contador = 0;  
  int num_adaptadores = 0;  
  int lineasSaltadas = 0;  

  /* --- Comprobar si la memoria fue asignada correctamente ------------------ */  
  if (linea == NULL) {  
      perror("Error asignando memoria para 'linea'");  
      return;  
  }  

  /* --- Ejecutar el comando netsh ------------------ */  
  archivo = _popen("netsh interface show interface", "r");  

  /* --- Comprobar si el comando se ejecutó correctamente --------------------- */  
  if (!archivo) {  
      perror("Error ejecutando netsh");  
      free(linea); // Liberar memoria antes de salir  
      return;  
  }  

  // Leer línea por línea e identificar los nombres  
  while (fgets(linea, BUFFER_SIZE, archivo)) { 
      // Saltar las primeras 3 líneas de cabecera  
      if (lineasSaltadas < 3) {  
          lineasSaltadas++;  
          continue;  
      }  

      /* --- Extraer la última columna que es el nombre del adaptador -------------*/  
      char* ultimo_token = strrchr(linea, ' ');  

      /* --- Comprobar si se encontró el último token---------------------- */  
      if (ultimo_token) {  

          /* --- Mover el puntero al primer carácter no espacio en blanco ----------------- */  
          while (*ultimo_token == ' ') ultimo_token++;  

          /* --- Eliminar el salto de línea al final de la cadena ------------------------- */  
          ultimo_token[strcspn(ultimo_token, "\r\n")] = 0;  

          /* --- Comprobar si el adaptador ya fue capturado --------------------- */  
          if (strlen(ultimo_token) > 0 && num_adaptadores < MAX_ADAPTADORES) {  
              strcpy_s(adaptador[num_adaptadores], BUFFER_SIZE, ultimo_token);  
              printf("%d) %s\n", num_adaptadores + 1, ultimo_token);  
              num_adaptadores++;  
          }  
      }  
  }  

  _pclose(archivo);  
  free(linea); // Liberar memoria después de usarla  
}
