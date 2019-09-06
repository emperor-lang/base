#ifndef BASE_GENERICS_H_
#define BASE_GENERICS_H_

#include <stdbool.h>

typedef struct base_any
{
	int intV;
	char charV;
	bool boolV;
	double doubleV;
	void* voidV;
} base_Any_t;

#endif /* BASE_GENERICS_H_ */