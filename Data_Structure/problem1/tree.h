typedef 
	struct _node_t {
		int data ;
		struct _node_t * child ; // left
		struct _node_t * sibling ; // right
	} 
	node_t ;

typedef struct _node_t tree_t ;

node_t * 
tree_create_node (int data) ;

node_t *
tree_add_child (node_t * parent, node_t * child) ;

int
tree_height(tree_t * t) ;

node_t *
tree_search (node_t * t, int key) ;

int
tree_degree (node_t * t) ;

int
tree_is_balanced (node_t * t) ;

int
tree_remove (node_t * t, node_t * n) ;

void
tree_print (tree_t * t) ;
