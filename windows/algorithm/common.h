#include <stdlib.h>

typedef char TreeNodeData;
typedef struct _treenode
{
	TreeNodeData d;
	struct _treenode *child;
	struct _treenode *sibling;
} TREENODE;
void tree_init();
int tree_add(TREENODE *p, char c);
void tree_print(const TREENODE *tnode);