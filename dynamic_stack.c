#include "dynamic_stack.h"

dynamic_stack* create_stack()
{
    dynamic_stack* temp = malloc(sizeof(dynamic_stack));
    temp->top = NULL;
    return temp;
}

void delete_stack(dynamic_stack* s)
{
    if(s != NULL)
    {
        stack_node* temp = s->top;
        stack_node* temp1 = NULL;
        while(temp != NULL)
        {
            temp1 = temp;
            temp = temp->next;
            free(temp1);
        }
        free(s);
    }
}

void push(dynamic_stack* s, Location loc)
{
    stack_node* temp = s->top;
    s->top = create_node(loc);
    s->top->next = temp;
}

Location pop(dynamic_stack* s)
{
    /*
    if(s->top == NULL)
    {
        //printf("POP_ON_ EMPTY_STACK_EXCEPTION");
        return s;
    }
    */
    if(isEmpty(s)){
        printf("No more elements");
        exit(1);
    }
    stack_node* temp = s->top;
    s->top = temp->next;
    Location result = temp->loc;
    delete_node(temp);
    return result;
}

int isEmpty(dynamic_stack* s){
    if(s->top == NULL)
        return 1;

    return 0;
}

Location peek(dynamic_stack* s)
{
    Location l = s->top->loc;
    return l;
}

void print_stack(dynamic_stack* s)
{
    if(s != NULL)
    {
        stack_node* temp = s->top;
        while(temp != NULL)
        {
            printf("(%d:%d)", temp->loc.row, temp->loc.column);
            temp = temp->next;
        }
        printf("\n");
    }
}
