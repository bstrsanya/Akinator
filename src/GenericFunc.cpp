#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Akinator.h"

// ---------------------------------------------------------------------------------------------

stack_t* Way (Tree* tree, char* str)
{
    Node_t* elem = NULL;
    Find (tree->main_node, str, &elem);

    if (!elem) return NULL;

    Node_t* elem_0 = elem;
    stack_t* stk = (stack_t*) calloc (1, sizeof (stack_t));
    StackCtor (stk, 10);

    while (elem->parent)
    {
        StackPush (stk, elem->parent);
        elem = elem->parent;
    }

    StackPush (stk, elem_0);

    return stk;
}

void Find (Node_t* node, char* str, Node_t** elem)
{
    if (!node) return;
    
    if (node->left) Find (node->left, str, elem);
    if (node->right) Find (node->right, str, elem);

    if (!strcmp (node->data, str)) *elem = node;
}

// ---------------------------------------------------------------------------------------------

int CleanBufer ()
{
    int ch = 0, i = 0;

    while ((ch = getchar ()) != '\n' && ch != EOF)
        i++;

    if (i > 0)
        return 0;
    
    return 1;
}

// ---------------------------------------------------------------------------------------------

int ScanYesNo ()
{
    char* str = ScanStr ();
    while (strcmp (str, "yes") && strcmp (str, "no"))
    {
        printf ("Input [YES] or [NO]\n");
        free (str);
        str = ScanStr ();
    }
    if (!strcmp (str, "yes")) 
    {
        free (str);
        return YES;
    }
    else
    {
        free (str);
        return NO;
    }
}

char* ScanStr ()
{
    int len = 0;
    char answer[100] = {};
    scanf  ("%99[^\n]%n", answer, &len);

    while (!CleanBufer ())
    {
        printf ("The maximum buffer size has been exceeded (100). Try again.\n");
        scanf  ("%99[^\n]%n", answer, &len);
    }

    char* zxc = (char*) calloc ((size_t) len + 1, sizeof (char));
    sscanf (answer, "%[^0]", zxc);
    return zxc;
}

// ---------------------------------------------------------------------------------------------
