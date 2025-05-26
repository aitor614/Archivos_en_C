#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include "crearXSLT.h"


// Método para escribir en un archivo
void writeFile(const char* filename, const char* content) {
    printf("\nEscribiendo en archivo: %s\n", filename); // Mensaje de depuración
   

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error al abrir el archivo para escritura");
        exit(EXIT_FAILURE);
    }

    if (fprintf(file, "%s", content) < 0) {
        fclose(file);
        perror("Error al escribir en el archivo");
        exit(EXIT_FAILURE);
    }

    fclose(file);
    printf("\nArchivo escrito exitosamente.\n"); // Mensaje de depuración
}

// Método para crear el contenido XSLT
char* createXSLTFromXML(const char* xmlFilename) {
    xmlDocPtr doc;
    xmlNodePtr root_element;

    // Cargar el archivo XML
    doc = xmlParseFile(xmlFilename);
    if (doc == NULL) {
        fprintf(stderr, "Error al cargar el archivo XML.\n");
        return NULL;
    }

    // Obtener el elemento raíz
    root_element = xmlDocGetRootElement(doc);
    if (root_element == NULL) {
        fprintf(stderr, "El archivo XML está vacío.\n");
        xmlFreeDoc(doc);
        return NULL;
    }

    // Comenzar a construir el contenido XSLT
    const char* xsltHeader =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<xsl:stylesheet version=\"1.0\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\">\n"
        "    <xsl:output method=\"html\" encoding=\"UTF-8\" indent=\"yes\"/>\n"
        "    <!-- Template principal -->\n"
        "    <xsl:template match=\"/\">\n"
        "        <html>\n"
        "            <head>\n"
        "                <title>Configuracion de Red</title>\n"
        "                <style>\n"
        "                    table {\n"
        "                        width: 50%;\n"
        "                        margin: 20px auto;\n"
        "                        border-collapse: collapse;\n"
        "                    }\n"
        "                    th, td {\n"
        "                        border: 1px solid #000;\n"
        "                        padding: 8px;\n"
        "                        text-align: left;\n"
        "                    }\n"
        "                    th {\n"
        "                        background-color: #f2f2f2;\n"
        "                        font-size: 1.2em;\n"
        "                        text-transform: uppercase;\n"
        "                    }\n"
        "                    tr:nth-child(even) {\n"
        "                        background-color: #f9f9f9;\n"
        "                    }\n"
        "                    td:first-child {\n"
        "                        font-weight: bold;\n"
        "                    }\n"
        "                </style>\n"
        "            </head>\n"
        "            <body>\n"
        "                <h2>Configuracion de Red</h2>\n"
        "                <table>\n"
        "                    <tr>\n"
        "                        <th>Elemento</th>\n"
        "                        <th>Valor</th>\n"
        "                    </tr>\n";
    const char* xsltFooter =
        "                </table>\n"
        "            </body>\n"
        "        </html>\n"
        "    </xsl:template>\n"
        "</xsl:stylesheet>\n";

    size_t xsltSize = strlen(xsltHeader) + strlen(xsltFooter) + 1;
    xmlNodePtr currentNode = root_element->children;

    // Calcular el tamaño necesario para el contenido dinámico
    while (currentNode) {
        if (currentNode->type == XML_ELEMENT_NODE) {
            xsltSize += strlen((const char*)currentNode->name) * 2 + 500; 
        }
        currentNode = currentNode->next;
    }

    // Asignar memoria para el contenido XSLT
    char* xsltContent = (char*)malloc(xsltSize);
    if (xsltContent == NULL) {
        perror("Error al asignar memoria");
        xmlFreeDoc(doc);
        return NULL;
    }

    // Construir el contenido XSLT
    strcpy_s(xsltContent, xsltSize, xsltHeader);
    currentNode = root_element->children;
    while (currentNode) {
        if (currentNode->type == XML_ELEMENT_NODE) {
            strcat_s(xsltContent, xsltSize, "                    <tr>\n");
            strcat_s(xsltContent, xsltSize, "                        <td>");
            strcat_s(xsltContent, xsltSize, (const char*)currentNode->name);
            strcat_s(xsltContent, xsltSize, "</td>\n");

            // CASO ESPECIAL PARA "Saltos"
            if (strcmp((const char*)currentNode->name, "Saltos") == 0) {
                strcat_s(xsltContent, xsltSize, "                        <td>\n");
                strcat_s(xsltContent, xsltSize, "                            <xsl:for-each select=\"ConfiguracionRed/Saltos/Salto\">\n");
                strcat_s(xsltContent, xsltSize, "                                <xsl:value-of select=\".\"/><br/>\n");
                strcat_s(xsltContent, xsltSize, "                            </xsl:for-each>\n");
                strcat_s(xsltContent, xsltSize, "                        </td>\n");
            }
            else {
                // CASO NORMAL
                strcat_s(xsltContent, xsltSize, "                        <td><xsl:value-of select=\"ConfiguracionRed/");
                strcat_s(xsltContent, xsltSize, (const char*)currentNode->name);
                strcat_s(xsltContent, xsltSize, "\"/></td>\n");
            }

            strcat_s(xsltContent, xsltSize, "                    </tr>\n");
        }
        currentNode = currentNode->next;
    }
    strcat_s(xsltContent, xsltSize, xsltFooter);

    xmlFreeDoc(doc);
    return xsltContent;
}
