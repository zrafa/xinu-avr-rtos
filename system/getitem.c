/* getitem.c - getfirst, getlast, getitem */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getfirst  -  Remove a process from the front of a queue
 *------------------------------------------------------------------------
 */
pid16	getfirst(
	  qid16		q	/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)		*/
{
	pid16	head;

	if (isempty(q)) {
		return EMPTY;
	}

	head = queuehead(q);
	return getitem(queuetab[head].qnext);
}

/*------------------------------------------------------------------------
 *  getlast  -  Remove a process from end of queue
 *------------------------------------------------------------------------
 */
pid16	getlast(
	  qid16		q	/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)		*/
{
	pid16 tail;

	if (isempty(q)) {
		return EMPTY;
	}

	tail = queuetail(q);
	return getitem(queuetab[tail].qprev);
}

/*------------------------------------------------------------------------
 *  getitem  -  Remove a process from an arbitrary point in a queue
 *------------------------------------------------------------------------
 */
pid16	getitem(
	  pid16		pid				/* ID of process to remove	*/
	)
{
	pid16	prev, next;

	next = queuetab[pid].qnext;	/* Following node in list	*/
	prev = queuetab[pid].qprev;	/* Previous node in list	*/
	queuetab[prev].qnext = next;
	queuetab[next].qprev = prev;
	return pid;
}
