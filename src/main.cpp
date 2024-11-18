#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Akinator.h"

int main()
{   
    Tree tree = {};
    TreeCtor (&tree, "./DataAkinator.txt");
    assert (&tree);
    
    InteractionUser (&tree);

    TreeDtor (&tree);
}