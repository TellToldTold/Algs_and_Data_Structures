#ifndef _STACK_PUBLIC
#define _STACK_PUBLIC

#include <stdio.h>

/* macro definition */
#define stack_empty_m(sp) (stack_count(sp) == 0)

/* type declarations */
typedef struct stack stack_tt;

/* extern function prototypes */
extern stack_tt *stack_init(int size);
extern int stack_count(stack_tt *sp);
extern int stack_push(stack_tt *sp, void *data);
extern int stack_pop(stack_tt *sp, void **data_ptr);
extern void stack_print(FILE *fp, stack_tt *sp, void (*print)(FILE *, void *));
extern void stack_dispose(stack_tt *sp, void (*quit)(void *));

#endif
