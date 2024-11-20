#ifndef AKINATOR_H
#define AKINATOR_H

#include "Readfile.h"
#include "SizeFile.h"
#include "stack.h"
#include "Struct.h"

struct Tree
{
    Node_t* main_node;
    FILE* file_data;
    char* array_tree;
};

// Akinator

Node_t* NodeCtor (char* value);
void TreeCtor (Tree* tree, const char* name_file);
void NodeDtor (Node_t* node);
void TreeDtor (Tree* tree);

void ReadDataBase (Tree* tree);
void SkipProb (char** str);

void InteractionUser(Tree* tree);

void Guessing (Tree* node);
void Identify (Tree* tree);
void PrintIdentify (stack_t* stk);
void Compare (Tree* tree);
void PrintCompare (stack_t* stk1, stack_t* stk2);
void ShowTree (Node_t* node);
void SaveBinaryTree (Node_t* node, Tree* tree);

// GraphDump
void GraphTreeForDebug (Node_t* node, FILE* file);
void GraphTreeForUser (Node_t* node, FILE* file_dot);

// GenericFunc
stack_t* Way (Tree* tree, char* str);
void Find (Node_t* node, char* str, Node_t** elem);
int CleanBufer ();
char* ScanStr ();
int ScanYesNo ();

const int YES = 1;
const int NEW = 2;
const int NO  = 0;

#endif