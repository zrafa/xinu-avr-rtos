/* semcreate.c - semcreate, newsem */

#include <xinu.h>

local	sid16	newsem(void);

/*------------------------------------------------------------------------
 *  semcreate  -  Create a new semaphore and return the ID to the caller
 *------------------------------------------------------------------------
 */
sid16	semcreate(
	  int16		count				/* Initial semaphore count	*/
	)
{
	intmask	mask;					/* Saved interrupt mask		*/
	sid16	sem;					/* Semaphore ID to return	*/

	mask = disable();

	if (count < 0 || ((sem=newsem())==SYSERR)) {
		restore(mask);
		return SYSERR;
	}
	semtab[sem].scount = count;		/* Initialize table entry	*/

	restore(mask);
	return sem;
}

/*------------------------------------------------------------------------
 *  newsem  -  Allocate an unused semaphore and return its index
 *------------------------------------------------------------------------
 */
local	sid16	newsem(void)
{
	static	sid16	nextsem = 0;	/* Next semaphore index to try	*/
	sid16	sem;					/* Semaphore ID to return		*/
	int16	i;						/* Iterate through # entries	*/

	for (i=0 ; i<NSEM ; i++) {
		sem = nextsem++;
		if (nextsem >= NSEM)
			nextsem = 0;
		if (semtab[sem].sstate == S_FREE) {
			semtab[sem].sstate = S_USED;
			return sem;
		}
	}
	return SYSERR;
}
