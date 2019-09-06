#ifndef GENERICS_H_
#define GENERICS_H_

#include <stdbool.h>

typedef struct base_any
{
	int intV;
	char charV;
	bool boolV;
	double doubleV;
	void* voidV;
} base_Any_t;

#endif /* GENERICS_H_ */