#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltutils.h>
#include <libxslt/transform.h>
#include "crearHTML.h"

void transformXMLtoHTML(const char* xmlFilename, const char* xsltFilename, const char* htmlFilename) {
    xmlDocPtr doc, res;
    xsltStylesheetPtr xslt = NULL;

    // Cargar el archivo XSLT
    xslt = xsltParseStylesheetFile((const xmlChar*)xsltFilename);
    if (xslt == NULL) {
        fprintf(stderr, "Error al cargar el archivo XSLT.\n");
        exit(EXIT_FAILURE);
    }

    // Cargar el archivo XML
    doc = xmlParseFile(xmlFilename);
    if (doc == NULL) {
        fprintf(stderr, "Error al cargar el archivo XML.\n");
        xsltFreeStylesheet(xslt);
        exit(EXIT_FAILURE);
    }

    // Aplicar la transformación XSLT
    res = xsltApplyStylesheet(xslt, doc, NULL);
    if (res == NULL) {
        fprintf(stderr, "Error al aplicar la transformación XSLT.\n");
        xmlFreeDoc(doc);
        xsltFreeStylesheet(xslt);
        exit(EXIT_FAILURE);
    }

    // Guardar el resultado en un archivo HTML
    FILE* file = fopen(htmlFilename, "w");
    if (file == NULL) {
        perror("Error al abrir el archivo para escritura");
        xmlFreeDoc(res);
        xmlFreeDoc(doc);
        xsltFreeStylesheet(xslt);
        exit(EXIT_FAILURE);
    }

    xsltSaveResultToFile(file, res, xslt);
    fclose(file);

    // Liberar memoria
    xmlFreeDoc(res);
    xmlFreeDoc(doc);
    xsltFreeStylesheet(xslt);

    printf("\nArchivo HTML generado exitosamente.\n");
}
