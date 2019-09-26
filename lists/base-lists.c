#include "base-lists.h"

static base_EmperorListNode_t* getNode(base_EmperorList_t*, int);
static base_EmperorListNode_t* getFromFront(base_EmperorList_t*, int);
static base_EmperorListNode_t* getFromBack(base_EmperorList_t*, int);

base_Any_t base_initEmperorList()
{
	base_EmperorList_t* lst = (base_EmperorList_t*)calloc(1, sizeof(base_EmperorList_t));

	if (lst == NULL)
	{
		fprintf(stderr, "Failed to allocate space for list\n");
		exit(EXIT_FAILURE);
	}

	return (base_Any_t){ .voidV = lst };
}

void base_destroyEmperorList(base_Any_t lst, void (*elementDestructor)(base_Any_t))
{
	base_EmperorList_t* lstV = (base_EmperorList_t*)lst.voidV;
	
	for (base_EmperorListNode_t* curr = (base_EmperorListNode_t*)lstV->first.voidV; curr != NULL; curr = (base_EmperorListNode_t*)curr->succ.voidV)
	{
		elementDestructor(curr->value);
		free(curr->prev.voidV);
	}

	if (lstV->length.intV > 1)
	{
		elementDestructor(lstV->last);
		free(lstV->last.voidV);
	}

	free(lstV);
}

bool base_isEmpty(base_Any_t lst)
{
	base_EmperorList_t* lstV = (base_EmperorList_t*)lst.voidV;
	return lst.voidV == NULL || lstV->length.intV == 0 || (lstV->first.voidV == NULL && lstV->last.voidV == NULL);
}

base_Any_t base_del(base_Any_t lst, int idx, void (*elementDestructor)(base_Any_t))
{
	// TODO
}

base_Any_t base_get(base_Any_t, int)
{
	// TODO
}
base_Any_t base_append(base_Any_t, base_Any_t)
{
	// TODO
}
base_Any_t base_prepend(base_Any_t, base_Any_t)
{
	// TODO
}
base_Any_t base_unite(base_Any_t, base_Any_t)
{
	// TODO
}

base_Any_t base_stringToCharList(char* str)
{
	return base_stringToCharListL(str, strlen(str));
}

base_Any_t base_stringToCharListL(char* str, size_t length)
{
	base_EmperorList_t* lst = (base_EmperorList_t*)base_initEmperorList().voidV;

	if (length > 0)
	{
		base_EmperorListNode_t* prev = NULL;
		base_EmperorListNode_t* curr = NULL;

		// TODO

	}

	return (base_Any_t){ .voidV = lst };
}

char* base_charListToString(base_Any_t lst)
{
	base_EmperorList_t* lstV = (base_EmperorList_t*)lst.voidV;
	int length = lstV->length.intV;

	char* str = (char*)malloc((length + 1) * sizeof(char));
	if (str == NULL)
	{
		printf(stderr, "Failed to allocate space for string during copy\n");
		exit(EXIT_FAILURE);
	}

	base_EmperorListNode_t* curr = (base_EmperorListNode_t*)lstV->first.voidV;

	for (int i = 0; i < length && curr != NULL; i++)
	{
		str[i] = curr->value.charV;
		curr = (base_EmperorListNode_t*)curr->succ.voidV;
	}

	str[length] = '\0';

	return str;
}

// base_Any_t base_initEmperorList(const base_ReferenceContext_t* ctx)
// {
// 	base_EmperorList_t* lst = (base_EmperorList_t*)calloc(1, sizeof(base_EmperorList_t));
// 	if (lst == NULL)
// 	{
// 		fprintf(stderr, "Could not allocate space for list");
// 		exit(EXIT_FAILURE);
// 	}

// 	return base_reference(lst, ctx);
// }

// void base_destroyEmperorList(base_Any_t UNUSED(lst), void (*elementDestructor)(base_Any_t))
// {
// 	fprintf(stderr, "Failed to free memory used by Emperor list (unimplemented)\n");
// 	exit(EXIT_FAILURE);
// 	elementDestructor = elementDestructor;

// 	// base_EmperorListNode_t* node = lst.referenceV->first;
// 	// base_EmperorListNode_t* next;

// 	// while (node != NULL)
// 	// {
// 	// 	next = node->succ;
// 	// 	printf("Freeing node value\n");
// 	// 	elementDestructor(node->value);
// 	// 	printf("Freeing node\n");
// 	// 	free(node);
// 	// 	node = next;
// 	// }

// 	// free(lst.referenceV);
// }

// bool base_isEmpty(base_Any_t lst)
// {
// 	base_EmperorList_t* lstVal = base_dereference(lst.referenceV);
// 	return lstVal == NULL || lstVal->length.intV == 0
// 	    || (lstVal->first.referenceV == NULL && lstVal->last.referenceV == NULL);
// }

// base_Any_t base_del(base_Any_t lst, int idx)
// {
// 	base_EmperorList_t* lstVal   = base_dereference(lst.referenceV);
// 	base_EmperorListNode_t* node = getNode(lstVal, idx);
// 	lstVal->length.intV--;

// 	if (base_dereference(node->prev.referenceV) == NULL)
// 	{
// 		// lstVal->first     = node->succ;
// 		base_authorReferenceChange(lstVal->first.referenceV, ctx, base_dereference(node->succ.referenceV));
// 		// node->succ->prev         = NULL;
// 		base_authorReferenceChange(
// 		    ((base_EmperorListNode_t*)base_dereference(node->succ.referenceV))->prev.referenceV, ctx, NULL);
// 	}
// 	else
// 	{
// 		// node->prev->succ = node->succ
// 		base_authorReferenceChange(((base_EmperorListNode_t*)base_dereference(node->prev.referenceV))->succ.referenceV,
// 		    ctx, base_dereference(node->succ.referenceV));
// 	}

// 	if (base_dereference(node->succ.referenceV) == NULL)
// 	{
// 		// lstVal->last     = node->prev;
// 		base_authorReferenceChange(lstVal->last.referenceV, ctx, base_dereference(node->prev.referenceV));
// 		// node->prev->succ = NULL;
// 		base_authorReferenceChange(
// 		    ((base_EmperorListNode_t*)base_dereference(node->prev.referenceV))->succ.referenceV, ctx, NULL);
// 	}
// 	else
// 	{
// 		// node->succ->prev = node->prev;
// 		base_authorReferenceChange(((base_EmperorListNode_t*)base_dereference(node->succ.referenceV))->prev.referenceV,
// 		    ctx, base_dereference(node->prev.referenceV));
// 		// base_authorReferenceChange(
// 		//     ((base_EmperorListNode_t*)base_dereference(node->succ.referenceV))->prev.referenceV,
// 		//     node->prev.referenceV) .referenceV;
// 	}

// 	return lst;
// }

// base_Any_t base_get(base_Any_t lst, int idx)
// {
// 	base_EmperorList_t* lstVal = base_dereference(lst.referenceV);
// 	base_EmperorListNode_t* n  = getNode(lstVal, idx);
// 	if (n == NULL)
// 	{
// 		fprintf(stderr, "List search returned NULL\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	return n->value;
// }

// // Precondition: lst != NULL
// static base_EmperorListNode_t* getNode(base_EmperorList_t* lst, int idx)
// {
// 	if (idx > lst->length.intV)
// 	{
// 		fprintf(stderr, "Could not access item %d from a list of length %d\n", idx, lst->length.intV);
// 		exit(EXIT_FAILURE);
// 	}

// 	// ~2x speed boost in general, but this is still O(n) ¯\_(ツ)_/¯
// 	if (idx <= lst->length.intV / 2)
// 		return getFromFront(lst, idx);
// 	else
// 		return getFromBack(lst, idx);
// }

// // Precondition: lst != NULL && idx <= lst->length
// static base_EmperorListNode_t* getFromFront(base_EmperorList_t* lst, int idx)
// {
// 	base_EmperorListNode_t* curr = (base_EmperorListNode_t*)base_dereference(lst->first.referenceV);
// 	while (idx > 0)
// 	{
// 		curr = (base_EmperorListNode_t*)base_dereference(curr->succ.referenceV);
// 		idx--;
// 	}
// 	return curr;
// }

// // Precondition: lst != NULL && lst->length/2 <= idx <= lst->length
// static base_EmperorListNode_t* getFromBack(base_EmperorList_t* lst, int idx)
// {
// 	idx                          = lst->length.intV - idx;
// 	base_EmperorListNode_t* curr = (base_EmperorListNode_t*)base_dereference(lst->last.referenceV);
// 	while (idx > 0)
// 	{
// 		curr = (base_EmperorListNode_t*)base_dereference(curr->prev.referenceV);
// 		idx--;
// 	}
// 	return curr;
// }

// // Precondition: lst != NULL
// base_Any_t base_append(base_Any_t lst, base_Any_t value)
// {
// 	printf("Running base_append(..)\n");
// 	base_EmperorList_t* lstVal      = base_dereference(lst.referenceV);
// 	base_ReferenceContext_t* newCtx = base_makeNewContext(lst.referenceV->ctx);
// 	base_EmperorList_t* toReturn    = (base_EmperorList_t*)malloc(sizeof(base_EmperorList_t));
// 	if (toReturn == NULL)
// 	{
// 		fprintf(stderr, "Failed to create list to return\n");
// 		exit(EXIT_FAILURE);
// 	}

// 	base_EmperorListNode_t* node = (base_EmperorListNode_t*)malloc(sizeof(base_EmperorListNode_t));
// 	printf("A");
// 	if (node == NULL)
// 	{
// 		fprintf(stderr, "Failed to allocate space when creating list node\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	node->value = value;
// 	node->succ  = base_reference(NULL, newCtx);
// 	node->prev  = base_reference(NULL, newCtx);
// 	printf("a");

// 	if (base_isEmpty(lst))
// 	{
// 		printf("a");
// 		toReturn->first = base_reference(node, newCtx);
// 		toReturn->last  = base_reference(node, newCtx);
// 	}
// 	else
// 	{
// 		// General case
// 		printf("a");
// 		node->succ = lstVal->first;
// 		// lst->last->succ = node;
// 		base_authorReferenceChange(
// 		    ((base_EmperorListNode_t*)base_dereference(lstVal->last.referenceV))->succ.referenceV, newCtx, node);
// 		// lst->last       = node;
// 		base_authorReferenceChange(lstVal->last.referenceV, newCtx, node);
// 	}
// 	printf("X\n");

// 	toReturn->length.intV = lstVal->length.intV + 1;

// 	return base_reference(toReturn, newCtx);
// }

// // Precondition: lst != NULL
// base_Any_t base_prepend(base_Any_t lst, base_Any_t value)
// {
// 	printf("Running base_prepend(..)\n");
// 	base_EmperorList_t* lstVal      = base_dereference(lst.referenceV);
// 	base_ReferenceContext_t* newCtx = base_makeNewContext(lst.referenceV->ctx);
// 	base_EmperorList_t* toReturn    = (base_EmperorList_t*)malloc(sizeof(base_EmperorList_t));
// 	if (toReturn == NULL)
// 	{
// 		fprintf(stderr, "Failed to create list to return\n");
// 		exit(EXIT_FAILURE);
// 	}

// 	base_EmperorListNode_t* node = (base_EmperorListNode_t*)malloc(sizeof(base_EmperorListNode_t));
// 	printf("A");
// 	if (node == NULL)
// 	{
// 		fprintf(stderr, "Failed to allocate space when creating list node\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	node->value = value;
// 	node->succ  = base_reference(NULL, newCtx);
// 	node->prev  = base_reference(NULL, newCtx);
// 	printf("a");

// 	if (base_isEmpty(lst))
// 	{
// 		printf("a");
// 		toReturn->first = base_reference(node, newCtx);
// 		toReturn->last  = base_reference(node, newCtx);
// 	}
// 	else
// 	{
// 		// General case
// 		printf("a");
// 		node->succ = lstVal->first;
// 		// lst->first->prev = node;
// 		base_authorReferenceChange(
// 		    ((base_EmperorListNode_t*)base_dereference(lstVal->first.referenceV))->prev.referenceV, newCtx, node);
// 		// lst->first       = node;
// 		base_authorReferenceChange(lstVal->first.referenceV, newCtx, node);
// 	}
// 	printf("X\n");

// 	toReturn->length.intV = lstVal->length.intV + 1;

// 	return base_reference(toReturn, newCtx);
// 	// base_EmperorListNode_t* node = (base_EmperorListNode_t*)malloc(sizeof(base_EmperorListNode_t));
// 	// if (node == NULL)
// 	// {
// 	// 	fprintf(stderr, "Failed to allocate space when creating list node\n");
// 	// 	exit(EXIT_FAILURE);
// 	// }
// 	// node->value = value;
// 	// node->succ  = NULL;
// 	// node->prev  = NULL;

// 	// if (lst->first == NULL)
// 	// {
// 	// 	lst->first  = node;
// 	// 	lst->last   = node;
// 	// 	lst->length = 1;
// 	// }
// 	// else
// 	// {
// 	// 	node->succ       = lst->first;
// 	// 	lst->first->prev = node;
// 	// 	lst->first       = node;
// 	// 	lst->length++;
// 	// }

// 	// return lst;
// 	// return NULL;
// }

// base_Any_t base_unite(base_Any_t lst1, base_Any_t lst2, const base_ReferenceContext_t* ctx)
// {
// 	base_EmperorList_t* toReturn = (base_EmperorList_t*)malloc(sizeof(base_EmperorList_t));
// 	if (toReturn == NULL)
// 	{
// 		fprintf(stderr, "Failed to allocate space while creating new list\n");
// 		exit(EXIT_FAILURE);
// 	}

// 	base_EmperorList_t* lst2Val = (base_EmperorList_t*)base_dereference(lst2.referenceV);
// 	base_EmperorList_t* lst1Val = (base_EmperorList_t*)base_dereference(lst1.referenceV);

// 	// Handle cases where list is empty
// 	if (lst1Val->length.intV == 0)
// 	{
// 		toReturn->first  = lst2Val->first;
// 		toReturn->last   = lst2Val->last;
// 		toReturn->length = lst2Val->length;
// 		return base_reference(toReturn, ctx);
// 	}
// 	else if (lst2Val->length.intV == 0)
// 	{
// 		toReturn->first  = lst1Val->first;
// 		toReturn->last   = lst1Val->last;
// 		toReturn->length = lst1Val->length;
// 		return base_reference(toReturn, ctx);
// 	}

// 	// Set end-points and length
// 	toReturn->first       = lst1Val->first;
// 	toReturn->last        = lst2Val->last;
// 	toReturn->length.intV = lst1Val->length.intV + lst2Val->length.intV;

// 	// Handle references where the lists are concatenated
// 	// lst1->last->succ  = lst2->first;
// 	base_authorReferenceChange(((base_EmperorListNode_t*)base_dereference(lst1Val->last.referenceV))->succ.referenceV,
// 	    ctx, base_dereference(lst2Val->first.referenceV));
// 	// lst2->first->prev = lst1->last;
// 	base_authorReferenceChange(((base_EmperorListNode_t*)base_dereference(lst2Val->first.referenceV))->prev.referenceV,
// 	    ctx, base_dereference(lst1Val->last.referenceV));

// 	return base_reference(toReturn, ctx);
// }

// base_Any_t base_stringToCharList(char* str, const base_ReferenceContext_t* ctx)
// {
// 	size_t length = strlen(str);

// 	base_EmperorList_t* lst = (base_EmperorList_t*)malloc(sizeof(base_EmperorList_t));
// 	if (lst == NULL)
// 	{
// 		fprintf(stderr, "Could not allocate memory for list\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	base_Any_t toReturn = base_reference(lst, ctx);

// 	for (size_t i = 0; i < length; i++)
// 	{
// 		base_Any_t x = (base_Any_t){ .charV = str[i] };
// 		base_append(toReturn, x);
// 	}

// 	return toReturn;
// }

// char* base_charListToString(base_Any_t lst)
// {
// 	base_EmperorList_t* lstVal = (base_EmperorList_t*)base_dereference(lst.referenceV);
// 	int len                    = lstVal->length.intV;
// 	char* buf                  = (char*)malloc(len * sizeof(char) + 1);

// 	base_EmperorListNode_t* curr = (base_EmperorListNode_t*)base_dereference(lstVal->first.referenceV);
// 	for (int i = 0; i < len && curr != NULL; i++, curr = base_dereference(curr->succ.referenceV))
// 	{
// 		buf[i] = curr->value.charV;
// 	}

// 	buf[len] = '\0';
// 	return buf;
// }
