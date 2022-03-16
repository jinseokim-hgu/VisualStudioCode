//DS_Lab6_21900193_JinseoKim_linkedlist.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

linkedlist_t * 
linkedlist_alloc (int unit) 
{
	linkedlist_t * l = (linkedlist_t *) malloc(sizeof(linkedlist_t)) ;
	l->left = l  ;	
	l->right = l ;
	l->element = malloc(sizeof(int)) ;
	int * u = (int *) l->element ;
	*u = unit ;

	return l ;
}

void
linkedlist_free (linkedlist_t * l, void (* free_element)(void * e))
{
	node_t * curr ;
	node_t * next ;

	curr = l->right ;
	while (curr != l) {
		next = curr->right ;
		if (free_element != 0x0)
			free_element(curr->element) ;
		free(curr->element) ;
		free(curr) ;
		curr = next ;
	}
	free(l->element) ;
	free(l) ;
}

int 
linkedlist_length (linkedlist_t * l)
{
	int len = 0 ;

	node_t * curr = l->right ;
	while (curr != l) {
		len += 1 ;
		curr = curr->right ; 
	}
	return len ; 
}

void
linkedlist_print (linkedlist_t * l, void (* print_element)(void * e))
{
	node_t * curr ;
	node_t * next ;

	curr = l->right ;
	while (curr != l) {
		print_element(curr->element) ;
		curr = curr->right ;
	}
}

void 
linkedlist_insert (node_t * left, void * e, int unit)
{
	node_t * _new = (node_t *) malloc(sizeof(node_t)) ;
	_new->element = malloc(unit) ;
	memcpy(_new->element, e, unit) ;

	node_t * right = left->right ;

	_new->left = left ;
	_new->right = right ;

	left->right = _new ;
	right->left = _new ;
}

void
linkedlist_insert_first (linkedlist_t * l, void * e)
{
	linkedlist_insert(l, e, *((int *)(l->element))) ;
}

void
linkedlist_insert_last (linkedlist_t * l, void * e)
{
	linkedlist_insert(l->left, e, *((int *)(l->element))) ;
}

int
linkedlist_remove (linkedlist_t * l, node_t * n)
{
	if (l->left == l)
		return 1 ;

	n->left->right = n->right ;
	n->right->left = n->left ;

	free(n->element) ;
	free(n) ;
	return 0 ;
}

int 
linkedlist_remove_first (linkedlist_t * l, void * e)
{
	if (l->right == l)
		return 1 ;

	memcpy(e, l->right->element, *((int *)(l->element))) ;
	linkedlist_remove(l, l->right) ;
	return 0 ;
}

int
linkedlist_remove_last (linkedlist_t * l, void * e)
{
	if (l->left == l)
		return 1 ;

	memcpy(e, l->left->element, *((int *)(l->element))) ;
	linkedlist_remove(l, l->left) ;
	return 0 ;
}

int 
linkedlist_get (linkedlist_t * l, int pos, void * e)
{
	if (pos < 0)
		return 1 ;

	int unit = *((int *) l->element) ;
	int i = 0 ;
	node_t * curr = l->right ;
	while (i < pos && curr != l) {
		curr = curr->right ;
		i += 1 ;
	}
	if (i != pos)
		return 1 ;

	memcpy(e, curr->element, unit) ;
	return 0 ;
}

void
linkedlist_sort (linkedlist_t * l, int ( cmp_elements)(void * e1, void * e2)) 
{
	node_t * i, * j, * m ;

	int unit = *((int *)(l->element)) ;

	for (i = l->right ; i != l ; i = i->right) {
		m = i ;
		for (j = i->right ; j != l ; j = j->right) {
			if (cmp_elements(j->element, m->element) < 0)
				m = j ;
		}

		void * t = i->element ;
		i->element = m->element ;
		m->element = t ;
	}
}

void
_linkedlist_qsort (linkedlist_t * l, int (* cmp_elements)(void * e1, void * e2), node_t * begin, node_t * end)
{
	if((begin==l || end==l) || begin == end || begin->left==end) return;

	void * t;

	node_t * pivot = begin;
	node_t * lbound = begin->right;
	node_t * rbound = end;

	while(1){
		while((lbound->right!=l && lbound!=end) && cmp_elements(lbound->element, pivot->element) <= 0){
			lbound=lbound->right;
		}

		while((rbound->left!=l && rbound!=begin) && cmp_elements(pivot->element, rbound->element) < 0){
			rbound=rbound->left;
		}

		if(lbound == rbound || lbound->left == rbound){
			break;
		}

		t = lbound->element ;
		lbound->element = rbound->element ;
		rbound->element = t ;
	}
	t = rbound->element ;
	rbound->element = pivot->element ;
	pivot->element = t ;

	_linkedlist_qsort(l, cmp_elements, begin, rbound->left);
	_linkedlist_qsort(l, cmp_elements, rbound->right, end);
}

void
linkedlist_qsort (linkedlist_t * l, int (* cmp_elements)(void * e1, void * e2))
{
	/* TODO */
	_linkedlist_qsort (l, cmp_elements, l->right, l->left);
}