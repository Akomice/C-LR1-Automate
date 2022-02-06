#ifndef _STACK_H
#define _STACK_H

typedef unsigned char octet;

struct stack;

typedef struct stack stack_t;

/* La fonction empty_stack 
@ requires : rien
@ assigns : rien
@ ensures : renvoie une pile vide
*/
stack_t * empty_stack();

/* La fonction add_stack 
@ requires : une pile 'p' valide
@ assigns : la pile 'p'
@ ensures : ajoute à la pile 'p' l'élement 'new_etat'
*/
void add_stack(octet new_etat, stack_t ** p);

/* La fonction top_of_stack 
@ requires : une pile 'p' valide
@ assigns : rien
@ ensures : renvoie le haut de la pile
*/
octet top_of_stack(stack_t * p);

/* La fonction del 
@ requires : une pile 'p' valide
@ assigns : la pile 'p'
@ ensures : dépile le haut de la pile
*/
void del(stack_t ** p);

/* La fonction initialise 
@ requires : rien
@ assigns : rien
@ ensures : renvoie une pile qui a pour unique élement le 0
*/
stack_t * initialise();

#endif