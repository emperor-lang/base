#ifndef EMPEROR_LISTS_H_
#define EMPEROR_LISTS_H_

#include "generics.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct emperorListNode
{
	any_t value;
	struct emperorListNode* succ;
	struct emperorListNode* prev;
} emperorListNode_t;

typedef struct emperorList
{
	int length;
	emperorListNode_t* first;
	emperorListNode_t* last;
} emperorList_t;

emperorList_t* initEmperorList(void);
void destroyEmperorList(emperorList_t*, void (*)(any_t));
bool isEmpty(emperorList_t* lst);
any_t get(emperorList_t*, int);
emperorListNode_t* getNode(emperorList_t*, int);
emperorListNode_t* getFromFront(emperorList_t*, int);
emperorListNode_t* getFromBack(emperorList_t*, int);
emperorList_t* del(emperorList_t*, int);
emperorList_t* append(emperorList_t*, any_t);
emperorList_t* prepend(emperorList_t*, any_t);
emperorList_t* unite(emperorList_t*, emperorList_t*);

emperorList_t* stringToCharList(char*);
emperorList_t* stringToCharListL(char* str, size_t length);
char* charListToString(emperorList_t*);

#endif /* EMPEROR_LISTS_H_ */