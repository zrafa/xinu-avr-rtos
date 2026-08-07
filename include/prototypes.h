
/* in file chprio.c */
extern	pri16	chprio(pid16, pri16);

/* in file clkhandler.c */
extern	interrupt clkhandler(void);

/* in file clkinit.c */
extern	void	clkinit(void);

/* in file create.c */
extern	pid16	create(int (*procaddr)(), int, int, char *, int, ...);

/* in file ctxsw.S */
extern	void	ctxsw(void *, void *);

/* in file freemem.c */
extern	syscall	freemem(char *, uint16);

/* in file getitem.c */
extern	pid16	getfirst(qid16);
extern	pid16	getlast(qid16);
extern	pid16	getitem(pid16);

/* in file getmem.c */
extern	char	*getmem(uint16);

/* in file getpid.c */
extern	pid16	getpid(void);

/* in file getprio.c */
extern	syscall	getprio(pid16);

/* in file getstk.c */
extern	char	*getstk(uint16);

/* in file insert.c */
extern	status	insert(pid16, qid16, char);

/* in file insertd.c */
extern	status	insertd(pid16, qid16, uint16);

/* in file intr.c */
extern	intmask	disable(void);
extern	void	enable(void);
extern	void	restore(intmask);
extern	void	halt(void);

/* in file kill.c */
extern	syscall	kill(pid16);

/* in file newqueue.c */
extern	qid16	newqueue(void);

/* in file platinit.c */
extern	void	platinit(void);

/* in file queue.c */
extern	pid16	enqueue(pid16, qid16);
extern	pid16	dequeue(qid16);

/* in file ready.c */
extern	status	ready(pid16);

/* in file receive.c */
extern	umsg16	receive(void);

/* in file recvclr.c */
extern	umsg16	recvclr(void);

/* in file recvtime.c */
extern	umsg16	recvtime(int16);

/* in file resched.c */
extern	void	resched(void);
extern	status	resched_cntl(int16);

/* in file resume.c */
extern	pri16	resume(pid16);

/* in file semcount.c */
extern	syscall	semcount(sid16);

/* in file semcreate.c */
extern	sid16	semcreate(int16);

/* in file semdelete.c */
extern	syscall	semdelete(sid16);

/* in file semreset.c */
extern	syscall	semreset(sid16, int16);

/* in file send.c */
extern	syscall	send(pid16, umsg16);

/* in file signal.c */
extern	syscall	signal(sid16);

/* in file signaln.c */
extern	syscall	signaln(sid16, int16);

/* in file sleep.c */
extern	syscall	sleepms(int16);
extern	syscall	sleep(int16);

/* in file suspend.c */
extern	syscall	suspend(pid16);

/* in file unsleep.c */
extern	syscall	unsleep(pid16);

/* in file userret.c */
extern	void	userret(void);

/* in file wait.c */
extern	syscall	wait(sid16);

/* in file wakeup.c */
extern	void	wakeup(void);

/* in file xdone.c */
extern	void	xdone(void);

/* in file yield.c */
extern	syscall	yield(void);

