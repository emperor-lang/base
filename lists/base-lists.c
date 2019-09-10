#include "base-lists.h"

static base_EmperorListNode_t* getNode(base_EmperorList_t*, int);
static base_EmperorListNode_t* getFromFront(base_EmperorList_t*, int);
static base_EmperorListNode_t* getFromBack(base_EmperorList_t*, int);

base_Any_t base_initEmperorList(void)
{
	base_EmperorList_t* lst = (base_EmperorList_t*)calloc(1, sizeof(base_EmperorList_t));
	if (lst == NULL)
	{
		fprintf(stderr, "Could not allocate space for list");
		exit(EXIT_FAILURE);
	}

	return base_reference(lst);
}

void base_destroyEmperorList(base_Any_t UNUSED(lst), void (*elementDestructor)(base_Any_t))
{
	fprintf(stderr, "Failed to free memory used by Emperor list (unimplemented)\n");
	exit(EXIT_FAILURE);
	elementDestructor = elementDestructor;

	// base_EmperorListNode_t* node = lst.referenceV->first;
	// base_EmperorListNode_t* next;

	// while (node != NULL)
	// {
	// 	next = node->succ;
	// 	printf("Freeing node value\n");
	// 	elementDestructor(node->value);
	// 	printf("Freeing node\n");
	// 	free(node);
	// 	node = next;
	// }

	// free(lst.referenceV);
}

bool base_isEmpty(base_Any_t lst)
{
	base_EmperorList_t* lstVal = base_dereference(lst.referenceV);
	return lstVal == NULL || lstVal->length.intV == 0
	    || (lstVal->first.referenceV == NULL && lstVal->last.referenceV == NULL);
}

base_Any_t base_del(base_Any_t lst, int idx)
{
	base_EmperorList_t* lstVal   = base_dereference(lst.referenceV);
	base_EmperorListNode_t* node = getNode(lstVal, idx);
	lstVal->length.intV--;

	if (base_dereference(node->prev.referenceV) == NULL)
	{
		// lstVal->first     = node->succ;
		base_authorReferenceChange(
		    lstVal->first.referenceV, lst.referenceV->ctx, base_dereference(node->succ.referenceV));
		// node->succ->prev         = NULL;
		base_authorReferenceChange(((base_EmperorListNode_t*)base_dereference(node->succ.referenceV))->prev.referenceV,
		    lst.referenceV->ctx, NULL);
	}
	else
	{
		// node->prev->succ = node->succ
		base_authorReferenceChange(((base_EmperorListNode_t*)base_dereference(node->prev.referenceV))->succ.referenceV,
		    lst.referenceV->ctx, base_dereference(node->succ.referenceV));
	}

	if (base_dereference(node->succ.referenceV) == NULL)
	{
		// lstVal->last     = node->prev;
		base_authorReferenceChange(
		    lstVal->last.referenceV, lst.referenceV->ctx, base_dereference(node->prev.referenceV));
		// node->prev->succ = NULL;
		base_authorReferenceChange(((base_EmperorListNode_t*)base_dereference(node->prev.referenceV))->succ.referenceV,
		    lst.referenceV->ctx, NULL);
	}
	else
	{
		// node->succ->prev = node->prev;
		base_authorReferenceChange(((base_EmperorListNode_t*)base_dereference(node->succ.referenceV))->prev.referenceV,
		    lst.referenceV->ctx, base_dereference(node->prev.referenceV));
		// base_authorReferenceChange(
		//     ((base_EmperorListNode_t*)base_dereference(node->succ.referenceV))->prev.referenceV,
		//     node->prev.referenceV) .referenceV;
	}

	return lst;
}

base_Any_t base_get(base_Any_t lst, int idx)
{
	base_EmperorList_t* lstVal = base_dereference(lst.referenceV);
	base_EmperorListNode_t* n  = getNode(lstVal, idx);
	if (n == NULL)
	{
		fprintf(stderr, "List search returned NULL\n");
		exit(EXIT_FAILURE);
	}
	return n->value;
}

// Precondition: lst != NULL
static base_EmperorListNode_t* getNode(base_EmperorList_t* lst, int idx)
{
	if (idx > lst->length.intV)
	{
		fprintf(stderr, "Could not access item %d from a list of length %d\n", idx, lst->length.intV);
		exit(EXIT_FAILURE);
	}

	// ~2x speed boost in general, but this is still O(n) ¯\_(ツ)_/¯
	if (idx <= lst->length.intV / 2)
		return getFromFront(lst, idx);
	else
		return getFromBack(lst, idx);
}

// Precondition: lst != NULL && idx <= lst->length
static base_EmperorListNode_t* getFromFront(base_EmperorList_t* lst, int idx)
{
	base_EmperorListNode_t* curr = (base_EmperorListNode_t*)base_dereference(lst->first.referenceV);
	while (idx > 0)
	{
		curr = (base_EmperorListNode_t*)base_dereference(curr->succ.referenceV);
		idx--;
	}
	return curr;
}

// Precondition: lst != NULL && lst->length/2 <= idx <= lst->length
static base_EmperorListNode_t* getFromBack(base_EmperorList_t* lst, int idx)
{
	idx                          = lst->length.intV - idx;
	base_EmperorListNode_t* curr = (base_EmperorListNode_t*)base_dereference(lst->last.referenceV);
	while (idx > 0)
	{
		curr = (base_EmperorListNode_t*)base_dereference(curr->prev.referenceV);
		idx--;
	}
	return curr;
}

// Precondition: lst != NULL
// TODO: Author changes here
base_Any_t base_append(base_Any_t lst, base_Any_t value)
{
	base_EmperorList_t* lstVal = base_dereference(lst.referenceV);
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

	if (lstVal->last == NULL)
	{
		// The list is empty
		printf("a");
		lstVal->last   = node;
		lstVal->first  = node;
		lstVal->length = 1;
	}
	else
	{
		// General case
		printf("a");
		lstVal->last->succ = node;
		node->prev         = lstVal->last;
		lstVal->last       = node;
		lstVal->length++;
	}
	printf("X\n");

	return lst;
}

// Precondition: lst != NULL
base_Any_t base_prepend(base_Any_t lst, base_Any_t value)
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

base_Any_t base_unite(base_Any_t lst1, base_Any_t lst2)
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

base_Any_t base_stringToCharList(char* str)
{
	size_t length = strlen(str);

	base_EmperorList_t* lst = (base_EmperorList_t*)malloc(sizeof(base_EmperorList_t));
	if (lst == NULL)
	{
		fprintf(stderr, "Could not allocate memory for list\n");
		exit(EXIT_FAILURE);
	}
	base_Any_t toReturn = base_reference(lst);

	for (size_t i = 0; i < length; i++)
	{
		base_Any_t x = (base_Any_t){ .charV = str[i] };
		base_append(toReturn, x);
	}

	return toReturn;
}

char* base_charListToString(base_Any_t lst)
{
	base_EmperorList_t* lstVal = (base_EmperorList_t*)base_dereference(lst.referenceV);
	int len                    = lstVal->length;
	char* buf                  = (char*)malloc(len * sizeof(char) + 1);

	base_EmperorListNode_t* curr = (base_EmperorListNode_t*)base_dereference(lstVal->first.referenceV);
	for (int i = 0; i < len && curr != NULL; i++, curr = base_dereference(curr->succ.referenceV))
	{
		buf[i] = curr->value.charV;
	}

	buf[len] = '\0';
	return buf;
}
