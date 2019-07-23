#include "binary_trees.h"

avl_t *rebalance(avl_t *node)
{
	avl_t *tmp, *z, *x, *y;
	int bal;

	tmp = node->parent;
	while (tmp)
	{
		bal = binary_tree_balance(tmp);
		printf("bal = %i\n", bal);
		if (bal > 1)
		{
			/* right rotate */
			z = tmp;
			printf("z's value = %i\n", z->n);
			y = z->right;
			x = binary_tree_balance(y) < 0 ? y->left : y->right;
			printf("done\n");
			if (x == y->left)
			{
				binary_tree_rotate_left(z);
				printf("rotate right success!\n");
			}
			else
			{
				binary_tree_rotate_right(y);;
				printf("rotate right success!\n");
				return (binary_tree_rotate_left(z));
			}
		} else if (bal < 1)
		{
			/* left rotate */
			z = tmp;
			printf("z's value = %i\n", z->n);
			y = z->left;
			x = binary_tree_balance(y) < 0 ? y->left : y->right;
			printf("done\n");
			if (x == y->left)
			{
				binary_tree_rotate_right(z);
				printf("rotate left success!\n");
			}
			else
			{
				binary_tree_rotate_left(y);;
				printf("rotate left success!\n");
				return (binary_tree_rotate_right(z));
			}
		}
		tmp = tmp->parent;
	}
	return (NULL);
}




/**
 * avl_insert - inserts a value in an AVL Tree
 * @tree: double pointer to root of tree
 * @value: input value
 * Return: pointer to the created node, or NULL on failure
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	avl_t *av, *node;

	if (!tree)
		return (NULL);
	av = calloc(1, sizeof(avl_t));
	if (!av)
		return (NULL);
	av->n = value;

	if (!*tree)
	{
		*tree = av;
		return (av);
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
				av->parent = node;
				return (rebalance(node->left = av));
			}
			node = node->left;
		} else
		{
			if (!node->right)
			{
				av->parent = node;
				return (rebalance(node->right = av));
			}
			node = node->right;
		}
	}
	return (NULL);
}
