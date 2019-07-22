#include "binary_trees.h"

/**
 * binary_tree_rotate_left - performs a left-rotation on a binary tree
 * @tree: pointer to root of tree
 * Return: pointer to the new root node of the tree once rotated
 */
binary_tree_t *binary_tree_rotate_left(binary_tree_t *tree)
{
	binary_tree_t *tmp = tree->right;

	tree->right = tmp->left;
	tree->parent = tmp;

	tmp->left = tree;
	tmp->parent = NULL;

	return (tmp);
}
