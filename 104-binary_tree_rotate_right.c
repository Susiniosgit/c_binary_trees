#include "binary_trees.h"

/**
 * binary_tree_rotate_right - performs a right-rotation on a binary tree
 * @tree: pointer to root of tree
 * Return: pointer to the new root node of the tree once rotated
 */
binary_tree_t *binary_tree_rotate_right(binary_tree_t *tree)
{
	binary_tree_t *tmp = tree->left;

	tree->left = tmp->right;
	tree->parent = tmp;

	tmp->right = tree;
	tmp->parent = NULL;

	return (tmp);
}
