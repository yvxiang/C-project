#include "link_stack.h"
#include "caculator.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#define MAX_EXP_LEN 100
static char suffix_exp[MAX_EXP_LEN];
/*
** get operator priority level
** 0 is the highest priority level, the larger the lowest
*/
int get_priority(char operator) {
    switch (operator) {
    case '(':
        return 0;
    case '*':
    case '/':
        return 1;
    case '+':
    case '-':
        return 2;
    default:
        printf("No matching operator!\n");
        exit(1);
    }
}

/*
** transfer infix expression to suffix expression
*/
char * transfer_exp(char *infix_exp) {
    int index = 0;
    char* ptr = infix_exp;
    Stack *pst = create_stack(sizeof(char));
    while (*ptr != '\0') {
        // just output the digit to the output expression
        if((*ptr >= '0' && *ptr < '9') || isspace(*ptr))
            suffix_exp[index++] = *ptr;
        // if current operator is ')', pop out of all the operators to the output expression until the '('
        // just pop '(', not output to the output expression
        else if (*ptr == ')') {
            while (!is_empty(pst) && *(char *)top(pst) != '(') {
                    suffix_exp[index++] = *(char *)top(pst);
                    pop(pst);
                   }
            // if there is no '('
            if (!is_empty(pst) && *(char *)top(pst) == '(') {
                pop(pst);
            }
            else {
                printf("No matching '(' in infix expression!\n");
                exit(2);
            }
        }
        else if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/' || *ptr == '(') {
            suffix_exp[index++] = ' ';
            // if the current operator's priority is lower or equal to the stack top operator, pop the operator to the output expression, except that the operator is '('
            // on the other hand, if the current operator's priority is higher than the stack top operator, or the stack is empty, or the top operator is '(', just push it into the stack
            while(!is_empty(pst) && *(char *)top(pst) != '(' && get_priority(*(char *)top(pst)) <= get_priority(*ptr) ) {
                        suffix_exp[index++] = *(char *)top(pst);
                        pop(pst);
               }
            if(is_empty(pst) || *(char *)top(pst) == '(' || get_priority(*(char *)top(pst)) > get_priority(*ptr)) {
                push(pst, ptr);
            }
        }
        ptr++;
    }
    // if the infix expression ends, just pop all the operators to the output expression
    while(!is_empty(pst)) {
        assert(*(char *)top(pst) != '(');
        suffix_exp[index++] = *(char *)top(pst);
        pop(pst);
    }
    suffix_exp[index] = '\0';
    return suffix_exp;
}

int caculator(const char * suffix_exp) {
    char * ptr = suffix_exp;
    char data_exp[20]; // store the digit expression
    Stack *pst = create_stack(sizeof(int));
    while (*ptr != '\0') {
        if (*ptr >= '0' && *ptr < '9') {
            int i = 0;
            while (*ptr >= '0' && *ptr < '9')
                data_exp[i++] = *ptr++;
            data_exp[i] = '\0';
            ptr--;
            int value = atoi(data_exp);
            push(pst, &value);
        }
        else if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/') {
            int operand2 = *(int *)top(pst);
            pop(pst);
            int operand1 = *(int *)top(pst);
            pop(pst);
            int re;
            switch (*ptr) {
            case '+':
                re = operand1+operand2;
                push(pst, &re);
                break;
            case '-':
                re = operand1-operand2;
                push(pst, &re);
                break;
            case '*':
                re = operand1*operand2;
                push(pst, &re);
                break;
            case '/':
                re = operand1/operand2;
                push(pst, &re);
                break;
            }
        }
        ptr++;
    }
    int re = *(int *)top(pst);
    pop(pst);
    assert(is_empty(pst));
    return re;
}

