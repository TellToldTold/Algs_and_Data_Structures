#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "item.h"
#include "data.h"

Item ITEMscan () {
  char name[MAXST];
  char id[MAXST];

  scanf ("%s%s", name, id);

  Item tmp = (Item) malloc(sizeof(data_t));
  if (tmp == NULL) {
    return ITEMsetvoid();
  } else {
    tmp->name = strdup(name);
    tmp->id = id;
  }
  
  return tmp;
}

void ITEMshow (Item data) {
  fprintf (stdout, "   name = %s id = %s  ", data->name, data->id);
}

void ITEMprint (Item data, FILE *fOut) {
    fprintf (fOut, "   name = %s id = %s  ", data->name, data->id);
}

int ITEMcheckvoid(Item data) {
  Key k1, k2 = "";
  
  k1 = KEYget(data);
  if (KEYcompare(k1,k2)==0)
    return 1;
  else
    return 0;
}

Item ITEMsetvoid() {
  char emptyStr[MAXST] = "";

  Item tmp = (Item) malloc(sizeof(data_t));
  if (tmp != NULL) {
    tmp->name = strdup(emptyStr);
    tmp->id = strdup(emptyStr);
  }
  return tmp;
}

Key KEYscan() {
  char name[MAXST];
  Key k;
  
  scanf("%s", name);
  k = strdup(name);
  return k;
}

int  KEYcompare(Key k1, Key k2) {
  return strcmp(k1,k2);
}

Key KEYget(Item data) {
  return data->id;
}
