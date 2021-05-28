//Functions for all compiler files

int scan(struct token *t);

struct ASTnode *mkastnode(int op,struct ASTnode *left,struct ASTnode *right,int intValue);
struct ASTnode *mkastleaf(int op,int intValue);
struct ASTnode *mkastsingle(int op,struct ASTnode *left,int intValue);
struct ASTnode *makeTree(void);
int computeAst(struct ASTnode *n);

static int ASTGen(struct ASTnode *n);
void generateCode(struct ASTnode *n);

void clearAllReg(void);
void cgPre();
void cgPost();
int cgLoad(int value);
int cgAdd(int r1, int r2);
int cgSub(int r1, int r2);
int cgMulti(int r1, int r2);
int cgDiv(int r1, int r2);
void cgPrintInt(int r);