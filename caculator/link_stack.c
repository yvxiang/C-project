#include "link_stack.h"
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>


Stack* create_stack(size_t data_byte) {
    Stack * pst = (Stack *)malloc(sizeof(Stack));
    pst->byte = data_byte;
    pst->head = NULL;
    return pst;
}

void destroy_stack(Stack *pst) {
    while(!is_empty(pst))
        pop(pst);
}

void push(Stack *pst, void* value) {
    StackNode *newNode;
    newNode = (StackNode *)malloc(sizeof(StackNode));
    assert(newNode != NULL);
    newNode->value = malloc(pst->byte);
    assert(newNode->value != NULL);
    memcpy(newNode->value, value, pst->byte);
    newNode->next = pst->head;
    pst->head = newNode;
}

void pop(Stack *pst) {
    StackNode * firstNode;
    assert(!is_empty(pst));

    firstNode = pst->head;
    pst->head = firstNode->next;
    free(firstNode);
}

void* top(Stack *pst) {
    assert(!is_empty(pst));
    return pst->head->value;
}

int is_empty(Stack *pst){
    return pst->head == NULL;
}

int stack_capacity(Stack *pst) {
    int count = 0;
    StackNode * stack_ptr = pst->head;
    while (stack_ptr != NULL) {
        count++;
        stack_ptr = stack_ptr->next;
    }
    return count;
}
