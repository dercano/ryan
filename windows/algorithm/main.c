#include <stdio.h>
#include "common.h"
#define USE_TREE2
int main(void)
{
#ifdef USE_TREE2

	TREENODE *a = tree2_createNode('A');
	TREENODE *b = tree2_createNode('B');
	TREENODE *c = tree2_createNode('C');
	TREENODE *d = tree2_createNode('D');
	TREENODE *e = tree2_createNode('E');
	TREENODE *f = tree2_createNode('F');
	TREENODE *g = tree2_createNode('G');

	tree2_addChild(a, b);
	tree2_addChild(a, c);
	  tree2_addChild(b, d);
	  tree2_addChild(b, e);
	    tree2_addChild(e, f);
	  tree2_addChild(c, g);

	tree2_print(a, 0);


#else
	TREENODE *tree_head;
	tree_head = (TREENODE *)malloc(sizeof(TREENODE));
	tree_head->child = tree_head->sibling = NULL;
	
	tree_add(tree_head, 'a');
	tree_add(tree_head, 'b');
	tree_add(tree_head->child, 'c');
	tree_add(tree_head->child, 'd');
	tree_add(tree_head->child, 'e');

	tree_add(tree_head->child->sibling, 'f');
	tree_add(tree_head->child->sibling, 'g');

	tree_print(tree_head->child, 0);
#endif
	return 0;
}