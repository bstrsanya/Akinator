#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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

Tree* ReadDataBase ()
{
    Tree* tree = (Tree*) calloc (1, sizeof (Tree));
    assert (tree);

    FILE* file = fopen ("./DataAkinator.txt", "r");
    char* str;
    size_t size = 0;
    str = ReadFile (file, &size);
    fclose (file);

    char* str_copy = str; // after clean
    
    stack_t stk = {};
    StackCtor (&stk, 10);

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
                sscanf (q, "%[^0]", cal_str);
                Node_t* ad = CreateNode (cal_str);
                StackPush (&stk, ad);
                if (tree->deep < (int) stk.size) tree->deep = (int) stk.size;
            }
        }
        if (str[0] == '}')
        {
            str += 1;
            Node_t* sun = NULL;
            StackPop (&stk, &sun);
            if (stk.size != 0) 
            {
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
            else 
            {
                StackPush (&stk, sun);
            }          
        }
    }

    StackPop (&stk, &tree->main_node);
    FreeStack (&stk);
    free (str_copy);
    return tree;
}

void SkipProb (char** str)
{
    int n = 0;
    sscanf (*str, "%*[\r \n]%n", &n);
    *str += n;
}

void InteractionUser (Tree* tree)
{
    printf ("Hello! What will you choose?\n");

    int c = 0;
    int isEnd = 1;

    while (isEnd)
    {
        printf ("[G]uess [I]dentify [C]ompare\n"
        "[B]inary_tree [S]ave [E]xit\n");
        c = getchar ();
        while (!CleanBufer ())
        {
            printf ("The command must contain one letter! Try again!\n");
            c = getchar ();
        }
        switch (c)
        {
        case 'G':
            {Guessing (tree);
            break;}
        case 'I':
            {Identify (tree);
            break;}
        case 'C':
            {Compare (tree);
            break;}
        case 'B':
            {printf ("update\n");
            break;}
        case 'S':
            {printf ("update\n");
            break;}
        case 'E':
            {isEnd = 0;
            break;}
        default:    
            printf ("Incorrect command! Try again\n");
        }
    }      
}

void Compare (Tree* tree)
{
    char str1[100] = "";
    scanf ("%[^\n]", str1);
    getchar ();
    stack_t* stk1 = Way (tree, str1);

    if (!stk1) printf ("This character is not in the database\n");
    else
    {
        char str2[100] = "";
        scanf ("%[^\n]", str2);
        getchar ();
        stack_t* stk2 = Way (tree, str2);
        if (!stk2) printf ("This character is not in the database\n");
        else
        {
            PrintCompare (stk1, stk2);
            FreeStack (stk1);
            FreeStack (stk2);
            free (stk1);
            free (stk2);
        }
    }
}

void PrintCompare (stack_t* stk1, stack_t* stk2)
{
    Node_t* node1_main = NULL;
    StackPop (stk1, &node1_main);
    Node_t* node2_main = NULL;
    StackPop (stk2, &node2_main);
    Node_t* node1_parent = NULL;
    StackPop (stk1, &node1_parent);
    Node_t* node2_parent = NULL;
    StackPop (stk2, &node2_parent);
    Node_t* node1_son = NULL;
    StackPop (stk1, &node1_son);
    Node_t* node2_son = NULL;
    StackPop (stk2, &node2_son);

    printf ("Similarities: ");
    while (!(strcmp (node1_son->data, node2_son->data)))
    {
        printf ("%s ", node1_parent->data);
        StackPush (stk1, node1_son);        
        StackPush (stk2, node2_son); 
        StackPop (stk1, &node1_parent);
        StackPop (stk2, &node2_parent);
        if (stk1->size > 0 && stk2->size > 0)
        {
            StackPop (stk1, &node1_son);
            StackPop (stk2, &node2_son);
        }
        else break;
    }
    printf ("\nDifferences: %s\n", node1_parent->data);
}

void Identify (Tree* tree)
{
    char str[100] = "";
    scanf ("%[^\n]", str);
    getchar ();
    stack_t* stk = Way (tree, str);

    if (!stk) printf ("This character is not in the database\n");
    else 
    {
        PrintIdentify (stk);
        FreeStack (stk);
        free (stk);
    }
}

stack_t* Way (Tree* tree, char* str)
{
    Node_t* elem = NULL;
    Find (tree->main_node, str, &elem);
    if (!elem) return NULL;
    Node_t* elem_0 = elem;
    stack_t* stk = (stack_t*) calloc (1, sizeof (stack_t));
    StackCtor (stk, 10);
    assert (stk);

    while (elem->parent)
    {
        StackPush (stk, elem->parent);
        elem = elem->parent;
    }
    StackPush (stk, elem_0);
    return stk;
}

void PrintIdentify (stack_t* stk)
{
    Node_t* node_0 = NULL;
    StackPop (stk, &node_0);
    Node_t* node_1 = NULL;
    Node_t* node_2 = NULL;
    printf ("%s it: ", node_0->data);
    while (stk->size > 1)
    {
        StackPop (stk, &node_1);
        StackPop (stk, &node_2);
        if (node_1->left == node_2)
            printf ("%s ", node_1->data);
        else
            printf ("NO %s ", node_1->data);
        StackPush (stk, node_2);
    }
    StackPop (stk, &node_1);
    if (node_1->left == node_0)
        printf ("%s ", node_1->data);
    else
        printf ("NO %s ", node_1->data);
    putchar ('\n');
}

void Find (Node_t* node, char* str, Node_t** elem)
{
    if (!node) return;
    
    if (node->left) Find (node->left, str, elem);
    if (node->right) Find (node->right, str, elem);

    if (!strcmp (node->data, str)) *elem = node;
}

void Guessing (Tree* tree)
{
    char answer[100] = {};
    Node_t* node = tree->main_node;

    while (node->left != NULL)
    {
        printf ("%s\n", node->data);

        if (ScanYesNo ())
            node = node->left;
        else
            node = node->right;
    }

    printf ("This is %s\nI was able to guess?\n", node->data);

    if (ScanYesNo ())
        printf ("thanks\n");

    else
    {
        tree->deep += 1;
        printf ("Who is it?\n");
        int n1 = 0;
        scanf  ("%[^\n]%n", answer, &n1);
        printf ("How does %s differ from %s\n", answer, node->data);
        getchar();

        char differ[100] = {};
        int n = 0;
        scanf ("%[^\n]%n", differ, &n);
        char* zxc = (char*) calloc ((size_t) n + 1, sizeof (char));
        sscanf (differ, "%[^0]", zxc);

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
        sscanf (answer, "%[^0]", zxc1);
        getchar ();

        Node_t* new_left = CreateNode (zxc1);
        dif->left = new_left; 
        new_left->parent = dif;
    }
}

int CleanBufer ()
{
    int ch = 0, i = 0;

    while ((ch = getchar ()) != '\n' && ch != EOF)
        i++;

    if (i > 0)
        return 0;
    
    return 1;
}

int ScanYesNo ()
{
    char str[10] = "";
    int nReadParam = scanf ("%s", str);

    while (!CleanBufer () || nReadParam != 1 || !(!strcmp (str, "yes") ^ !strcmp (str, "no")))
        {
        printf ("Enter \"yes\" or \"no\"\n");
        nReadParam = scanf ("%s", str);
        }
    
    if (!strcmp (str, "yes")) return 1;
    return 0;
}