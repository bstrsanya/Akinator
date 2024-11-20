#include <stdio.h>

#include "Akinator.h"

// ---------------------------------------------------------------------------------------------

void GraphTreeForDebug (Node_t* node, FILE* file_dot)
{
    if (!node) return;

    fprintf (file_dot, "node%p [shape=record; style = filled; fillcolor = \"#ffe4c4\"; color = \"#800000\"; label = \"{data = %s | address (parent) = %p | address = %p | { <f0> left = %p | <f1> right = %p}}\"];\n", node, node->data, node->parent, node, node->left, node->right);

    if (node->left) 
    {
        fprintf (file_dot, "node%p: <f0> -> node%p [color = red, style = bold, arrowhead = vee, taillabel = \"yes\"];\n", node, node->left);
        GraphTreeForDebug (node->left, file_dot);
    }
    if (node->right) 
    {
        fprintf (file_dot, "node%p: <f1> -> node%p [color = red, style = bold, arrowhead = vee, taillabel = \"no\"];\n", node, node->right);
        GraphTreeForDebug (node->right, file_dot);
    }
}

void GraphTreeForUser (Node_t* node, FILE* file_dot)
{
    if (!node) return;

    fprintf (file_dot, "node%p [shape=record; style = filled; fillcolor = \"#ffe4c4\"; color = \"#800000\"; label = \"{%s}\"];\n", node, node->data);

    if (node->left) 
    {
        fprintf (file_dot, "node%p -> node%p [color = red, style = bold, arrowhead = vee, taillabel = \"yes\"];\n", node, node->left);
        GraphTreeForUser (node->left, file_dot);
    }
    if (node->right) 
    {
        fprintf (file_dot, "node%p -> node%p [color = red, style = bold, arrowhead = vee, taillabel = \"no\"];\n", node, node->right);
        GraphTreeForUser (node->right, file_dot);
    }
}

// ---------------------------------------------------------------------------------------------
