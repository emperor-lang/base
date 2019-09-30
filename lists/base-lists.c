#include "base-lists.h"

static base_EmperorListNode_t* getNode(base_EmperorList_t*, int);
static base_EmperorListNode_t* getNodeFromFront(base_EmperorList_t*, int);
static base_EmperorListNode_t* getNodeFromBack(base_EmperorList_t*, int);

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

	for (base_EmperorListNode_t* curr = lstV->first.voidV; curr != NULL; curr = curr->succ.voidV)
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

base_Any_t base_shallowCopyList(base_Any_t lst)
{
	if (lst.voidV == NULL)
	{
		fprintf(stderr, "Attempted to shallow copy null list\n");
		exit(EXIT_FAILURE);
	}

	base_EmperorList_t* lstV     = lst.voidV;
	base_EmperorList_t* toReturn = base_initEmperorList().voidV;

	toReturn->length = lstV->length;

	if (!base_isEmpty(lst))
	{
		base_EmperorListNode_t* curr    = lstV->first.voidV;
		base_EmperorListNode_t* newCurr = (base_EmperorListNode_t*)malloc(sizeof(base_EmperorListNode_t));
		if (newCurr == NULL)
		{
			fprintf(stderr, "Failed to allocate memory when shallow copying list\n");
			exit(EXIT_FAILURE);
		}
		memcpy(newCurr, curr, sizeof(base_EmperorListNode_t));

		toReturn->first.voidV = newCurr;

		while (curr != NULL)
		{
			// Allocate space for new node
			newCurr = (base_EmperorListNode_t*)malloc(sizeof(base_EmperorListNode_t));
			if (newCurr == NULL)
			{
				fprintf(stderr, "Failed to allocate memory when shallow copying list\n");
				exit(EXIT_FAILURE);
			}

			// Copy node value
			memcpy(newCurr, curr, sizeof(base_EmperorListNode_t));

			curr = curr->succ.voidV;
		}

		toReturn->last.voidV = newCurr;
	}

	return (base_Any_t){ .voidV = toReturn };
}

// Precondition: lst != NULL
static base_EmperorListNode_t* getNode(base_EmperorList_t* lst, int idx)
{
	if (idx > lst->length.intV || 0 > idx)
	{
		fprintf(stderr, "Could not access item %d from a list of length %d\n", idx, lst->length.intV);
		exit(EXIT_FAILURE);
	}

	// ~2x speed boost in general, but this is still O(n) ¯\_(ツ)_/¯
	if (idx <= lst->length.intV / 2)
		return getNodeFromFront(lst, idx);
	else
		return getNodeFromBack(lst, idx);
}

// Precondition: lst != NULL && idx <= lst->length
static base_EmperorListNode_t* getNodeFromFront(base_EmperorList_t* lst, int idx)
{
	base_EmperorListNode_t* curr = lst->first.voidV;
	while (idx > 0)
	{
		curr = curr->succ.voidV;
		idx--;
	}
	return curr;
}

// Precondition: lst != NULL && lst->length/2 <= idx <= lst->length
static base_EmperorListNode_t* getNodeFromBack(base_EmperorList_t* lst, int idx)
{
	idx                          = lst->length.intV - idx;
	base_EmperorListNode_t* curr = lst->last.voidV;
	while (idx > 0)
	{
		curr = curr->prev.voidV;
		idx--;
	}
	return curr;
}

bool base_isEmpty(base_Any_t lst)
{
	base_EmperorList_t* lstV = lst.voidV;
	return lst.voidV == NULL || lstV->length.intV == 0 || (lstV->first.voidV == NULL && lstV->last.voidV == NULL);
}

base_Any_t base_del(base_Any_t lst, base_Any_t idx, void (*elementDestructor)(base_Any_t))
{
	base_EmperorList_t* lstV = lst.voidV;
	if (base_isEmpty(lst))
	{
		fprintf(stderr, "Failed to get element from empty list\n");
		exit(EXIT_FAILURE);
	}
	else if (idx.intV < 0 || lstV->length.intV <= idx.intV)
	{
		fprintf(stderr, "Failed to get element %d from list of length %d\n", idx.intV, lstV->length.intV);
		exit(EXIT_FAILURE);
	}

	base_EmperorListNode_t* nodeToDelete = getNode(lstV, idx.intV);

	// Re-route pointers
	((base_EmperorListNode_t*)(nodeToDelete->prev.voidV))->succ
	    = ((base_EmperorListNode_t*)(nodeToDelete->succ.voidV))->prev;
	((base_EmperorListNode_t*)(nodeToDelete->succ.voidV))->prev
	    = ((base_EmperorListNode_t*)(nodeToDelete->prev.voidV))->succ;

	elementDestructor(nodeToDelete->value);
	free(nodeToDelete);

	lstV->length.intV--;

	return lst;
}

base_Any_t base_get(base_Any_t lst, base_Any_t idx) { return getNode(lst.voidV, idx.intV)->value; }

base_Any_t base_append(base_Any_t lst, base_Any_t value)
{
	base_EmperorList_t* lstV        = lst.voidV;
	base_EmperorListNode_t* newNode = (base_EmperorListNode_t*)malloc(sizeof(base_EmperorListNode_t));
	if (newNode == NULL)
	{
		fprintf(stderr, "Failed to allocate memory while creating new list node\n");
		exit(EXIT_FAILURE);
	}

	newNode->value = value;

	// Arrange pointers
	newNode->succ.voidV = NULL;
	newNode->prev       = lstV->last;
	if (base_isEmpty(lst))
	{
		lstV->first.voidV = newNode;
	}
	if (newNode->prev.voidV != NULL)
	{
		((base_EmperorListNode_t*)(newNode->prev.voidV))->succ.voidV = newNode;
	}
	lstV->last.voidV = newNode;

	lstV->length.intV++;

	return lst;
}

base_Any_t base_prepend(base_Any_t lst, base_Any_t value)
{
	// TODO: Match the method above, this one seems to have a tonne of lost memory

	base_EmperorList_t* lstV        = lst.voidV;
	base_EmperorListNode_t* newNode = (base_EmperorListNode_t*)malloc(sizeof(base_EmperorListNode_t));
	if (newNode == NULL)
	{
		fprintf(stderr, "Failed to allocate memory while creating new list node\n");
		exit(EXIT_FAILURE);
	}

	newNode->value = value;

	// Arrange pointers
	newNode->prev.voidV = NULL;
	newNode->succ       = lstV->first;
	lstV->first.voidV   = newNode;
	if (base_isEmpty(lst))
	{
		lstV->last.voidV = newNode;
	}
	lstV->length.intV++;

	return lst;
}

base_Any_t base_unite(base_Any_t lst1, base_Any_t lst2)
{
	base_EmperorList_t* lst1V = lst1.voidV;
	base_EmperorList_t* lst2V = lst2.voidV;

	// Update lengths
	lst1V->length.intV += lst2V->length.intV;
	lst2V->length.intV = lst1V->length.intV;

	// Reroute pointers
	((base_EmperorListNode_t*)(lst1V->last.voidV))->succ  = lst2V->first;
	((base_EmperorListNode_t*)(lst2V->first.voidV))->prev = lst1V->last;
	lst2V->first                                          = lst1V->first;
	lst1V->last                                           = lst2V->last;

	free(lst2V);

	return lst1;
}

base_Any_t base_stringToCharList(char* str) { return base_stringToCharListL(str, strlen(str)); }

base_Any_t base_stringToCharListL(char* str, size_t length)
{
	base_EmperorList_t* lst = (base_EmperorList_t*)base_initEmperorList().voidV;

	lst->length.intV = (int)length;

	// TODO Fix this?

	if (length > 0)
	{
		base_EmperorListNode_t* prev = NULL;
		base_EmperorListNode_t* curr = (base_EmperorListNode_t*)malloc(sizeof(base_EmperorListNode_t));
		if (curr == NULL)
		{
			fprintf(stderr, "Failed to allocate memory for list node while converting from string to [char]\n");
			exit(EXIT_FAILURE);
		}

		lst->first.voidV  = curr;
		curr->value.charV = str[0];
		prev              = curr;

		for (size_t i = 1; i < length; i++)
		{
			curr = (base_EmperorListNode_t*)malloc(sizeof(base_EmperorListNode_t));
			if (curr == NULL)
			{
				fprintf(stderr, "Failed to allocate memory for list node while converting from string to [char]\n");
				exit(EXIT_FAILURE);
			}

			curr->value.charV = str[i];

			// Juggle pointers
			curr->prev.voidV = prev;
			if (prev != NULL)
			{
				prev->succ.voidV = curr;
			}

			prev = curr;
		}

		curr->succ.voidV = NULL;
		lst->last.voidV  = curr;
	}

	return (base_Any_t){ .voidV = lst };
}

char* base_charListToString(base_Any_t lst)
{
	base_EmperorList_t* lstV = (base_EmperorList_t*)lst.voidV;
	int length               = lstV->length.intV;

	char* str = (char*)malloc((length + 1) * sizeof(char));
	if (str == NULL)
	{
		fprintf(stderr, "Failed to allocate space for string during copy\n");
		exit(EXIT_FAILURE);
	}

	base_EmperorListNode_t* curr = (base_EmperorListNode_t*)lstV->first.voidV;
	for (int i = 0; i < length; i++)
	{
		str[i] = curr->value.charV;
		curr   = (base_EmperorListNode_t*)curr->succ.voidV;

		if (curr == NULL && i != length - 1)
		{
			fprintf(stderr, "Encountered null current node when reading [char] in to internal string\n");
			exit(EXIT_FAILURE);
		}
	}

	str[length] = '\0';

	return str;
}
