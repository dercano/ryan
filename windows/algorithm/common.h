#include <stdlib.h>

typedef char TreeNodeData;
typedef struct _treenode
{
	TreeNodeData d;
	struct _treenode *child;
	struct _treenode *sibling;
} TREENODE;
TREENODE* tree2_createNode(TreeNodeData c);
int tree2_addChild(TREENODE *p, TREENODE *c);
void tree2_print(const TREENODE *tnode, int depth);

void tree_init();
int tree_add(TREENODE *p, char c);
void tree_print(const TREENODE *tnode);