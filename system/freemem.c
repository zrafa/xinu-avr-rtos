/* freemem.c - freemem */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  freemem  -  Free a memory block, returning the block to the free list
 *------------------------------------------------------------------------
 */
syscall	freemem(
	  char		*blkaddr,	/* Pointer to memory block	*/
	  uint16	nbytes		/* Size of block in bytes	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	memblk	*next, *prev, *block;
	uint16	top;

	mask = disable();
	if ((nbytes == 0) || ((uint16) blkaddr < (uint16) minheap)
			  || ((uint16) blkaddr > (uint16) maxheap)) {
		restore(mask);
		return SYSERR;
	}

	nbytes = (uint16) roundmb(nbytes);	/* Use memblk multiples	*/
	block = (struct memblk *)blkaddr;

	prev = &memlist;			/* Walk along free list	*/
	next = memlist.mnext;
	while ((next != NULL) && (next < block)) {
		prev = next;
		next = next->mnext;
	}

	if (prev == &memlist) {		/* Compute top of previous block*/
		top = (uint16) NULL;
	} else {
		top = (uint16) prev + prev->mlength;
	}

	/* Ensure new block does not overlap previous or next blocks	*/

	if (((prev != &memlist) && (uint16) block < top)
	    || ((next != NULL)	&& (uint16) block+nbytes>(uint16)next)) {
		restore(mask);
		return SYSERR;
	}

	memlist.mlength += nbytes;

	/* Either coalesce with previous block or add to free list */

	if (top == (uint16) block) { 	/* Coalesce with previous block	*/
		prev->mlength += nbytes;
		block = prev;
	} else {			/* Link into list as new node	*/
		block->mnext = next;
		block->mlength = nbytes;
		prev->mnext = block;
	}

	/* Coalesce with next block if adjacent */

	if (((uint16) block + block->mlength) == (uint16) next) {
		block->mlength += next->mlength;
		block->mnext = next->mnext;
	}
	restore(mask);
	return OK;
}
