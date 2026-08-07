/* clock.h */

extern	volatile uint16	clktime;	/* current time in secs since boot		*/
extern  volatile uint16  count1000; /* ms since last clock tick             */

extern	volatile qid16	sleepq;		/* queue for sleeping processes			*/
extern	int16	slnonempty;			/* nonzero if sleepq is nonempty		*/
extern	int16	*sltop;				/* ptr to key in first item on sleepq	*/
extern	volatile uint16	preempt;	/* preemption counter					*/

