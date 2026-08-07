/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg16	receive(void)
{
	intmask	mask;				/* Saved interrupt mask			*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	umsg16	msg;				/* Message to return			*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_RECV;
		resched();				/* Block until message arrives	*/
	}
	msg = prptr->prmsg;			/* Retrieve message				*/
	prptr->prhasmsg = FALSE;	/* Reset message flag			*/
	restore(mask);
	return msg;
}
