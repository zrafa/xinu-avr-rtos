#include <xinu.h>

int comunicacion(void)
{
	while(1) {
//		putchar('a');
		serial_put_str("Hola mundo!\n");
		sleep(1);
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
	resume(create(led_placa, 128, 10, "led", 0));
	while(1) {
		sleep(1);
		kprintf("hola mundo\n");
		//serial_put_str("hola mundo\n");
		freemem_get();
	}
//	resume(create(comunicacion, 512, 20, "comm", 0));

	return 0;
}

