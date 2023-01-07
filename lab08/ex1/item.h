#ifndef _DATO_INCLUDED
#define _DATO_INCLUDED

#include "data.h"

#define MAXST 10

typedef data_t* Item;
typedef char *Key;

Item ITEMscan();
void ITEMshow(Item data);
void ITEMprint(Item data, FILE *);
int ITEMcheckvoid(Item data);
Item ITEMsetvoid();
Key KEYscan();
int KEYcompare(Key k1, Key k2);
Key KEYget(Item data);
#endif

