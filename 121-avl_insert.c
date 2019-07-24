#include "binary_trees.h"

avl_t *r = NULL;

/**
 * balance_left - balances left side
 * @node: pointer to temp node
 */
avl_t *balance_left(avl_t *node)
{
	avl_t *z, *x, *y, *ret;

	z = node;
	y = z->left;
	if (!y)
		return (NULL);
	x = binary_tree_balance(y) < 0 ? y->right : y->left;
	if (!x)
		return (NULL);
	if (x == y->left)
	{
		printf("rotate right\n");
		ret = binary_tree_rotate_right(z);
		binary_tree_print(r);
		return (ret);
	} else
	{
		printf("rotate left\n");
		binary_tree_rotate_left(y);
		binary_tree_print(r);
		printf("rotate right\n");
		ret = binary_tree_rotate_right(z);
		binary_tree_print(r);
		return (ret);
	}
	return (NULL);
}

/**
 * balance_right - balances right side
 * @node: pointer to temp node
 */
avl_t *balance_right(avl_t *node)
{
	avl_t *z, *x, *y, *ret;

	z = node;
	y = z->right;
	if (!y)
		return (NULL);
	x = binary_tree_balance(y) < 0 ? y->right : y->left;
	if (!x)
		return (NULL);
	if (x == y->right)
	{
		printf("rotate left\n");
		ret = binary_tree_rotate_left(z);
		binary_tree_print(r);
		return (ret);
	} else
	{
		printf("rotate right\n");
		binary_tree_rotate_right(y);
		binary_tree_print(r);
		printf("rotate left\n");
		ret = binary_tree_rotate_left(z);
		binary_tree_print(r);
		return (ret);
	}
	return (NULL);
}

/**
 * rebalance - rebalance AVL tree
 * @node: pointer to node to rebalance
 * Return: pointer to input node
 */
avl_t *rebalance(avl_t *node, avl_t **tree)
{
	avl_t *tmp, *root;
	int bal;

	tmp = node->parent;
	while (tmp)
	{
		bal = binary_tree_balance(tmp);
		printf("balance = %i\n", bal);
		if (bal > 1)
		{
			root = balance_left(tmp);
			if (root)
				*tree = root;
		}
		else if (bal < -1)
		{
			root = balance_right(tmp);
			if (root)
				*tree = root;
		}
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

	r = *tree;

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
				node->left = av;
				binary_tree_print(*tree);
				return (rebalance(node->left, tree));
			}
			node = node->left;
		} else
		{
			if (!node->right)
			{
				av->parent = node;
				node->right = av;
				binary_tree_print(*tree);
				return (rebalance(node->right, tree));
			}
			node = node->right;
		}
	}
	return (NULL);
}
