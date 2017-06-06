#ifndef DYNAMIC_STACK_NODE_H_INCLUDED
#define DYNAMIC_STACK_NODE_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include "location.h"

typedef struct dynamic_stack_node
{
    Location loc;
    struct dynamic_stack_node *next;
} stack_node;

stack_node* create_node(Location loc);

void delete_node(stack_node* s);

#endif
