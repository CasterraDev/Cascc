#include "defs.h"
#include "data.h"
#include "decl.h"

int computeAst(struct ASTnode *n){
    int lVal,rVal;

    if (n->left) lVal = computeAst(n->left);
    if (n->right) rVal = computeAst(n->right);

    switch(n->op){
        case(A_ADD):
            return(lVal + rVal);
            break;
        case(A_SUBTRACT):
            return(lVal - rVal);
            break;
        case(A_MULTIPLY):
            return(lVal * rVal);
            break;
        case(A_DIVIDE):
            return(lVal / rVal);
            break;
        case(A_INTLIT):
            return(n->intValue);
            break;
        default:
            fprintf(stderr,"Couldn't compute ASTnode in function computeAst() with operator: %d\n",n->op);
            exit(1);
    }
}