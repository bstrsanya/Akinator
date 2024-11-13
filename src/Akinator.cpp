#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Akinator.h"

Node_t* CreateNode (char* value)
{
    Node_t* new_node = (Node_t*) calloc (1, sizeof (Node_t));
    if (new_node == NULL) assert (0);

    new_node->data = value;

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

    fprintf (file_dot, "node%p [shape=record; style = filled; fillcolor = \"#ffe4c4\"; color = \"#800000\"; label = \"{data = %s | address = %p | { <f0> left = %p | <f1> right = %p}}\"];\n", node, node->data, node, node->left, node->right);

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

void ReadDataBase ()
{
    size_t size = 0;
    FILE* file = fopen ("./DataAkinator.txt", "r");
    char* str;
    str = ReadFile (file, &size);
    char* str_copy = str;
    
    while (str[0]) // != EOF
    {
        SkipProb (&str);
        if (str[0] == '{')
        {
            printf ("Создание нового узла\n");
            str += 1;
        }
        if (str[0] == '}')
        {
            printf ("Закрытие узла\n");
            str += 1;
        }
        if (str[0] == '"')
        {
            char q[100] = {};
            int n = 0;
            sscanf (str + 1, "%[^\"]%n", q, &n); // begin reading after ' " '
            printf ("Data = %s\n", q);
            str += n + 2;                        // skip ' " ... " '
        }
    }


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
    Node_t* way[10] = {};
    way[0] = node;
    int i = 0;

    char answer[100] = {};

    while (way[i]->left != NULL)
    {
        i++;
        printf ("%s\n", way[i-1]->data);
        scanf ("%s", answer);

        if (!strcmp (answer, "yes"))
        {
            way[i] = way[i-1]->left;
        }
        if (!strcmp (answer, "no"))
        {
            way[i] = way[i-1]->right;
        }
    }

    printf ("This is %s\nI was able to guess?\n", way[i]->data);
    scanf ("%s", answer);
    if (!strcmp (answer, "yes"))
        printf ("thanks\n");

    if (!strcmp (answer, "no"))
    {
        printf ("Who is it?\n");
        int n1 = 0;
        scanf  ("%s%n", answer, &n1);
        printf ("How does %s differ from %s\n", answer, way[i]->data);

        char differ[100] = {};
        int n = 0;
        scanf ("%s%n", differ, &n);
        char* zxc = (char*) calloc ((size_t) n, sizeof (char));
        sscanf (differ, "%s", zxc);


        Node_t* dif = CreateNode(zxc);

        if (way[i-1]->left == way[i]) 
        {
            Node_t* old = way[i-1]->left;
            way[i-1]->left = dif;
            dif->right = old;
        }
        else
        {
            Node_t* old = way[i-1]->right;
            way[i-1]->right = dif;
            dif->right = old;
        }

        char* zxc1 = (char*) calloc ((size_t) n1, sizeof (char));
        sscanf (answer, "%s", zxc1);

        Node_t* new_left = CreateNode (zxc1);
        dif->left = new_left; 
    }
}
