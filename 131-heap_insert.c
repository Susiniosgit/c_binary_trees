#include "binary_trees.h"

/**
 * swap - swaps two nodes in binary tree
 * @node: first node
 * @new: second node
 * Return: pointer to root
 */
bst_t *swap(bst_t *node, bst_t *new)
{
	bst_t *temp = NULL;
	_Bool left_child = false;

	if (node->parent)
		left_child = node->parent->left == node;
	if (new->parent && new->parent != node)
		new->parent->left = NULL;
	new->parent = node->parent;
	if (node->parent)
	{
		if (left_child)
			node->parent->left = new;
		else
			node->parent->right = new;
	}
	if (node->left != new)
	{
		new->left = node->left;
		node->left->parent = new;
	}
	if (node->right && node->right != new)
	{
		new->right = node->right;
		node->right->parent = new;
	}
	temp = new;
	while (temp->parent)
		temp = temp->parent;
	free(node);
	return (temp);
}

/**
 * convert - converts number and base into string
 * @num: input number
 * @base: input base
 * @lowercase: flag if hexa values need to be lowercase
 * Return: result string
 */
char *convert(unsigned long int num, int base, int lowercase)
{
	static char *rep;
	static char buffer[50];
	char *ptr;

	rep = (lowercase)
		? "0123456789abcdef"
		: "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = 0;
	do {
		*--ptr = rep[num % base];
		num /= base;
	} while (num);

	return (ptr);
}


/**
 * binary_tree_size - measures the size of a binary tree
 * @tree: input binary tree
 * Return: number of descendant child nodes
 */
size_t binary_tree_size(const binary_tree_t *tree)
{
	if (!tree)
		return (0);

	return (1 + binary_tree_size(tree->left) + binary_tree_size(tree->right));
}

/**
 * heap_insert - inserts a value in Max Binary Heap
 * @root: double pointer to root of tree
 * @value: input value
 * Return: pointer to the created node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *ht = NULL, *tmp, *ret;
	int size;
	unsigned int i;
	char *binary;
	char c;

	if (!root)
		return (NULL);
	ht = calloc(1, sizeof(heap_t));
	ht->n = value;
	if (!*root)
	{
		*root = ht;
		return (ht);
	}
	tmp = *root;
	size = binary_tree_size(tmp) + 1;
	binary = convert(size, 2, 1);
	for (i = 1; i < strlen(binary); i++)
	{
		c = binary[i];
		if (i == strlen(binary) - 1)
		{
			if (c == '1')
			{
				ht->parent = tmp;
				tmp->right = ht;
				break;
			}
			else if (c == '0')
			{
				ht->parent = tmp;
				tmp->left = ht;
				break;
			}
		}
		if (c == '1')
		{
			tmp = tmp->right;
		} else if (c == '0')
		{
			tmp = tmp->left;
		}
	}
	tmp = *root;
	if (ht->n > ht->parent->n)
	{
		printf("=====================================\n");
		printf("time to swap %i, %i\n", ht->n, ht->parent->n);
		ret = swap(ht->parent, ht);
		if (ret)
			*root = ret;
	}
	return (ht);
}
