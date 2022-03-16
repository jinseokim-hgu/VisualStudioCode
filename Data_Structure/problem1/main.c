#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main()
{
    node_t * t1=tree_create_node(1);
    node_t * t2=tree_create_node(2);
    node_t * t3=tree_create_node(3);
    node_t * t4=tree_create_node(4);
    node_t * t5=tree_create_node(5);
    tree_add_child(t1, t2);
    tree_add_child(t1, t3);
    tree_add_child(t2, t4);
    tree_add_child(t3, t5);

    int degree = tree_degree(t1) ;

    printf("Degree : %d\n", degree);
    return 0;
}