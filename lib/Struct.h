#ifndef STRUCT_H
#define STRUCT_H

struct Node_t
{
    char* data;
    Node_t* left;
    Node_t* right;
    Node_t* parent;
    int type;
};

typedef Node_t* StackElem_t;

#endif