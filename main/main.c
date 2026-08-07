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
	int n = 100;
    pid16 pid;

	serial_init();

    kprintf("%s sizeof(struct procent) %d\n", __func__, sizeof(struct procent));

    pid = create(led, 400, 20, "led", 2, 13, 500);
    kprintf("%s pid %d\n", __func__, pid);

    resume(pid);

	while(1) {
		sleepms(2000);

		n++;
		serial_put_str("Hello World ");
		serial_put_int(n, 4);
		serial_put_str("!\n");
	}
}


