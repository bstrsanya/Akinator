#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "stack.h"

#include "Akinator.h"

Node_t* CreateNode (char* value)
{
    Node_t* new_node = (Node_t*) calloc (1, sizeof (Node_t));
    if (new_node == NULL) assert (0);

    new_node->data   = value;
    new_node->left   = NULL;
    new_node->right  = NULL;
    new_node->parent = NULL;

    return new_node;
}

void Print (Node_t* node)
{
    if (!node) return;
    
    printf ("{\n");
    printf ("%s", node->data);
    if (node->left) Print (node->left);
    
    if (node->right) Print (node->right);

    printf ("}\n");
}

void DtorNode (Node_t* node)
{
    if (!node) return;
    
    if (node->left) DtorNode (node->left);
    if (node->right) DtorNode (node->right);

    free (node->data);
    free (node);
}


void CreateDot (Node_t* node, FILE* file_dot)
{
    if (!node) return;

    fprintf (file_dot, "node%p [shape=record; style = filled; fillcolor = \"#ffe4c4\"; color = \"#800000\"; label = \"{data = %s | address (parent) = %p | address = %p | { <f0> left = %p | <f1> right = %p}}\"];\n", node, node->data, node->parent, node, node->left, node->right);

    if (node->left) 
    {
        fprintf (file_dot, "node%p: <f0> -> node%p [color = red, style = bold, arrowhead = vee, taillabel = \"yes\"];\n", node, node->left);
        CreateDot (node->left, file_dot);
    }
    if (node->right) 
    {
        fprintf (file_dot, "node%p: <f1> -> node%p [color = red, style = bold, arrowhead = vee, taillabel = \"no\"];\n", node, node->right);
        CreateDot (node->right, file_dot);
    }
}

void PrintDot (Node_t* node)
{
    FILE* file_dot = fopen ("./aaa.dot", "w");
    assert (file_dot != NULL);
    fprintf (file_dot, "digraph{\nsplines=\"ortho\";\n");
    CreateDot (node, file_dot);
    fprintf (file_dot, "}");
    fclose (file_dot);
    system ("dot ./aaa.dot -Tpng -o ./aaa.png");
}

void ReadDataBase (Node_t* main_node)
{
    size_t size = 0;
    FILE* file = fopen ("./DataAkinator.txt", "r");
    char* str;
    str = ReadFile (file, &size);
    fclose (file);
    char* str_copy = str;
    
    stack_t stk = {};
    StackCtor (&stk, 10);
    StackPush (&stk, main_node);

    while (str[0]) // != EOF
    {
        SkipProb (&str);
        if (str[0] == '{')
        {
            str += 1;
            SkipProb (&str);

            if (str[0] == '"')
            {
                char q[100] = {};
                int n = 0;
                sscanf (str + 1, "%[^\"]%n", q, &n);
                str += n + 2;

                char* cal_str = (char*) calloc ((size_t) n + 1, sizeof (char));
                q[n] = '"';
                sscanf (q, "%[^\"]", cal_str);
                Node_t* ad = CreateNode (cal_str);
                StackPush (&stk, ad);
            }

        }
        if (str[0] == '}')
        {
            str += 1;
            Node_t* sun = NULL;
            StackPop (&stk, &sun);
            Node_t* parent = NULL;
            StackPop (&stk, &parent);

            if (!parent->left)
            {
                parent->left = sun;
            }
            else
            {
                parent->right = sun;
            }
            sun->parent = parent;
            StackPush (&stk, parent);
            
        }
    }

    FreeStack (&stk);
    free (str_copy);
}

void SkipProb (char** str)
{
    int n = 0;
    sscanf (*str, "%*[\r \n]%n", &n);
    *str += n;
}

void InteractionUser (Node_t* node)
{
    printf ("Hello, now guess the object at the physics department, and I'll try to guess it!\n"
            "You should answer yes or no to my questions.\n Let's start!\n");
    Guessing (node);

}

void Guessing (Node_t* node)
{
    char answer[100] = {};

    while (node->left != NULL)
    {
        printf ("%s\n", node->data);
        scanf ("%s", answer);

        if (!strcmp (answer, "yes"))
        {
            node = node->left;
        }
        if (!strcmp (answer, "no"))
        {
            node = node->right;
        }
    }

    printf ("This is %s\nI was able to guess?\n", node->data);
    scanf ("%s", answer);
    if (!strcmp (answer, "yes"))
        printf ("thanks\n");

    if (!strcmp (answer, "no"))
    {
        printf ("Who is it?\n");
        int n1 = 0;
        scanf  ("%s%n", answer, &n1);
        printf ("How does %s differ from %s\n", answer, node->data);

        char differ[100] = {};
        int n = 0;
        scanf ("%s%n", differ, &n);
        char* zxc = (char*) calloc ((size_t) n + 1, sizeof (char));
        sscanf (differ, "%s", zxc);

        Node_t* dif = CreateNode(zxc);
        dif->parent = node->parent;

        if (node->parent->left == node) 
        {
            Node_t* old = node->parent->left;
            node->parent->left = dif;
            dif->right = old;
        }
        else
        {
            Node_t* old = node->parent->right;
            node->parent->right = dif;
            dif->right = old;
        }
        node->parent = dif;
        char* zxc1 = (char*) calloc ((size_t) n1 + 1, sizeof (char));
        sscanf (answer, "%s", zxc1);

        Node_t* new_left = CreateNode (zxc1);
        dif->left = new_left; 
        new_left->parent = dif;
    }
}
