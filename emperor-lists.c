#include "emperor-lists.h"
#include <stdio.h>

static emperorListNode_t* getFromFront(emperorList_t*, int);
static emperorListNode_t* getFromBack(emperorList_t*, int);
static emperorListNode_t* getNode(emperorList_t*, int);

// destroyEmperorList get delete

emperorList_t* initEmperorList(void) { return calloc(1, sizeof(emperorList_t*)); }

void destroyEmperorList(emperorList_t* lst, void (*elementDestructor)(void*))
{
	emperorListNode_t* node = lst->first;
	emperorListNode_t* next;

	while (node != NULL)
	{
		next = node->succ;
		elementDestructor(node->value);
		free(node);
		node = next;
	}

	free(lst);
}

int isEmpty(emperorList_t* lst)
{
	return lst == NULL || lst->length == 0 || (lst->first == NULL && lst->first == NULL);
}

void* get(emperorList_t* lst, int idx) { return getNode(lst, idx)->value; }

emperorList_t* del(emperorList_t* lst, int idx)
{
	emperorListNode_t* node = getNode(lst, idx);

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

// Precondition: lst != NULL
static emperorListNode_t* getNode(emperorList_t* lst, int idx)
{
	if (idx > lst->length)
	{
		fprintf(stderr, "Could not access item %d from a list of length %d", idx, lst->length);
		exit(-1);
	}

	// ~2x speed boost in general, but this is still O(n) ¯\_(ツ)_/¯
	if (idx <= lst->length >> 1)
		return getFromFront(lst, idx)->value;
	else
		return getFromBack(lst, idx)->value;
}

// Precondition: lst != NULL && idx <= lst->length
static emperorListNode_t* getFromFront(emperorList_t* lst, int idx)
{
	emperorListNode_t* curr = lst->first;
	while (idx > 0)
	{
		curr = curr->succ;
		idx--;
	}
	return curr;
}

// Precondition: lst != NULL && idx <= lst->length
static emperorListNode_t* getFromBack(emperorList_t* lst, int idx)
{
	emperorListNode_t* curr = lst->last;
	while (idx > 0)
	{
		curr = curr->prev;
		idx--;
	}
	return curr;
}

// Precondition: lst != NULL
emperorList_t* append(emperorList_t* lst, void* value)
{
	emperorListNode_t* node = (emperorListNode_t*)malloc(sizeof(emperorListNode_t));
	if (node == NULL)
	{
		fprintf(stderr, "Failed to allocate space when creating list node\n");
		exit(-1);
	}
	node->value = value;
	node->succ  = NULL;
	node->prev  = NULL;

	if (lst->last == NULL)
	{
		// The list is empty
		lst->last   = node;
		lst->first  = node;
		lst->length = 1;
	}
	else
	{
		// General case
		lst->last->succ = node;
		node->prev      = lst->last;
		lst->last       = node;
		lst->length++;
	}

	return lst;
}

// Precondition: lst != NULL
emperorList_t* prepend(emperorList_t* lst, void* value)
{
	emperorListNode_t* node = (emperorListNode_t*)malloc(sizeof(emperorListNode_t));
	if (node == NULL)
	{
		fprintf(stderr, "Failed to allocate space when creating list node\n");
		exit(-1);
	}
	node->value = value;
	node->prev  = NULL;
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

emperorList_t* unite(emperorList_t* lst1, emperorList_t* lst2)
{
	// Handle cases where list is empty
	if (isEmpty(lst1))
		return lst1;
	else if (isEmpty(lst2))
		return lst1;

	lst1->last->succ  = lst2->first;
	lst2->first->prev = lst1->last;
	lst1->length += lst2->length;

	return lst1;
}
