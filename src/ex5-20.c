/*
 * Expand dcl to handle declaration with function argument types,
 * qualifiers like const, and so on.
 */

/*
 * what I added support for here is full support for function parameters
 * and support for a 'const' before the type of the variable (i.e. the west
 * const). 'const' is supported nowhere else, mainly because it'd be a bit too
 * difficult to add support for const pointers.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS, CONST };

void typename(void);
void dcl(void);
void dirdcl(void);
int gettoken(void);

int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char out[100];              /* output string */

int prev_type;              /* type of second-to-last token */
int in_parameters = 0;      /* 1 if we are currently parsing a function parameter */

/* uncomment for the undcl version. */
// #define UNDCL

#ifndef UNDCL

/* convert declaration to words */
int main(void)
{
    char datatype[MAXTOKEN];    /* data type = char, int, etc. */

    while (gettoken() != EOF) {
        name[0] = '\0';
        out[0] = '\0';
        typename();
        if (tokentype != '\n') {
            printf("syntax error\n");
            /* the simplest error handling... any error encountered?
             * skip to the next declaration... */
            while (tokentype != '\n')
                gettoken();
        } else if (name[0] != '\0')
            printf("%s: %s\n", name, out);
    }
    return 0;
}

#else

/* for debugging purposes */
int gettoken2()
{
    printf("prev = %d, cur = %d\n", prev_type, tokentype);
    return gettoken();
}

/* undcl: convert word description to declaration */
int main(void)
{
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token);
        while (type = gettoken(), type != '\n') {
            if (type == BRACKETS || type == PARENS) {
                /* check if this is inside a pointer, and if so, add parentheses */
                if (prev_type == '*') {
                    sprintf(temp, "(%s)%s", out, token);
                    strcpy(out, temp);
                } else
                    strcat(out, token);
            } else if (type == '*') {
                sprintf(temp, "*%s", out);
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else
                printf("invalid input at %s\n", token);
        }
        printf("%s\n", out);
    }
    return 0;
}

#endif

int getch(void);
void ungetch(int);

/* return next token */
int gettoken(void)
{
    int c;
    char *p = token;

    prev_type = tokentype;
    while (c = getch(), c == ' ' || c == '\t')
        ;
    if (c == '(') {
        if (c = getch(), c == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; *p = getch(), *p != ']' && isdigit(*p); )
            p++;
        *++p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; c = getch(), isalnum(c); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = strcmp(token, "const") == 0 ? CONST : NAME;
    } else
        return tokentype = c;
}

/* typename: parse a declarator with a leading typename */
void typename(void)
{
    char datatype[MAXTOKEN];
    char temp[100];
    int is_const = 0;

    if (tokentype == CONST) {
        is_const = 1;
        gettoken();
    }
    if (tokentype == NAME) {
        strcpy(datatype, token);
        dcl();
        sprintf(temp, "%s%s%s", out, is_const ? "const " : "", datatype);
        strcpy(out, temp);
    }
}

/* dcl: parse a declarator */
void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*'; ) /* count *'s */
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, "pointer to ");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
    int type;
    int old_in_parameters;

    if (tokentype == '(') {         /* ( dcl ) */
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
    } else if (tokentype == NAME) { /* variable name */
        if (!in_parameters)
            strcpy(name, token);
        else
            printf("error: names are not allowed for parameters\n");
    } else {
        if (!in_parameters)         /* require a name for the variable */
            printf("error: expected name or (dcl)\n");
        return;
    }

    while (type = gettoken(), type == '(' || type == PARENS || type == BRACKETS) {
        if (type == PARENS)
            strcat(out, "function returning ");
        else if (type == '(') {
            strcat(out, "function (");
            old_in_parameters = in_parameters;
            in_parameters = 1;
            do {
                gettoken();
                typename();
                if (tokentype == ',')
                    strcat(out, ", ");
            } while (tokentype == ',');
            strcat(out, ") returning ");
            in_parameters = old_in_parameters;
        } else {
            strcat(out, "array ");
            strcat(out, token);
            strcat(out, " of ");
        }
    }
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
