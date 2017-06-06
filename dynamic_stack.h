#ifndef DYNAMIC_STACK_H_INCLUDED
#define DYNAMIC_STACK_H_INCLUDED
#include "dynamic_stack_node.h"
typedef struct dynamic_stack
{
    stack_node* top;
} dynamic_stack;

dynamic_stack* create_stack();

void delete_stack(dynamic_stack* s);

void push(dynamic_stack* s, Location loc);

Location pop(dynamic_stack* s);

Location peek(dynamic_stack* s);

void print_stack(dynamic_stack* s);

int isEmpty(dynamic_stack* s);

#endif
