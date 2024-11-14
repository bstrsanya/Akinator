#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Akinator.h"

int main()
{    
    char differ6[] = "MAIN";
    char* zxc6 = (char*) calloc (70, sizeof (char));
    sscanf (differ6, "%s", zxc6);
    Node_t* main_node = CreateNode (zxc6);
    ReadDataBase(main_node);

    InteractionUser (main_node);

    
    PrintDot (main_node);
    DtorNode (main_node);
}