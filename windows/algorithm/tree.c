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
*                                       CONSTANTS
***************************************************************************************************
*/


/*
***************************************************************************************************
*                                       MACROS
***************************************************************************************************
*/


/*
***************************************************************************************************
*                                       DATATYPES
***************************************************************************************************
*/



/*
***************************************************************************************************
*                                       CONST TABLES
***************************************************************************************************
*/


/*
***************************************************************************************************
*                                       VARIABLES
***************************************************************************************************
*/
//TREENODE *tree_head;

/*
***************************************************************************************************
* 
*
*   
***************************************************************************************************
*/
//void tree_init()
//{
//	tree_head = (TREENODE *)malloc(sizeof(TREENODE));
//	tree_head->child = tree_head;
//	tree_head->sibling = tree_head;
//}

int tree_add(TREENODE *p, char c)
{
	TREENODE *it, *n;

	it = (TREENODE *)malloc(sizeof(TREENODE));
	it->d = c;

	if( p->child == NULL )
	{
		//Child ����.
		p->child = it;
	}
	else
	{
		// Child node ����.
		n = p->child;
		while( n->sibling != NULL)
			n = n->sibling;
		n->sibling = it;
	}
	it->child = it->sibling = NULL;

	return 0;
}

void tree_print(const TREENODE *tnode, int depth)
{
	int i;
	for(i=0 ; i<depth ; i++)
		printf("  ");

	// Child ���
	printf("%c\n",tnode->d);
	if(tnode->child != NULL )
		tree_print(tnode->child, depth+1);

	// Sibling ���
	if(tnode->sibling != NULL )
		tree_print(tnode->sibling, depth);
}