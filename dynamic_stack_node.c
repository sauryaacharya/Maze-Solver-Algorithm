#include "dynamic_stack_node.h"
stack_node* create_node(Location l)
{
    stack_node* temp = malloc(sizeof(stack_node));
    temp->loc = l;
    temp->next = NULL;
    return temp;
}

void delete_node(stack_node* n)
{
    if(n != NULL)
    {
        free(n);
    }
}
