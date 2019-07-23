#include "binary_trees.h"

/**
 * bst_insert - inserts a value in a Binary Search Tree
 * @tree: double pointer to root of tree
 * @value: input value
 * Return: pointer to the created node, or NULL on failure
 */
bst_t *bst_insert(bst_t **tree, int value)
{
	binary_tree_t *bt = NULL, *node;

	if (!tree)
		return (NULL);
	bt = calloc(1, sizeof(binary_tree_t));
	if (!bt)
		return (NULL);
	bt->n = value;

	if (!*tree)
	{
		*tree = bt;
		return (bt);
	}

	node = *tree;
	while (node)
	{
		if (value == node->n)
			return (NULL);
		if (value < node->n)
		{
			if (!node->left)
			{
				bt->parent = node;
				return (node->left = bt);
			}
			node = node->left;
		} else
		{
			if (!node->right)
			{
				bt->parent = node;
				return (node->right = bt);
			}
			node = node->right;
		}
	}
	return (NULL);
}
