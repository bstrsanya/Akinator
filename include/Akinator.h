#ifndef TREE_H
#define TREE_H

#include "Readfile.h"
#include "SizeFile.h"

struct Node_t
{
    char* data;
    Node_t* left;
    Node_t* right;
    Node_t* parent;
};

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
void Identify (Tree* tree, char* str);

#endif