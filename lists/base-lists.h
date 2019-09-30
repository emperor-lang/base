#ifndef BASE_LISTS_H_
#define BASE_LISTS_H_

#include "../generics/base-generics.h"
#include "../unused/base-unused.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct base_emperorListNode
{
	base_Any_t value;
	base_Any_t succ;
	base_Any_t prev;
} base_EmperorListNode_t;

typedef struct base_emperorList
{
	base_Any_t length;
	base_Any_t first;
	base_Any_t last;
} base_EmperorList_t;

base_Any_t base_initEmperorList();
void base_destroyEmperorList(base_Any_t, void (*)(base_Any_t));
base_Any_t base_shallowCopyList(base_Any_t);
bool base_isEmpty(base_Any_t lst);
base_Any_t base_del(base_Any_t, int, void (*)(base_Any_t));
base_Any_t base_get(base_Any_t, int);
base_Any_t base_append(base_Any_t, base_Any_t);
base_Any_t base_prepend(base_Any_t, base_Any_t);
base_Any_t base_unite(base_Any_t, base_Any_t);

base_Any_t base_stringToCharList(char* str);
base_Any_t base_stringToCharListL(char* str, size_t length);
char* base_charListToString(base_Any_t);

#endif /* BASE_LISTS_H_ */
