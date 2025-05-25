#include "extraer_ip.h"
#include <stdio.h>
#include <ctype.h>


bool extraer_ip_de_linea(const char* linea, char* ip_out, size_t size) {
    const char* p = linea;

    while (*p) {
        // Inicializar variables a 0 para evitar advertencias C6001
        int b1 = 0, b2 = 0, b3 = 0, b4 = 0;

        // Usar sscanf_s (versión segura)
        if (isdigit(*p) && sscanf_s(p, "%d.%d.%d.%d", &b1, &b2, &b3, &b4) == 4) {
            if ((b1 | b2 | b3 | b4) <= 255) {
                // Usar sprintf_s (segura también)
                sprintf_s(ip_out, size, "%d.%d.%d.%d", b1, b2, b3, b4);
                return true;
            }
        }
        p++;
    }

    return false;
}
