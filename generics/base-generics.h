#ifndef BASE_GENERICS_H_
#define BASE_GENERICS_H_

#include "../unused/base-unused.h"
#include <stdbool.h>

typedef struct base_any
{
	int intV;
	char charV;
	bool boolV;
	double doubleV;
	void* voidV;
} base_Any_t;

void base_noDestroy(base_Any_t _);

#endif /* BASE_GENERICS_H_ */
