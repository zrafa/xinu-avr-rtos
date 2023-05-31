/*  main.c  - main */

/* Basic Xinu app for quick start */

#include <xinu.h>
#include "QMC5883L.h"


process	main(void)
{
	/* We create() a new process. Arguments:
	 *         process code: example0()
	 *         stack size: 128 bytes
	 *         priority: 50
	 * 	   name: "ex0"
	 *         arguments: 2
	 * 	   first argument: 3 (int)
	 * 	   second argument: "hello world"
	 */

    resume(create(magnetometro_init, 128, 50, "magnetometro_init", 0));
    resume(create(mostrar_angulo, 512, 50, "mostrar_angulo", 0));

	/* Wait for example0 to exit */

	receive();
	printf("\n %s process has completed.\n", proctab[currpid].prname);

	return OK;
}
