#ifndef TREE_H
#define TREE_H

#include "Readfile.h"
#include "SizeFile.h"

struct Node_t
{
    char* data;
    Node_t* left;
    Node_t* right;
};

Node_t* CreateNode (char* value);
void Print (Node_t* node);
void DtorNode (Node_t* node);
void CreateDot (Node_t* node, FILE* file);
void PrintDot (Node_t* node);
void InteractionUser(Node_t *node);
// void NewFunction(Node_t *node);
void Guessing (Node_t* node);
void ReadDataBase ();
void SkipProb (char** str);

#endif