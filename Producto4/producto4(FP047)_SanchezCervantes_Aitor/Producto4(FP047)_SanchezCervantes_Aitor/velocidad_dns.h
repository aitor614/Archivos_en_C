// velocidad_dns.h

#ifndef VELOCIDAD_DNS_H
#define VELOCIDAD_DNS_H

#define LONG_BUFFER 1024


void obtener_velocidad_respuesta_dns(const char* dns, char* velocidadMedia);
int trazar_ruta_dns(const char* dns, char ip_saltos[][LONG_BUFFER], int max_saltos);


#endif // VELOCIDAD_DNS_H
