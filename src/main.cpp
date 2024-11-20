#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Akinator.h"

int main ()
{
    Tree tree = {};
    TreeCtor (&tree, "./DataAkinator.txt");
    
    InteractionUser (&tree);

    TreeDtor (&tree);
}