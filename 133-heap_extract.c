#include "binary_trees.h"

/**
 * swap_head - helper func to swap head and node
 * @head: pointer to head
 * @node: pointer to node
 * Return: pointer to severed head of tree
 */
heap_t *swap_head(heap_t *head, heap_t *node)
{
	if (node->parent->left == node)
	{
		node->parent->left = NULL;
	} else
		node->parent->right = NULL;
	node->parent = NULL;
	node->left = head->left;
	node->right = head->right;
	if (head->left)
		head->left->parent = node;
	if (head->right)
		head->right->parent = node;
	return (head);
}

/**
 * perc_down - percolate head into correct position
 * @node: pointer to head
 * Return: pointer to head of tree
 */
heap_t *perc_down(heap_t *node)
{
	int max;
	_Bool left_child = false;

	if (!node || (!node->left && !node->right))
	{
		while (node->parent)
			node = node->parent;
		return (node);
	}
	if (node->left && node->right)
	{
		max = MAX(node->left->n, node->right->n);
		if (max == node->left->n)
			left_child = true;
	}
	else if (node->left && !node->right)
	{
		max = node->left->n;
		left_child = true;
	}
	else if (!node->left && node->right)
		max = node->right->n;
	if (node->n <= max)
	{
		if (left_child)
		{
			swap(node, node->left);
			perc_down(node);
		} else
		{
			swap(node, node->right);
			perc_down(node);
		}
	}
	while (node->parent)
		node = node->parent;
	return (node);
}

/**
 * heap_extract - extracts the root node of a Max Binary Heap
 * @root: double pointer to root of tree
 * Return: value stored in the root node
 */
int heap_extract(heap_t **root)
{
	size_t size, i;
	char *binary;
	char c;
	int res;
	heap_t *tmp, *head;

	if (!root || !*root)
		return (0);
	tmp = *root;
	size = binary_tree_size(*root);
	if (size == 1)
	{
		res = tmp->n;
		free(tmp);
		*root = NULL;
		return (res);
	}
	binary = convert(size, 2, 1);

	for (i = 1; i < strlen(binary); i++)
	{

		c = binary[i];
		if (i == strlen(binary) - 1)
		{
			if (c == '1')
			{
				tmp = tmp->right;
				break;
			}
			else if (c == '0')
			{
				tmp = tmp->left;
				break;
			}
		}
		if (c == '1')
			tmp = tmp->right;
		else if (c == '0')
			tmp = tmp->left;
	}

	head = *root;
	head = swap_head(head, tmp);
	res = head->n;
	free(head);
	*root = tmp;
	tmp = perc_down(tmp);
	*root = tmp;
	return (res);
}
