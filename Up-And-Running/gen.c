#include "defs.h"
#include "data.h"
#include "decl.h"

static int ASTGen(struct ASTnode *n){
    int lVal, rVal;

    if (n->left) lVal = ASTGen(n->left);
    if (n->right) rVal = ASTGen(n->right);

    switch(n->op){
        case(A_ADD):
            cgAdd(lVal,rVal);
            break;
        case(A_SUBTRACT):
            cgSub(lVal,rVal);
            break;
        case(A_MULTIPLY):
            cgMulti(lVal,rVal);
            break;
        case(A_DIVIDE):
            cgDiv(lVal,rVal);
            break;
        case(A_INTLIT):
            cgLoad(n->intValue);
            break;
        default:
            fprintf(stderr,"Couldn't compute ASTnode in function computeAst() with operator: %d\n",n->op);
            exit(1);
    }
}

void generateCode(struct ASTnode *n){
    int reg;

    cgPre();
    reg = ASTGen(n);
    cgPrintInt(reg);
    cgPost();
}
