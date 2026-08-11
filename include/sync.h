#include <xinu.h>

#ifndef _SYNC_H
#define _SYNC_H 

extern char semaforo[];

void sync_wait(uint8 n);
void sync_signal(uint8 n);
void sync_set(uint8 n, char v);

#endif

