#include "defs.h"
#include "data.h"
#include "decl.h"

static char *regList[4] = {"%r8","%r9","%r10","%r11"};

static int availReg[4];

void clearAllReg(void){
    availReg[0] = 1;
    availReg[1] = 1;
    availReg[2] = 1;
    availReg[3] = 1;
}

static int allocReg(void){
    for (int i = 0;i<4;i++){
        if (availReg[i]){
            availReg[i] = 0;
            return(i);
        }
    }
    fprintf(stderr,"No Available Register");
    exit(1);
}

static void clearReg(int reg){
    if (availReg[reg] != 0){
        fprintf(stderr,"Error trying to clear register\n");
        exit(1);
    }else{
        availReg[reg] = 1;
    }
}

void cgPre(){
    clearAllReg();
    fputs(
        "\t.text\n"
        ".LC0:\n"
        "\t.string\t\"%d\\n\"\n"
        "printint:\n"
        "\tpushq\t%rbp\n"
        "\tmovq\t%rsp, %rbp\n"
        "\tsubq\t$16, %rsp\n"
        "\tmovl\t%edi, -4(%rbp)\n"
        "\tmovl\t-4(%rbp), %eax\n"
        "\tmovl\t%eax, %esi\n"
        "\tleaq	.LC0(%rip), %rdi\n"
        "\tmovl	$0, %eax\n"
        "\tcall	printf@PLT\n"
        "\tnop\n"
        "\tleave\n"
        "\tret\n"
        "\n"
        "\t.globl\tmain\n"
        "\t.type\tmain, @function\n"
        "main:\n"
        "\tpushq\t%rbp\n"
        "\tmovq	%rsp, %rbp\n",
    Outfile);
}

void cgPost(){
    fputs(
        "\tmovl $0, %eax\n"
        "\tpopq %rbp\n"
        "\tret\n",
    Outfile);
}

int cgLoad(int val){
    int r = allocReg();
    fprintf(Outfile, "\tmovq\t$%d, %s\n",val,regList[r]);
    return(r);
}

int cgAdd(int r1,int r2){
    fprintf(Outfile,"\taddq\t%s, %s\n",regList[r1],regList[r2]);
    clearReg(r1);
    return(r2);
}

int cgSub(int r1,int r2){
    fprintf(Outfile,"\tsubq\t%s, %s\n",regList[r2],regList[r1]);
    clearReg(r2);
    return(r1);
}

int cgMulti(int r1,int r2){
    fprintf(Outfile,"\timulq\t%s, %s\n",regList[r1],regList[r2]);
    clearReg(r1);
    return(r2);
}

int cgDiv(int r1,int r2){
    fprintf(Outfile, "\tmovq\t%s,%%rax\n", regList[r1]);
    fprintf(Outfile, "\tcqo\n");
    fprintf(Outfile, "\tidivq\t%s\n", regList[r2]);
    fprintf(Outfile, "\tmovq\t%%rax,%s\n", regList[r1]);
    clearReg(r2);
    return(r1);
}

void cgPrintInt(int r){
    fprintf(Outfile, "\tmovq\t%s, %%rdi\n", regList[r]);
    fprintf(Outfile, "\tcall\tprintint\n");
    clearReg(r);
}
