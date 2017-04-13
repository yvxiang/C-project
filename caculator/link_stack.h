#ifndef LINK_STACK_H
#define LINK_STACK_H
#include <stddef.h>

typedef struct STACK_NODE{
    void* value;
    struct STACK_NODE *next;
} StackNode;

typedef struct{
    StackNode *head;
    size_t byte;
} Stack;

Stack* create_stack(size_t data_byte);
void destroy_stack(Stack *pst);
void push(Stack *pst, void* value);
void pop(Stack *pst);
void* top(Stack *pst);
int is_empty(Stack *pst);
int stack_capacity(Stack *pst);
#endif
