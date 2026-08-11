#include <ltgt8f328p.h>

void set_clock_32MHz(void) {
    // Definición local y segura del registro CLKPR (Dirección 0x61)
    volatile unsigned char *clkpr_reg = (volatile unsigned char *)0x61;

    // Deshabilitar interrupciones por seguridad (secuencia crítica de 4 ciclos)
    __asm__ volatile("cli" ::: "memory"); 

    // Escribir un '1' en el bit de habilitación de cambio (Bit 7 / PMCE o CLKPCE)
    *clkpr_reg = 0x80; 

    // Dentro de los 4 ciclos siguientes, escribir el factor de división (0x00 = Divisor 1)
    *clkpr_reg = 0x00; 

    // Rehabilitar interrupciones globales
    //__asm__ volatile("sei" ::: "memory"); 
}

void init_system_clock(void) {
    // Configura el reloj interno a 32MHz reales sin división previa
    __asm__ __volatile__ (
        "ldi r24, 0x80\n\t"  // Habilitar cambio (CLKPCE)
        "sts 0x61, r24\n\t"  // Escribir en CLKPR (0x61)
        "ldi r24, 0x00\n\t"  // División por 1
        "sts 0x61, r24\n\t"
        : : : "r24"
    );
}

