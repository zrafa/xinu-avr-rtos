/*
 * ex0: ejemplo0. 
 * main es la primer tarea puesta en ejecución por XINU RTOS.
 * Esta tarea crea una tarea y luego muestra un mensaje a 1hz.
 *
 * Las 3 tareas son gestionadas por el RTOS, quien las ejecuta
 * de manera concurrente (null, main, y led).
 */

#include <xinu.h>
#include "serial.h"

void led();
void frec();


int main(void)
{
	int n = 0;

	serial_init();

	resume(create(led, 128, 20, "led", 2, 13, 500));

	while(1) {
		sleepms(1000);

		n++;
		serial_put_str("Hello World!. Free mem: ");
		serial_put_int(free_mem, 4);
		serial_put_str("\n\r");
	}
}


