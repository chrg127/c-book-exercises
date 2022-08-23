/*
 * Rewrite the postfix calculator of Chapter 4 to use scanf and/or
 * sscanf to do the input and number conversion.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAXOP  100  /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */

int getop(double *n);
void push(double);
double pop(void);

/* reverse polish calculator */
int main(void)
{
    int type;
    double op2, n;

    while (type = getop(&n), type != EOF) {
        switch (type) {
        case NUMBER:
            push(n);
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            if (op2 >= 0.0)
                push(fmod(pop(), op2));
            else
                printf("error: negative number as operand to %\n");
            break;
        case '\n':
            printf("%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %c\n", type);
            break;
        }
    }

    return 0;
}

#define MAXVAL 100  /* maximum depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* getop: get next operator or numeric operand */
int getop(double *n)
{
    int r, c;

    while (c = getchar(), c == ' ' || c == '\t')
        ;
    if (!isdigit(c) && c != '.')
        return c;   /* not a number */
    ungetc(c, stdin);
    scanf("%lf", n);
    return NUMBER;
}
