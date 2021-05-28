#include "defs.h"
#include "decl.h"
#include "data.h"

struct ASTnode *mkastnode(int op,struct ASTnode *left,struct ASTnode *right,int intValue){
    struct ASTnode *n;

    n = (struct ASTnode *) malloc(sizeof(struct ASTnode));

    if (n == NULL){
        fprintf(stderr,"Could Not Make ASTNode in mkastnode()\n");
        exit(1);
    }

    n->op = op;
    n->left = left;
    n->right = right;
    n->intValue = intValue;
    return(n);
}
//Make a node with no children
struct ASTnode *mkastleaf(int op,int intValue){
    return(mkastnode(op,NULL,NULL,intValue));
}
//Make a node with one child
struct ASTnode *mkastsingle(int op,struct ASTnode *left,int intValue){
    return(mkastnode(op,left,NULL,intValue));
}