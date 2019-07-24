#include "binary_trees.h"

#define INIT_NODE {0, NULL, NULL, NULL}
/**
 * swap - swaps two nodes in binary tree
 * @a: first node
 * @b: second node
 * Return: pointer to root
 */
bst_t *swap(bst_t *a, bst_t *b)
{
	bst_t a_copy = INIT_NODE;

	printf("SWAP!: %d with %d\n", a->n, b->n);
	
	a_copy.n = a->n;
	a_copy.parent = a->parent;
	a_copy.left = a->left;
	a_copy.right = a->right;

	a->parent = b;
	a->left = b->left;
	a->right = b->right;

	b->parent = a_copy.parent;
	if (b == a_copy.left)
	{
		b->left = a;
		b->right = a_copy.right;
	}
	else
	{
		b->right = a;
		b->left = a_copy.left;
	}
	while (b->parent)
		b = b->parent;
	return (b);
}

/**
 * swap_old - swaps two nodes in binary tree
 * @node: first node
 * @new: second node
 * Return: pointer to root
 */
bst_t *swap_old(bst_t *node, bst_t *new)
{
	bst_t *temp = NULL;
	_Bool left_child = false;

	if (node->parent)
		left_child = node->parent->left == node;
	
	if (new->parent && new->parent != node)
		new->parent->left = NULL; /* ??? */
	

	new->parent = node->parent;
	/* if old node has a parent, set its child-relation to the new node */
	if (node->parent)
	{
		if (left_child)
			node->parent->left = new;
		else
			node->parent->right = new;
	}

	/* set left child of old node to left child of new node, if they are not equal */
	if (node->left != new)
	{
		new->left = node->left;
		node->left->parent = new;
	}
	/* set right child of old node to right child of new node, if they are not equal */
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
				printf("inserted %d as right child of %d\n", ht->n, tmp->n);
				ht->parent = tmp;
				tmp->right = ht;
				break;
			}
			else if (c == '0')
			{
				printf("inserted %d as left child of %d\n", ht->n, tmp->n);
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
	printf("AFTER INSERT TREE:\n");
	binary_tree_print(tmp);
	if (ht->n > ht->parent->n)
	{
		printf("=====================================\n");
		printf("time to swap %i, %i\n", ht->n, ht->parent->n);
		ret = swap(ht->parent, ht);
		printf("RET: %d\n", ret->n);
		if (ret)
			*root = ret;
		printf("PRINT: %d\n", (*root)->n);
		binary_tree_print(*root);
	}
	return (ht);
}
