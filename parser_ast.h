#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tokenType {
	int tokenNumber;
	char *tokenValue;
};
typedef struct nodeType {
	struct tokenType token;
	enum {terminal, nonterm} noderep;
	struct nodeType *son;
	struct nodeType *brother;
}Node;
	
enum nodeNumber {
	ACTUAL_PARAM,   ADD,            ADD_ASSIGN,     ARRAY_VAR,      ASSIGN_OP,
	CALL,           COMPOUND_ST,    CONST_NODE,     DCL,            DCL_ITEM,
	DCL_LIST,       DCL_SPEC,       DIV,            DIV_ASSIGN,     EQ,
	ERROR_NODE,     EXP_ST,         FORMAL_PARA,    FUNC_DEF,       FUNC_HEAD,
	GE,             GT,		IDENT,          IF_ELSE_ST,     IF_ST,
	INDEX,          INT_NODE,	LE,             LOGICAL_AND,    LOGICAL_NOT,
	LOGICAL_OR,     LT,		MOD,            MOD_ASSIGN,     MUL,
	MUL_ASSIGN,     NE,		NUMBER,         PARAM_DCL,      POST_DEC,
	POST_INC,       PRE_DEC,        PRE_INC,        PROGRAM,        RETURN_ST,
	SIMPLE_VAR,     STAT_LIST,      SUB,            SUB_ASSIGN,     UNARY_MINUS,
	VOID_NODE,      WHILE_ST
};

char *nodeName[] = {
    "ACTUAL_PARAM", "ADD",         "ADD_ASSIGN",  "ARRAY_VAR",   "ASSIGN_OP",
    "CALL",         "COMPOUND_ST", "CONST_NODE",  "DCL",         "DCL_ITEM",
    "DCL_LIST",     "DCL_SPEC",    "DIV",         "DIV_ASSIGN",  "EQ",
    "ERROR_NODE",   "EXP_ST",      "FORMAL_PARA", "FUNC_DEF",    "FUNC_HEAD",
    "GE",           "GT",          "IDENT",       "IF_ELSE_ST",  "IF_ST",
    "INDEX",        "INT_NODE",    "LE",          "LOGICAL_AND", "LOGICAL_NOT",
    "LOGICAL_OR",   "LT",          "MOD",         "MOD_ASSIGN",  "MUL",
    "MUL_ASSIGN",   "NE",          "NUMBER",      "PARAM_DCL",   "POST_DEC",
    "POST_INC",     "PRE_DEC",     "PRE_INC",     "PROGRAM",     "RETURN_ST",
    "SIMPLE_VAR",   "STAT_LIST",   "SUB",         "SUB_ASSIGN",  "UNARY_MINUS",
    "VOID_NODE",    "WHILE_ST"
};

int ruleName[] = {
    0, PROGRAM, 0, 0, 0,
    0, FUNC_DEF, FUNC_HEAD, DCL_SPEC, 0,
    0, 0, 0, CONST_NODE, INT_NODE,
    VOID_NODE, 0, FORMAL_PARA, 0, 0,
    0, 0, PARAM_DCL, COMPOUND_ST, DCL_LIST,
    DCL_LIST, 0, 0, DCL, 0,
    0, DCL_ITEM, DCL_ITEM, SIMPLE_VAR, ARRAY_VAR,
    0, 0, STAT_LIST, 0, 0,
    0, 0, 0, 0, 0,
    0, EXP_ST, 0, 0, IF_ST,
    IF_ELSE_ST, WHILE_ST, RETURN_ST, 0, 0,
    ASSIGN_OP, ADD_ASSIGN, SUB_ASSIGN, MUL_ASSIGN, DIV_ASSIGN,
    MOD_ASSIGN, 0, LOGICAL_OR, 0, LOGICAL_AND,
    0, EQ, NE, 0, GT,
    LT, GE, LE, 0, ADD,
    SUB, 0, MUL, DIV, MOD,
    0, UNARY_MINUS, LOGICAL_NOT, PRE_INC, PRE_DEC,
    0, INDEX, CALL, POST_INC, POST_DEC,
    0, 0, ACTUAL_PARAM, 0, 0,
    0, 0, 0
};
/*
char* toString(char* temp);
Node* buildNode(int tokenNumber, char* tokenValue);
Node* buildTree(int tokenNumber, Node* son);
void appendNext(Node* node, Node* next);
void printNode(Node *pt, int indent, FILE* astFile);
void printTree(Node *ptr, int indent, FILE* astFile);
*/

Node* buildNode(int tokenNumber, char* tokenValue)
{
    Node *ptr;

    ptr = (Node *) malloc(sizeof(Node));

    if (!ptr) {
        printf("malloc error in buildNode()\n");
        exit(1);
    }

    ptr->token.tokenNumber = tokenNumber;
    ptr->token.tokenValue = tokenValue;
    ptr->noderep = terminal;
    ptr->son = ptr->brother = NULL;
    return ptr;
}

Node* buildTree(int tokenNumber, Node* son)
{
    Node *ptr;

    ptr = (Node*) malloc(sizeof(Node));
    if (!ptr) {
        printf("malloc error in buildTree()\n");
        exit(1);
    }

    ptr->token.tokenNumber = tokenNumber;
    ptr->token.tokenValue = NULL;
    ptr->noderep = nonterm;
    ptr->son = son;
    ptr->brother = NULL;

    return ptr;
}

void appendNext(Node* node, Node* next)
{
    Node *ptr = node;
    int i = 1;
    while (ptr->brother != NULL) {
        ptr = ptr->brother;
        i++;
    }
    ptr->brother = next;
}

void printNode(Node *pt, int indent, FILE* astFile)
{
    int i;
    for (i = 1; i <= indent; i++) {
        fprintf(astFile, "     ");
    }

    if (pt->noderep == terminal)    {
        fprintf(astFile, "Terminal: %s\n", pt->token.tokenValue);
    } 
    else {
        fprintf(astFile, "Nonterminal: %s\n", nodeName[(int)(pt->token.tokenNumber)]);
    }
}

void printTree(Node *ptr, int indent, FILE* astFile)
{
    Node *p = ptr;
    while (p != NULL) {
        printNode(p, indent, astFile);
        if (p->noderep == nonterm) {
            printTree(p->son, indent + 1, astFile);
        }
        p = p->brother;
    }
}
