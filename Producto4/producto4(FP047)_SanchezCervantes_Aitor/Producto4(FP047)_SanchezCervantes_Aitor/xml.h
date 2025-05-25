//xml.h

#ifndef XML_H
#define XML_H

#define LONG_BUFFER 1024

void crear_archivo_xml(const char* ip, const char* mascara_subred, const char* puerta_enlace, const char* dns, const char* velocidad_media, int numero_saltos, char ip_saltos[][LONG_BUFFER]);

#endif // XML_H
