#include "binary_trees.h"

/**
 * balance_left - balances left side
 * @node: pointer to temp node
 */
void balance_left(avl_t *node)
{
	avl_t *z, *x, *y;

	z = node;
	y = z->left;
	if (!y)
		return;
	x = binary_tree_balance(y) < 0 ? y->right : y->left;
	if (!x)
		return;
	if (x == y->left)
	{
		binary_tree_rotate_right(z);
	} else
	{
		binary_tree_rotate_left(y);
		binary_tree_rotate_right(z);
	}
}

/**
 * balance_right - balances right side
 * @node: pointer to temp node
 */
void balance_right(avl_t *node)
{
	avl_t *z, *x, *y;

	z = node;
	y = z->right;
	if (!y)
		return;
	x = binary_tree_balance(y) < 0 ? y->right : y->left;
	if (!x)
		return;
	if (x == y->right)
	{
		binary_tree_rotate_left(z);
	} else
	{
		binary_tree_rotate_right(y);
		binary_tree_rotate_left(z);
	}

}

/**
 * rebalance - rebalance AVL tree
 * @node: pointer to node to rebalance
 * Return: pointer to input node
 */
avl_t *rebalance(avl_t *node)
{
	avl_t *tmp;
	int bal;

	tmp = node->parent;
	while (tmp)
	{
		bal = binary_tree_balance(tmp);
		if (bal > 1)
			balance_left(tmp);
		else if (bal < -1)
			balance_right(tmp);
		tmp = tmp->parent;
	}
	return (node);
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
