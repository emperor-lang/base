#ifndef BASE_LISTS_H_
#define BASE_LISTS_H_

#include "../generics/base-generics.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct base_emperorListNode
{
	base_Any_t value;
	struct base_emperorListNode* succ;
	struct base_emperorListNode* prev;
} base_EmperorListNode_t;

typedef struct base_emperorList
{
	int length;
	base_EmperorListNode_t* first;
	base_EmperorListNode_t* last;
} base_EmperorList_t;

base_EmperorList_t* base_initEmperorList(void);
void base_destroyEmperorList(base_EmperorList_t*, void (*)(base_Any_t));
bool base_isEmpty(base_EmperorList_t* lst);
base_Any_t base_get(base_EmperorList_t*, int);
base_EmperorListNode_t* getNode(base_EmperorList_t*, int);
base_EmperorListNode_t* getFromFront(base_EmperorList_t*, int);
base_EmperorListNode_t* getFromBack(base_EmperorList_t*, int);
base_EmperorList_t* base_del(base_EmperorList_t*, int);
base_EmperorList_t* base_append(base_EmperorList_t*, base_Any_t);
base_EmperorList_t* base_prepend(base_EmperorList_t*, base_Any_t);
base_EmperorList_t* base_unite(base_EmperorList_t*, base_EmperorList_t*);

base_EmperorList_t* base_stringToCharList(char*);
base_EmperorList_t* base_stringToCharListL(char* str, size_t length);
char* base_charListToString(base_EmperorList_t*);

#endif /* BASE_LISTS_H_ */