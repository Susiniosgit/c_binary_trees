#include "binary_trees.h"

/**
 * bst_insert - inserts a value in a Binary Search Tree
 * @tree: double pointer to root of tree
 * @value: input value
 * Return: pointer to the created node, or NULL on failure
 */
bst_t *bst_insert(bst_t **tree, int value)
{
	binary_tree_t *bt = NULL;

	bt = calloc(1, sizeof(binary_tree_t));
	if (!bt)
		return (NULL);
	bt->n = value;

	/* insert as root */
	if (!*tree)
	{
		*tree = bt;
		return (bt);
	}

	/* traverse left */
	if (value < tree->n)
	{

	} else
	{

	}

}
