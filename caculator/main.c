#include <stdio.h>
#include "caculator.h"
#include "link_stack.h"
#include <stdlib.h>

int main()
{
    char *infix_exp;
    while(scanf("%s", infix_exp) > 0) {
        printf("Result is: %d\n",caculator(transfer_exp(infix_exp)));
    }
    return 0;
}
