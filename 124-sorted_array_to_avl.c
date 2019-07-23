#include "binary_trees.h"


avl_t *_sorted_array_to_avl(int *array, int start, int end)
{
	avl_t *new;
	int mid;

	if (start > end)
		return (NULL);
	mid = (start + end) / 2;
	new = calloc(1, sizeof(avl_t));
	if (!new)
		return (NULL);
	new->n = array[mid];
	new->parent = ;
	printf("new = %i\n", new->n);
	new->left = _sorted_array_to_avl(array, start, mid - 1);
	new->right = _sorted_array_to_avl(array, mid + 1, end);
	return (new);
}


/**
 * sorted_array_to_avl - builds an AVL tree from an array
 * @array: input array
 * @size: size of array
 * Return: pointer to the root node of the created AVL tree, or NULL on failure
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{

	if (!array)
		return (NULL);
	return(_sorted_array_to_avl(array, 0, size - 1));
}
