#include <stdio.h>
#include "common.h"

int main(void)
{

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

	return 0;
}