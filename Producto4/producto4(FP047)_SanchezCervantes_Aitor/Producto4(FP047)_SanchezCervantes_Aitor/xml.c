#include "xml.h"
#include <stdio.h>
#include <stdlib.h>

#define LONG_BUFFER 1024

void crear_archivo_xml(const char* ip, const char* mascara_subred, const char* puerta_enlace, const char* dns, const char* velocidad_media, int numero_saltos, char ip_saltos[][LONG_BUFFER]) {
    FILE* file = fopen("configuracion_red.xml", "w");
    if (file == NULL) {
        perror("Error al crear el archivo XML");
        return;
    }

    fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(file, "<ConfiguracionRed>\n");
    fprintf(file, "    <IP>%s</IP>\n", ip);
    fprintf(file, "    <MascaraSubred>%s</MascaraSubred>\n", mascara_subred);
    fprintf(file, "    <PuertaEnlace>%s</PuertaEnlace>\n", puerta_enlace);
    fprintf(file, "    <DNS>%s</DNS>\n", dns);
    fprintf(file, "    <VelocidadMedia>%s</VelocidadMedia>\n", velocidad_media);
    fprintf(file, "    <NumeroSaltos>%d</NumeroSaltos>\n", numero_saltos);
    fprintf(file, "    <Saltos>\n");
    for (int i = 0; i < numero_saltos; i++) {
        fprintf(file, "        <Salto numero=\"%d\">%s</Salto>\n", i + 1, ip_saltos[i]);
    }
    fprintf(file, "    </Saltos>\n");
    fprintf(file, "</ConfiguracionRed>\n");

    fclose(file);
}
