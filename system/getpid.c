/* getpid.c - getpid */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getpid  -  Return the ID of the currently executing process
 *------------------------------------------------------------------------
 */
pid16	getpid(void)
{
	return (currpid);
}
