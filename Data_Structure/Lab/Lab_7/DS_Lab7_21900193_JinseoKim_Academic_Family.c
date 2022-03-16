//DS_Lab7_21900193_JinseoKim_Academic_Family.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef 
	struct _node_t {
		char * data ;
		struct _node_t * child ; // left
		struct _node_t * sibling ; // right
	} 
	node_t ;

typedef struct _node_t tree_t ;

node_t * 
tree_create_node (char * data) 
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
tree_search (node_t * t, char * key)
{
	if (strcmp(t->data, key)==0)
		return t ;

	for (node_t * i = t->child ; i != 0x0 ; i = i->sibling) {
		node_t * r ;
		r = tree_search(i, key) ;
		if (r != 0x0) 
			return r ;		
	}

	return 0x0 ;
}

void
_tree_print (node_t * t, int level)
{
	for (int i = 0 ; i < level ; i++){
		if(i<level-1){
			printf("   ") ;
		}
		else{
			printf("+--") ;
		}
	}
	printf("%s\n", t->data) ;
	
	node_t * curr ;
	for (curr = t->child ; curr != 0x0 ; curr = curr->sibling) 
		_tree_print(curr, level + 1) ;
}

void
tree_print (tree_t * t)
{
	_tree_print(t, 0) ;
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

	tree_t * t[100];
	for(int i=0; i<N; i++){
		t[i]=NULL;
	}

	char name[10000][2][65];
	int index_or;
	int index_ee;

    for(int i=0; i<M; i++){
        scanf("%s %s", name[i][0], name[i][1]);
	}

	node_t * advisor=tree_create_node(name[0][0]);
	node_t * advisee=tree_create_node(name[0][1]);
	tree_add_child(advisor, advisee);
	t[0]=advisor;

	for(int i=1; i<M; i++){
		node_t * advisor=NULL;
		node_t * advisee=NULL;

		int j=0;
        while(t[j]!=NULL){
			if(advisor==NULL){
				advisor=tree_search(t[j], name[i][0]);
				if(advisor!=NULL){
					index_or=j;
				}
			}
			if(advisee==NULL){
				advisee=tree_search(t[j], name[i][1]);
				if(advisee!=NULL){
					index_ee=j;
				}
			}
			j+=1;
        }

		if(advisor==NULL){
			advisor=tree_create_node(name[i][0]);
			if(advisee==NULL){
				advisee=tree_create_node(name[i][1]);
				tree_add_child(advisor, advisee);
				int k;
				for(k=0; t[k]!=NULL; k++);
				t[k]=advisor;
			}
			else{
        		tree_add_child(advisor, advisee);
				t[index_ee]=advisor;
			}
		}
		else{
			if(advisee==NULL){
				advisee=tree_create_node(name[i][1]);
				tree_add_child(advisor, advisee);
			}
			else{
				tree_add_child(advisor, advisee);
				t[index_or]=advisor;
				t[index_ee]=NULL;
				for(int x=0;x<N;x++){
        			for(int y=x+1;y<N;y++){
        			    if(t[x]==NULL && t[y]!=NULL){
        			        t[x]=t[y];
							t[y]=NULL;
        			        break;
        			    }
        			}
    			}
			}
		}
    }

	int a=0;
	while(t[a]!=NULL){
		tree_print(t[a]);
		a+=1;
	}
}