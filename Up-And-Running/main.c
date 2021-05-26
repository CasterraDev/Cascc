#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <errno.h>

char *tokstr[] = {"+","-","*","/","intlit"};

static void usage(char *p){
    fprintf(stderr,"Usage: %s infile\n",p);
    exit(1);
}

static void scanFile(){
    struct token t;
    
    while(scan(&t)){
        printf("Token %s", tokstr[t.token]);
        if (t.token == T_INTLIT){
            printf(", value %d", t.intValue);
        }
        printf("\n");
    }
}

void main(int argc,char *argv[]){
    if (argc != 2){
        usage(argv[0]);
    }

    Line = 1;
    Putback = '\n';

    if ((Infile = fopen(argv[1],"r")) == NULL){
        fprintf(stderr,"Unable to open %s: %s\n",argv[1],strerror(errno));
        exit(1);
    }

    scanFile();
    exit(0);
}