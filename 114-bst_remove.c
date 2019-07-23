#include "binary_trees.h"

/**
 * bst_search - searches for a value in a Binary Search Tree
 * @tree: pointer to root of tree
 * @value: input value
 * Return: pointer to the node containing a value equals to value
 */
bst_t *bst_search(const bst_t *tree, int value)
{
    if (!tree)
        return (NULL);
    while (tree)
    {   
        if (value == tree->n)
            return ((bst_t *)tree);
        tree = value < tree->n ? tree->left
                               : tree->right;
    }   
    return ((bst_t *)tree);
}


bst_t *swap(bst_t *node, bst_t *new)
{
	bst_t *temp = NULL;
	_Bool left_child = false;

	printf("SWAP: %d with %d\n", node->n, new ? new->n : -1);
	if (node->parent)
		left_child = node->parent->left == node;

	printf("BEOFRE !NEW\n");
	if (!new)
	{
		if (!node->parent)
		{
			free(node);
			return (NULL);
		}
		if (left_child)
			node->parent->left = NULL;
		else
			node->parent->right = NULL;
		temp = node->parent;
		while (temp->parent)
			temp = temp->parent;
		free(node);
		return (temp);
	}
	printf("POST !NEW\n");
		
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
	printf("POST IF PARENT\n");
	
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

	printf("FOOO\n");
	temp = new;
	printf("PRE WHILE\n");
	while (temp->parent)
		temp = temp->parent;
	printf("POST WHILE\n");
	free(node);
	return (temp);
}

/**
 * bst_remove - removes a node from a Binary Search Tree
 * @root: pointer to root of tree
 * @value: input value
 * Return: pointer to the new root node of the tree after removing the
 * desired value
 */
bst_t *bst_remove(bst_t *root, int value)
{
	bst_t *node, *temp;

	if (!root)
		return (NULL);
	node = bst_search(root, value);
	if (!node)
		return (NULL);
	if (!node->right)
		return swap(node, node->left);
	temp = node->right;
	while (temp->left)
		temp = temp->left;
	return swap(node, temp);
}
