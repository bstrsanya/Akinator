#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Akinator.h"

// -----------------------------------Ctor & Dtor-----------------------------------------------

Node_t* NodeCtor (char* value)
{
    Node_t* new_node = (Node_t*) calloc (1, sizeof (Node_t));
    if (new_node == NULL) assert (0);

    new_node->data   = value;
    new_node->left   = NULL;
    new_node->right  = NULL;
    new_node->parent = NULL;

    return new_node;
}

void NodeDtor (Node_t* node)
{
    if (!node) return;
    
    if (node->left) NodeDtor (node->left);
    if (node->right) NodeDtor (node->right);
    if (node->type) free (node->data);
    free (node);
}

void TreeCtor (Tree* tree, const char* name_file)
{
    assert (tree);
    assert (name_file);

    FILE* file = fopen (name_file, "r");
    tree->file_data = file;
    ReadDataBase (tree);
    fclose (tree->file_data);
}

void TreeDtor (Tree* tree)
{
    NodeDtor (tree->main_node);
    free (tree->array_tree);
}

// ---------------------------------------------------------------------------------------------

void ReadDataBase (Tree* tree)
{
    size_t size = 0;
    char* str = ReadFile (tree->file_data, &size);

    tree->array_tree = str;

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
                int n = 0;
                str += 1;
                sscanf (str, "%*[^\"]%n", &n);
                str[n] = '\0';

                Node_t* ad = NodeCtor (str);
                StackPush (&stk, ad);
                str += n + 1;
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
                    parent->left = sun;
                else
                    parent->right = sun;

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
}

void SkipProb (char** str)
{
    int n = 0;
    sscanf (*str, "%*[\r \n]%n", &n);
    *str += n;
}

// ---------------------------------------------------------------------------------------------

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
        case 'G': case 'g':
            {Guessing (tree);
            break;}
        case 'I': case 'i':
            {Identify (tree);
            break;}
        case 'C': case 'c':
            {Compare (tree);
            break;}
        case 'B': case 'b':
            {ShowTree (tree->main_node);
            break;}
        case 'S': case 's':
            {
            FILE* file = fopen ("./DataAkinator.txt", "w");
            tree->file_data = file;
            SaveBinaryTree (tree->main_node, tree);
            fclose (file);
            break;}
        case 'E': case 'e':
            {isEnd = 0;
            break;}
        default:    
            printf ("Incorrect command! Try again\n");
        }
    }      
}

// ---------------------------------------------------------------------------------------------

void Guessing (Tree* tree)
{
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
        printf ("Who is it?\n");
        char* answer_0 = ScanStr (); 
        printf ("How does %s differ from %s\n", answer_0, node->data);

        char* zxc = ScanStr ();

        Node_t* dif = NodeCtor(zxc);
        dif->parent = node->parent;
        dif->type = NEW;

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

        Node_t* new_left = NodeCtor (answer_0);
        new_left->type = NEW;
        dif->left = new_left; 
        new_left->parent = dif;
    }
}

// ---------------------------------------------------------------------------------------------

void Identify (Tree* tree)
{
    char* str = ScanStr ();
    stack_t* stk = Way (tree, str);
    free (str);

    if (!stk) printf ("This character is not in the database\n");
    else 
    {
        PrintIdentify (stk);
        FreeStack (stk);
        free (stk);
    }
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
            printf ("%s, ", node_1->data);
        else
            printf ("NO %s, ", node_1->data);

        StackPush (stk, node_2);
    }

    StackPop (stk, &node_1);

    if (node_1->left == node_0)
        printf ("%s.", node_1->data);
    else
        printf ("NO %s.", node_1->data);

    putchar ('\n');
}

// ---------------------------------------------------------------------------------------------

void Compare (Tree* tree)
{
    char* str1 = ScanStr ();
    stack_t* stk1 = Way (tree, str1);
    free (str1);

    if (!stk1) printf ("This character is not in the database\n");
    else
    {
        char* str2 = ScanStr ();
        stack_t* stk2 = Way (tree, str2);
        free (str2);
        
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

    int n = 0;

    while (!(strcmp (node1_son->data, node2_son->data)))
    {
        if (!n) 
        {
            printf ("%s is similar to %s in that ", node1_main->data, node2_main->data);
            n += 1;
        }

        if (node1_parent->left == node1_son)
            printf ("%s, ", node1_parent->data);

        else
            printf ("NO %s, ", node1_parent->data);

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

    if (n) 
        printf ("but %s is %s\n", node1_main->data, node1_parent->data);
    else    
        printf ("%s is differ %s in that %s\n", node1_main->data, node2_main->data, node1_parent -> data);
}

// ---------------------------------------------------------------------------------------------

void ShowTree (Node_t* node)
{
    FILE* file_dot = fopen ("./BinaryTree.dot", "w");
    assert (file_dot != NULL);
    fprintf (file_dot, "digraph{\nsplines=\"ortho\";\n");
    GraphTreeForUser (node, file_dot);
    fprintf (file_dot, "}");
    fclose (file_dot);
    
    system ("dot ./BinaryTree.dot -Tpng -o ./BinaryTree.png");
}

// ---------------------------------------------------------------------------------------------

void SaveBinaryTree (Node_t* node, Tree* tree)
{
    if (!node) return;
    
    fprintf (tree->file_data, "{");
    fprintf (tree->file_data, "\"%s\"", node->data);
    if (node->left) SaveBinaryTree (node->left, tree);
    if (node->right) SaveBinaryTree (node->right, tree);

    fprintf (tree->file_data, "}");
}

// ---------------------------------------------------------------------------------------------
