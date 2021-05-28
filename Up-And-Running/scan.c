#include "defs.h"
#include "data.h"
#include "decl.h"

//Get the position of a character from a string
static int charPos(char *s,int c){
    char *p;
    p = strchr(s,c);
    return (p ? p - s : -1);
}
//Move to the next character
static int next(void){
    int c;

    if(Putback){
        c = Putback;
        Putback = 0;
        return c;
    }

    c = fgetc(Infile);
    if ('\n' == c){
        Line++;
    }
    return c;
}

//Put back a character we don't need
static void putback(int c){
    Putback = c;
}

//skip whitespace
//Like tabs, spaces, line breaks
static int skipWhiteSpace(void){
    int c;

    c = next();
    while (' ' == c || '\t' == c || '\f' == c || '\r' == c || '\n' == c){
        c = next();
    }

    return(c);
}

static int scanInt(int c){
    int k,val=0;

    //Use charPos() to find the pos of k
    while((k = charPos("0123456789",c)) >= 0){
        val = val * 10 + k;
        c = next();
    }

    //Put back the non-integer character
    putback(c);
    return(val);
}

int scan(struct token *t){
    int c;

    c = skipWhiteSpace();

    switch(c){
        case EOF:
            t->token = T_EOF;
            return(0);
        case('+'):
            t->token = T_PLUS;
            break;
        case('-'):
            t->token = T_MINUS;
            break;
        case('/'):
            t->token = T_SLASH;
            break;
        case('*'):
            t->token = T_STAR;
            break;
        default:
            if (isdigit(c)){
                t->intValue = scanInt(c);
                t->token = T_INTLIT;
                break;
            }

            printf("Unrecognised character %c on line %d\n",c,Line);
            exit(1);
    }
    //We found a token
    return(1);
}
