/* semcount.c - semcount */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  semcount  -  Return the count of a semaphore (because any integer is
 *		   possible, return of SYSERR may be ambiguous)
 *------------------------------------------------------------------------
 */
syscall semcount(
	  sid16		semid		/* ID of semaphore to use	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	int16	count;			/* Current sempahore count	*/

	mask = disable();
	
	if (isbadsem(semid) || semtab[semid].sstate == S_FREE) {
		restore(mask);
		return SYSERR;
	}
	count = semtab[semid].scount;
	restore(mask);
	return count;
}
