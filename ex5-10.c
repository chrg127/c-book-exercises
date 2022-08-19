/*
 * Write the program expr, which evaluates a reverse Polish
 * expression from the command line, where each operator or operand is a separate
 * argument. For example,
 *
 *      expr 2 3 4 + *
 *
 * evaluates 2 * (3+4)
 */

/* implementation is from exercise 4-9 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXOP   100  /* max size of operand or operator */
#define NUMBER  '0'  /* signal that a number was found */

#define PRINT   'P'
#define DUP     'D'
#define SWAP    'W'
#define CLEAR   'C'

#define SIN     'S'
#define EXP     'E'

#define VARIABLE 'a'
#define UNKNOWN 'U'

int getop(char s[]);
void push(double);
double pop(void);
void clear_stack(void);
void push_var(int v);
int pop_var(void);
void clear_var_stack();

/* reverse polish calculator */
int main(int argc, char *argv[])
{
    int type, i;
    double op1, op2;
    char *s;
    double variables[26];

    if (argc < 2) {
        printf("usage: %s [expr...]\n", *argv);
        return 0;
    }

    /* initialize all variables */
    for (i = 0; i < 26; i++)
        variables[i] = 0.0;

    while (++argv, --argc > 0) {
        s = *argv;
        type = getop(s);
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
        case UNKNOWN:
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

/* getop: parse next operator or numeric operand */
int getop(char *s)
{
    int i;

    if (s[0] == '\0')
        return UNKNOWN;
    if (s[1] == '\0') {
        if (s[0] >= 'a' && s[0] <= 'z')
            return VARIABLE;
        if (!isdigit(s[0]) && s[0] != '.')
            return s[0];    /* not a number */
    }
    i = 0;
    while (isdigit(s[++i]))
        ;
    if (s[i] == '.')
        while (isdigit(s[++i]))
            ;
    if (s[i] != '\0')
        return UNKNOWN;
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
    if (c == EOF)   /* my design: signal error if an EOF is pushed back, and ignore it */
        printf("ungetch: EOF pushed back\n");
    else if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void ungets(char s[])   /* push an entire string on input */
{
    int i, len;

    len = strlen(s);
    if (len + bufp >= BUFSIZE) {
        printf("ungets: string too long to push back\n");
        return;
    }
    for (i = len-1; i >= 0; i--)
        ungetch(s[i]);
}
