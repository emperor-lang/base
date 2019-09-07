/**
 * @file base-lists.c
 * @author Ed Jones (ed@kcza.net)
 * @brief Defines functions to create, handle and destroy lists
 * @version 0.1
 * @date 2019-09-06
 *
 * @copyright Copyright (c) 2019
 *
 */
#include "base-lists.h"

base_EmperorList_t* base_initEmperorList(void)
{
	base_EmperorList_t* lst = (base_EmperorList_t*)calloc(1, sizeof(base_EmperorList_t*));
	if (lst == NULL)
	{
		fprintf(stderr, "Could not allocate space for list");
		exit(EXIT_FAILURE);
	}

	return lst;
}

void base_destroyEmperorList(base_EmperorList_t* lst, void (*elementDestructor)(base_Any_t))
{
	base_EmperorListNode_t* node = lst->first;
	base_EmperorListNode_t* next;

	while (node != NULL)
	{
		next = node->succ;
		printf("Freeing node value\n");
		elementDestructor(node->value);
		printf("Freeing node\n");
		free(node);
		node = next;
	}

	free(lst);
}

bool base_isEmpty(base_EmperorList_t* lst)
{
	return lst == NULL || lst->length == 0 || (lst->first == NULL && lst->first == NULL);
}

base_EmperorList_t* base_del(base_EmperorList_t* lst, int idx)
{
	base_EmperorListNode_t* node = getNode(lst, idx);

	if (node->prev == NULL)
	{
		lst->first       = node->succ;
		node->succ->prev = NULL;
	}
	else
	{
		node->prev->succ = node->succ;
	}

	if (node->succ == NULL)
	{
		lst->last        = node->prev;
		node->prev->succ = NULL;
	}
	else
	{
		node->succ->prev = node->prev;
	}

	lst->length--;

	return lst;
}

base_Any_t base_get(base_EmperorList_t* lst, int idx)
{
	base_EmperorListNode_t* n = getNode(lst, idx);
	if (n == NULL)
	{
		fprintf(stderr, "List search returned NULL\n");
		exit(EXIT_FAILURE);
	}
	return n->value;
}

// Precondition: lst != NULL
base_EmperorListNode_t* getNode(base_EmperorList_t* lst, int idx)
{
	if (idx > lst->length)
	{
		fprintf(stderr, "Could not access item %d from a list of length %d\n", idx, lst->length);
		exit(EXIT_FAILURE);
	}

	// ~2x speed boost in general, but this is still O(n) ¯\_(ツ)_/¯
	if (idx <= lst->length / 2)
		return getFromFront(lst, idx);
	else
		return getFromBack(lst, idx);
}

// Precondition: lst != NULL && idx <= lst->length
base_EmperorListNode_t* getFromFront(base_EmperorList_t* lst, int idx)
{
	base_EmperorListNode_t* curr = lst->first;
	while (idx > 0)
	{
		curr = curr->succ;
		idx--;
	}
	return curr;
}

// Precondition: lst != NULL && lst->length/2 <= idx <= lst->length
base_EmperorListNode_t* getFromBack(base_EmperorList_t* lst, int idx)
{
	idx                          = lst->length - idx;
	base_EmperorListNode_t* curr = lst->last;
	while (idx > 0)
	{
		curr = curr->prev;
		idx--;
	}
	return curr;
}

// Precondition: lst != NULL
base_EmperorList_t* base_append(base_EmperorList_t* lst, base_Any_t value)
{
	printf("Running base_append(..)\n");
	base_EmperorListNode_t* node = (base_EmperorListNode_t*)malloc(sizeof(base_EmperorListNode_t));
	printf("A");
	if (node == NULL)
	{
		fprintf(stderr, "Failed to allocate space when creating list node\n");
		exit(EXIT_FAILURE);
	}
	node->value = value;
	node->succ  = NULL;
	node->prev  = NULL;
	printf("a");

	if (lst->last == NULL)
	{
		// The list is empty
		printf("a");
		lst->last   = node;
		lst->first  = node;
		lst->length = 1;
	}
	else
	{
		// General case
		printf("a");
		lst->last->succ = node;
		node->prev      = lst->last;
		lst->last       = node;
		lst->length++;
	}
	printf("X\n");

	return lst;
}

// Precondition: lst != NULL
base_EmperorList_t* base_prepend(base_EmperorList_t* lst, base_Any_t value)
{
	base_EmperorListNode_t* node = (base_EmperorListNode_t*)malloc(sizeof(base_EmperorListNode_t));
	if (node == NULL)
	{
		fprintf(stderr, "Failed to allocate space when creating list node\n");
		exit(EXIT_FAILURE);
	}
	node->value = value;
	node->succ  = NULL;
	node->prev  = NULL;

	if (lst->first == NULL)
	{
		lst->first  = node;
		lst->last   = node;
		lst->length = 1;
	}
	else
	{
		node->succ       = lst->first;
		lst->first->prev = node;
		lst->first       = node;
		lst->length++;
	}

	return lst;
}

base_EmperorList_t* base_unite(base_EmperorList_t* lst1, base_EmperorList_t* lst2)
{
	// Handle cases where list is empty
	if (base_isEmpty(lst1))
		return lst1;
	else if (base_isEmpty(lst2))
		return lst1;

	lst1->last->succ  = lst2->first;
	lst2->first->prev = lst1->last;
	lst1->length += lst2->length;
	lst1->last = lst2->last;

	return lst1;
}

base_EmperorList_t* base_stringToCharList(char* str)
{
	size_t length = strlen(str);

	base_EmperorList_t* toReturn = (base_EmperorList_t*)malloc(sizeof(base_EmperorList_t));
	if (toReturn == NULL)
	{
		fprintf(stderr, "Could not allocate memory for list\n");
		exit(EXIT_FAILURE);
	}

	for (size_t i = 0; i < length; i++)
	{
		base_Any_t x = (base_Any_t){ .charV = str[i] };
		base_append(toReturn, x);
	}

	return toReturn;
}

char* base_charListToString(base_EmperorList_t* lst)
{
	int len   = lst->length;
	char* buf = (char*)malloc(len * sizeof(char) + 1);

	base_EmperorListNode_t* curr = lst->first;
	for (int i = 0; i < len && curr != NULL; i++, curr = curr->succ)
	{
		buf[i] = curr->value.charV;
	}

	buf[len] = '\0';
	return buf;
}
