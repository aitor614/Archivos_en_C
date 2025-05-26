#// crearXSLT.h

#ifndef CREARXSLT_H
#define CREARXSLT_H

// Función para crear el contenido XSLT dinámicamente a partir de un XML
char* createXSLTFromXML(const char* xmlFilename);

// Función para escribir contenido en un archivo
void writeFile(const char* filename, const char* content);

#endif 
