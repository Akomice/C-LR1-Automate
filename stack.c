#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

struct stack 
{
    octet etat;
    struct stack *next;
};

stack_t * empty_stack() {
    return NULL;
}

void add_stack(octet new_etat, stack_t ** p) {
    stack_t * new_stack;
    new_stack = malloc(sizeof(stack_t));
    new_stack->etat=new_etat;
    new_stack->next=*p;
    *p = new_stack;
}

octet top_of_stack(stack_t * p) {
    return p->etat;
}

void del(stack_t ** p) {
    *p = (*p)->next;
}

stack_t * initialise() {
    stack_t * create = empty_stack();
    add_stack((octet)'\000',&create);
    return create;
}

