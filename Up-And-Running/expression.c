#include "defs.h"
#include "data.h"
#include "decl.h"

static struct ASTnode *getFirstToken(void){
    struct ASTnode *n;

    switch(Token.token){
        //For an INTLIT make a leaf (no children) AST node
        case(T_INTLIT):
            n = mkastleaf(A_INTLIT,Token.intValue);
            //Get the next Token
            scan(&Token);
            return(n);
        default:
            fprintf(stderr,"Syntax error on line %d\n",Line);
            exit(1);
    }
}

//Convert token into ast
int asthop(int t){
    printf("ASTHOP: %d\n",t);
    switch(t){
        case(T_PLUS):
            return(A_ADD);
        case(T_MINUS):
            return(A_SUBTRACT);
        case(T_STAR):
            return(A_MULTIPLY);
        case(T_SLASH):
            return(A_DIVIDE);
        default:
            fprintf(stderr,"Unknown token in asthop() on line %d\n",Line);
            exit(1);
    }
}

struct ASTnode *multiplicativeExp(void){
    struct ASTnode  *l,*r;
    int type;

    l = getFirstToken();

    type = Token.token;
    //If there are no other tokens return the left and end
    if (type == T_EOF){
        return(l);
    }

    while(type == T_STAR || type == T_SLASH){
        scan(&Token);
        r = getFirstToken();
        l = mkastnode(asthop(type),l,r,0);
        type = Token.token;
        if (type == T_EOF){
            break;
        }
    }

    return(l);
}

struct ASTnode *addExp(void){
    struct ASTnode *l,*r;
    int type;

    l = multiplicativeExp();

    type = Token.token;

    if (type == T_EOF){
        return(l);
    }

    while(1){
        scan(&Token);

        r = multiplicativeExp();
        l = mkastnode(asthop(type),l,r,0);

        type = Token.token;
        if (type == T_EOF){
            break;
        }
    }

    return(l);
}

struct ASTnode *makeTree(void){
    return(addExp());
}
