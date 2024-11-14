#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Akinator.h"

int main()
{   
    Tree* tree = ReadDataBase();
    assert (tree);
    InteractionUser (tree);
    
    PrintDot (tree->main_node);
    DtorNode (tree->main_node);
    free (tree);
}