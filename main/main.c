#include <xinu.h>
#include <avr/interrupt.h>
#include "serial.h"
#include "sync.h"


#define SEM_COM 0
#define SEM_PROD 1

int comunicacion(void)
{
	while(1) {
		sync_wait(SEM_PROD);
		serial_put_str("Arriba america!\n");
		sync_signal(SEM_COM);
		
		sleep(2);
	}

}


int led_placa(void)
{
    volatile unsigned char* DDR_B = (unsigned char*) 0x24;
    volatile unsigned char* PUERTO_B = (unsigned char*) 0x25;

    *DDR_B = 0x20; // control: salida.

    while (1){
        sleepms(500);
        *PUERTO_B = 0x20; // high
        sleepms(500);
        *PUERTO_B = 0; // low
    }

}

void freemem_get(void)
{
	struct  memblk  *memptr;        /* Ptr to memory block          */
        uint32  free_mem;               /* Total amount of free memory  */

        /* Output Xinu memory layout */

        free_mem = 0;
        for (memptr = memlist.mnext; memptr != NULL;
					memptr = memptr->mnext) {
                free_mem += memptr->mlength;
        }
        kprintf("\nFreeMEM:%d (bytes)\n\n", free_mem);
}


int main(void)
{

	serial_init();


	resume(create(led_placa, 64, 10, "led", 0));
	resume(create(comunicacion, 256, 20, "comm", 0));

	sync_set(SEM_COM, 1);
	sync_set(SEM_PROD, 0);

	while(1) {
		sleep(1);

		sync_wait(SEM_COM);
		//kprintf("hola mundo\n");
		serial_put_str("hola mundo\n");
		sync_signal(SEM_PROD);
		
//		freemem_get();
		
	}

	return 0;
}

