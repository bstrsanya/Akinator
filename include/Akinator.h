#ifndef TREE_H
#define TREE_H

#include "Readfile.h"
#include "SizeFile.h"
#include "stack.h"
#include "Struct.h"

struct Tree
{
    Node_t* main_node;
    int deep;
};

typedef Node_t* StackElem_t;

Node_t* CreateNode (char* value);
void Print (Node_t* node);
void DtorNode (Node_t* node);
void CreateDot (Node_t* node, FILE* file);
void PrintDot (Node_t* node);
void InteractionUser(Tree* tree);
// void NewFunction(Node_t *node);
void Guessing (Tree* node);
Tree* ReadDataBase ();
void SkipProb (char** str);
int CleanBufer ();
int ScanYesNo ();
void Find (Node_t* node, char* str, Node_t** elem);
void Identify (Tree* tree);
void Compare (Tree* tree);
stack_t* Way (Tree* tree, char* str);
void PrintIdentify (stack_t* stk);
void PrintCompare (stack_t* stk1, stack_t* stk2);
char* ScanStr ();

#endif