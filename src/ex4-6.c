/*
 * Add commands for handling variables. (It's easy to provide twenty-six
 * variables with single-letter names.) Add a variable for the most recently
 * printed value.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP   100  /* max size of operand or operator */
#define NUMBER  '0'  /* signal that a number was found */

#define PRINT   'P'
#define DUP     'D'
#define SWAP    'W'
#define CLEAR   'C'

#define SIN     'S'
#define EXP     'E'

#define VARIABLE 'a'

int getop(char s[]);
void push(double);
double pop(void);
void clear_stack(void);
void push_var(int v);
int pop_var(void);
void clear_var_stack();

/* reverse polish calculator */
int main(void)
{
    int type, i;
    double op1, op2;
    char s[MAXOP];
    /* variable array. the z variable is the most recently printed value. */
    double variables[26];

    /* initialize all variables */
    for (i = 0; i < 26; i++)
        variables[i] = 0.0;

    while (type = getop(s), type != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
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
        case '^':
            op2 = pop();
            push(pow(pop(), op2));
            break;
        case SIN:
            push(sin(pop()));
            break;
        case EXP:
            push(exp(pop()));
            break;
        case PRINT:
            op2 = pop();
            printf("%.8g\n", op2);
            variables['z' - 'a'] = op2;
            push(op2);
            break;
        case DUP:
            op2 = pop();
            push(op2);
            push(op2);
            break;
        case SWAP:
            op2 = pop();
            op1 = pop();
            push(op2);
            push(op1);
            break;
        case CLEAR:
            clear_stack();
            break;
        case VARIABLE:
            push(variables[s[0] - 'a']);
            push_var(s[0]);
            break;
        case '=':
            op2 = pop();
            variables[pop_var() - 'a'] = op2;
            break;
        case '\n':
            /*
             * this is kind of a huge hack. since variables are popped only on assignments,
             * and we may use variables on expression that arent assignments, the variable
             * stack could reach the max without the user doing anything. therefore, I
             * decided to clear it on every line, and assume assignments are always done
             * on a single line
             */
            clear_var_stack();
            break;
        default:
            printf("error: unknown command %s\n", s);
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

void clear_stack(void)
{
    sp = 0;
}

/* we use a variable stack in case of nested assignments */
int var_sp = 0;
int var_stack[MAXVAL];

void push_var(int v)
{
    if (var_sp < MAXVAL)
        var_stack[var_sp++] = v;
    else
        printf("error: var stack full, can't push %c\n", v);
}

int pop_var(void)
{
    if (var_sp > 0)
        return var_stack[--var_sp];
    else {
        printf("error: stack empty\n");
        return 'a';
    }
}

void clear_var_stack()
{
    var_sp = 0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;

    while (s[0] = c = getch(), c == ' ' || c == '\t')
        ;
    s[1] = '\0';

    /* check for variable. */
    if (c >= 'a' && c <= 'z')
        return VARIABLE;

    if (!isdigit(c) && c != '.')
        return c;   /* not a number */
    i = 0;
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')   /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int  bufp = 0;      /* next free position in buf */

int getch(void)     /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

