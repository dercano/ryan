/*
***************************************************************************************************
*                                       INCLUDE FILES
***************************************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/*
***************************************************************************************************
* 
*
*   
***************************************************************************************************
*/
TREENODE* tree2_createNode(TreeNodeData c)
{
	TREENODE *i;
	i = (TREENODE *)malloc(sizeof(TREENODE));
	i->d = c;
	i->child = i->sibling = NULL;

	return i;
}

int tree2_addChild(TREENODE *p, TREENODE *c)
{
	if(p->child == NULL)
	{
		p->child = c;
	}
	else
	{
		TREENODE *i;
		i = p->child;
		while( i->sibling != NULL )
			i = i->sibling;
		i->sibling = c;
	}
	return 0;
}

void tree2_print(const TREENODE *tnode, int depth)
{
	int i;
	for(i=0 ; i<depth ; i++)
		printf("  ");

	// Child Âï°í
	printf("%c\n",tnode->d);
	if(tnode->child != NULL )
		tree2_print(tnode->child, depth+1);

	// Sibling Âï°í
	if(tnode->sibling != NULL )
		tree2_print(tnode->sibling, depth);
}