#ifndef GENERICS_H_
#define GENERICS_H_

#include <stdbool.h>

typedef struct any
{
	int intV;
	char charV;
	bool boolV;
	double doubleV;
	void* voidV;
} any_t;

#endif /* GENERICS_H_ */