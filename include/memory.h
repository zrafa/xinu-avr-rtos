/* memory.h - roundmb, truncmb, freestk */

/*----------------------------------------------------------------------
 * roundmb, truncmb - Round or truncate address to memory block size
 *----------------------------------------------------------------------
 */
#define	roundmb(x)	(char *)( (3 + (uint16)(x)) & (~3) )
#define	truncmb(x)	(char *)( ((uint16)(x)) & (~3) )

/*----------------------------------------------------------------------
 *  freestk  --  Free stack memory allocated by getstk
 *----------------------------------------------------------------------
 */
#define	freestk(p,len)	freemem((char *)((uint16)(p)		\
				- ((uint16)roundmb(len))	\
				+ (uint16)sizeof(uint16)),	\
				(uint16)roundmb(len) )

struct	memblk	{					/* See roundmb & truncmb		*/
	struct	memblk	*mnext;			/* Ptr to next free memory blk	*/
	uint16	mlength;				/* Size of blk (includes memblk)*/
	};
extern	struct	memblk	memlist;	/* Head of free memory list		*/
extern	void	*minheap;			/* Start of heap				*/
extern	void	*maxheap;			/* Highest valid heap address	*/
/* RAFA */
extern uint16  free_mem;            /* Total amount of free memory  */
/* FIN de RAFA */


