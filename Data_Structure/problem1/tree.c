#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

node_t * 
tree_create_node (int data) 
{
	node_t * root ;
	root = (node_t *) malloc(sizeof(node_t)) ;
	root->data = data ;
	root->child = 0x0 ;
	root->sibling = 0x0 ; 
	return root ;
}

node_t *
tree_add_child (node_t * parent, node_t * child)
{
	if (parent->child == 0x0) {
		parent->child = child ;
	}
	else {
		node_t * curr ;
		for (curr = parent->child ; curr->sibling != 0x0 ; curr = curr->sibling) ;
		// curr->sibling == 0x0  
		curr->sibling = child ;

	}
	return parent ;
}

int
tree_height(tree_t * t) 
{
	int max = 0 ; 
	node_t * c ;
	for (c = t->child ; c != 0x0 ; c = c->sibling) {
		int h = tree_height(c) ;
		max = (max < h) ? h : max ;
	}
	return max + 1 ;
}

node_t *
tree_search (node_t * t, int key)
{
	if (t->data == key)
		return t ;

	for (node_t * i = t->child ; i != 0x0 ; i = i->sibling) {
		node_t * r ;
		r = tree_search(i, key) ;
		if (r != 0x0) 
			return r ;		
	}

	return 0x0 ;
}

int
tree_degree (node_t * t)
{
	/* 	TODO: implement here 

		int tree_degree (node_t *t)
		
		Return the degree of the given tree t.
	*/
	int max = 0;
	int degree = 0 ;
	node_t * c ;
	for(c = t->child ; c != 0x0 ; c = c->sibling){
		degree += 1;
		int d = tree_degree(c);
		max = (degree < d) ? d : degree ;
	}
	return max ;
}

int
tree_is_balanced (node_t * t)
{
	/*	TODO: impelement here

		int tree_is_balanced (node_t * t)

		Check whether or not tree t is balanced. A tree is 
		balanced when it is empty, or the height difference of 
		every pair of sibling subtrees is always no more than 1.
		
		Return 1 if tree t is balanced. Otherwise, return 0.
	*/
	if(t==NULL) return 1 ;
	node_t * c ;
	for(c = t->child ; c != 0x0 ; c = c->sibling){

		int balance = tree_is_balanced(c);
		if(balance==0){
			return 0;
		}
	}
}

int
tree_remove (node_t * t, node_t * n)
{
	/*	TODO: impelement this function 

		int tree_remove(node_t * t, node_t * n)

		Remove a given node n from a given tree t. If a node n 
		has one or more children nods, they become children of 
		n's parent node and take the place of n in the sibling list.

		Return 0 if the remove operation was successful.
		Return 1 if there is no node n in the given tree t.
	*/
	if(t==NULL) return 1 ;
	node_t * c ;
	if(c = tree_search(t, n->data) == NULL) return 1 ;
	else {
		if(c->child == NULL) free(n);
		else if(c->child != NULL && c->child->sibling == NULL)  
	}
}



void
_tree_print (node_t * t, int level)
{
	for (int i = 0 ; i < level ; i++)
		printf("  ") ;
	printf("%d\n", t->data) ;
	
	node_t * curr ;
	for (curr = t->child ; curr != 0x0 ; curr = curr->sibling) 
		_tree_print(curr, level + 1) ;
}

void
tree_print (tree_t * t)
{
	_tree_print(t, 0) ;
}
