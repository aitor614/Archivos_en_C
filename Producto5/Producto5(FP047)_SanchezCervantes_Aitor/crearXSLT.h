#// crearXSLT.h

#ifndef CREARXSLT_H
#define CREARXSLT_H

// Funci�n para crear el contenido XSLT din�micamente a partir de un XML
char* createXSLTFromXML(const char* xmlFilename);

// Funci�n para escribir contenido en un archivo
void writeFile(const char* filename, const char* content);

#endif 
